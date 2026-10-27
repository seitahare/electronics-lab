
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_check.h"

#include "esp_err.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "shared_i2c_test.h"
#include "imu_web.h"

// I2C configuration
#define I2C_SDA_PIN GPIO_NUM_5
#define I2C_SCL_PIN GPIO_NUM_6

#define OLED_ADDR 0x3C
#define IMU_ADDR  0x6A

// IMU registers
#define IMU_WHO_AM_I 0x0F
#define IMU_CTRL1    0x10
#define IMU_CTRL2    0x11
#define IMU_CTRL3    0x12
#define IMU_CTRL6    0x15
#define IMU_CTRL8    0x17
#define IMU_OUTX_L_G 0x22

// Sensor sensitivity
#define ACC_SCALE  0.00059820565f
#define GYRO_SCALE 0.00875f

#define UPDATE_INTERVAL_MS 200

static const char *TAG = "IMU_OLED";

// 5x7 font, indexed from ASCII 32.
static const uint8_t font[59][5] = {
    ['+' - 32] = {0x08, 0x08, 0x3E, 0x08, 0x08},
    ['-' - 32] = {0x08, 0x08, 0x08, 0x08, 0x08},
    ['.' - 32] = {0x00, 0x60, 0x60, 0x00, 0x00},
    ['/' - 32] = {0x20, 0x10, 0x08, 0x04, 0x02},
    [':' - 32] = {0x00, 0x36, 0x36, 0x00, 0x00},

    ['0' - 32] = {0x3E, 0x51, 0x49, 0x45, 0x3E},
    ['1' - 32] = {0x00, 0x42, 0x7F, 0x40, 0x00},
    ['2' - 32] = {0x42, 0x61, 0x51, 0x49, 0x46},
    ['3' - 32] = {0x21, 0x41, 0x45, 0x4B, 0x31},
    ['4' - 32] = {0x18, 0x14, 0x12, 0x7F, 0x10},
    ['5' - 32] = {0x27, 0x45, 0x45, 0x45, 0x39},
    ['6' - 32] = {0x3C, 0x4A, 0x49, 0x49, 0x30},
    ['7' - 32] = {0x01, 0x71, 0x09, 0x05, 0x03},
    ['8' - 32] = {0x36, 0x49, 0x49, 0x49, 0x36},
    ['9' - 32] = {0x06, 0x49, 0x49, 0x29, 0x1E},

    ['A' - 32] = {0x7E, 0x11, 0x11, 0x11, 0x7E},
    ['C' - 32] = {0x3E, 0x41, 0x41, 0x41, 0x22},
    ['D' - 32] = {0x7F, 0x41, 0x41, 0x22, 0x1C},
    ['E' - 32] = {0x7F, 0x49, 0x49, 0x49, 0x41},
    ['G' - 32] = {0x3E, 0x41, 0x49, 0x49, 0x7A},
    ['M' - 32] = {0x7F, 0x02, 0x0C, 0x02, 0x7F},
    ['O' - 32] = {0x3E, 0x41, 0x41, 0x41, 0x3E},
    ['R' - 32] = {0x7F, 0x09, 0x19, 0x29, 0x46},
    ['S' - 32] = {0x46, 0x49, 0x49, 0x49, 0x31},
    ['X' - 32] = {0x63, 0x14, 0x08, 0x14, 0x63},
    ['Y' - 32] = {0x07, 0x08, 0x70, 0x08, 0x07},
    ['Z' - 32] = {0x61, 0x51, 0x49, 0x45, 0x43},
};

// Write a register in the IMU.
static esp_err_t imu_write_reg(
    i2c_master_dev_handle_t imu,
    uint8_t reg,
    uint8_t value)
{
    uint8_t packet[2] = {reg, value};

    return i2c_master_transmit(
        imu,
        packet,
        sizeof(packet),
        1000
    );
}

// Read consecutive IMU registers.
static esp_err_t imu_read_regs(
    i2c_master_dev_handle_t imu,
    uint8_t reg,
    uint8_t *data,
    size_t length)
{
    return i2c_master_transmit_receive(
        imu,
        &reg,
        1,
        data,
        length,
        1000
    );
}

// Configure the accelerometer and gyroscope.
static esp_err_t imu_init(i2c_master_dev_handle_t imu)
{
    uint8_t who_am_i = 0;

    esp_err_t err = imu_read_regs(
        imu,
        IMU_WHO_AM_I,
        &who_am_i,
        1
    );

    if (err != ESP_OK) {
        return err;
    }

    ESP_LOGI(TAG, "WHO_AM_I = 0x%02X", who_am_i);

    if (who_am_i != 0x70) {
        ESP_LOGE(TAG, "Unexpected IMU ID");
        return ESP_ERR_INVALID_RESPONSE;
    }

    // Block data update and enable auto-increment.
    ESP_RETURN_ON_ERROR(
        imu_write_reg(imu, IMU_CTRL3, 0x44),
        TAG,
        "CTRL3 write failed"
    );

    // Accelerometer full scale: +/-2 g.
    ESP_RETURN_ON_ERROR(
        imu_write_reg(imu, IMU_CTRL8, 0x00),
        TAG,
        "CTRL8 write failed"
    );

    // Gyroscope full scale: +/-250 dps.
    ESP_RETURN_ON_ERROR(
        imu_write_reg(imu, IMU_CTRL6, 0x01),
        TAG,
        "CTRL6 write failed"
    );

    // Accelerometer ODR: 120 Hz.
    ESP_RETURN_ON_ERROR(
        imu_write_reg(imu, IMU_CTRL1, 0x06),
        TAG,
        "CTRL1 write failed"
    );

    // Gyroscope ODR: 120 Hz.
    ESP_RETURN_ON_ERROR(
        imu_write_reg(imu, IMU_CTRL2, 0x06),
        TAG,
        "CTRL2 write failed"
    );

    vTaskDelay(pdMS_TO_TICKS(50));

    ESP_LOGI(TAG, "IMU initialized");
    return ESP_OK;
}

// Convert two bytes to a signed 16-bit value.
static int16_t read_int16(const uint8_t *data)
{
    uint16_t value =
        (uint16_t)data[0] |
        ((uint16_t)data[1] << 8);

    return (int16_t)value;
}

// Send a command to the SSD1306.
static void oled_command(
    i2c_master_dev_handle_t oled,
    uint8_t command)
{
    uint8_t packet[2] = {0x00, command};

    ESP_ERROR_CHECK(
        i2c_master_transmit(
            oled,
            packet,
            sizeof(packet),
            1000
        )
    );
}

// Select an OLED page and starting column.
static void oled_cursor(
    i2c_master_dev_handle_t oled,
    uint8_t page)
{
    oled_command(oled, 0xB0 | page);
    oled_command(oled, 0x00);
    oled_command(oled, 0x10);
}

// Initialize the OLED controller.
static void oled_init(i2c_master_dev_handle_t oled)
{
    const uint8_t commands[] = {
        0xAE,
        0xD5, 0x80,
        0xA8, 0x3F,
        0xD3, 0x00,
        0x40,
        0x8D, 0x14,
        0x20, 0x02,
        0xA1,
        0xC8,
        0xDA, 0x12,
        0x81, 0x7F,
        0xD9, 0xF1,
        0xDB, 0x40,
        0xA4,
        0xA6,
        0x2E,
        0xAF
    };

    for (size_t i = 0; i < sizeof(commands); i++) {
        oled_command(oled, commands[i]);
    }

    ESP_LOGI(TAG, "OLED initialized");
}

// Draw one line on an OLED page.
static void oled_draw_line(
    i2c_master_dev_handle_t oled,
    uint8_t page,
    const char *text)
{
    uint8_t packet[129] = {0x40};

    for (size_t i = 0;
         text[i] != '\0' && i < 21;
         i++) {

        unsigned char c = (unsigned char)text[i];

        if (c < 32 || c > 90) {
            c = ' ';
        }

        size_t position = 1 + i * 6;

        memcpy(
            &packet[position],
            font[c - 32],
            5
        );
    }

    oled_cursor(oled, page);

    ESP_ERROR_CHECK(
        i2c_master_transmit(
            oled,
            packet,
            sizeof(packet),
            1000
        )
    );
}

// Prepare the initial OLED screen.
static void oled_prepare_screen(
    i2c_master_dev_handle_t oled)
{
    for (uint8_t page = 0; page < 8; page++) {
        oled_draw_line(oled, page, "");
    }

    oled_draw_line(oled, 0, "ACC M/S2");
    oled_draw_line(oled, 4, "GYRO DEG/S");
}

// Shared I2C application.
void shared_i2c_test_run(void)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2C_SDA_PIN,
        .scl_io_num = I2C_SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus = NULL;

    ESP_ERROR_CHECK(
        i2c_new_master_bus(&bus_config, &bus)
    );

    // Register IMU on the shared I2C bus.
    i2c_device_config_t imu_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = IMU_ADDR,
        .scl_speed_hz = 100000,
    };

    i2c_master_dev_handle_t imu = NULL;

    ESP_ERROR_CHECK(
        i2c_master_bus_add_device(
            bus,
            &imu_config,
            &imu
        )
    );

    // Register OLED on the same I2C bus.
    i2c_device_config_t oled_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = OLED_ADDR,
        .scl_speed_hz = 100000,
    };

    i2c_master_dev_handle_t oled = NULL;

    ESP_ERROR_CHECK(
        i2c_master_bus_add_device(
            bus,
            &oled_config,
            &oled
        )
    );

    ESP_LOGI(TAG, "Shared I2C bus ready");

    // Initialize both devices.
    ESP_ERROR_CHECK(imu_init(imu));

    oled_init(oled);
    oled_prepare_screen(oled);

    uint32_t count = 0;

    // Continuous sensor acquisition and display.
    while (1) {
        uint8_t raw[12];

        esp_err_t err = imu_read_regs(
            imu,
            IMU_OUTX_L_G,
            raw,
            sizeof(raw)
        );

        if (err != ESP_OK) {
            ESP_LOGW(
                TAG,
                "IMU read failed: %s",
                esp_err_to_name(err)
            );

            vTaskDelay(
                pdMS_TO_TICKS(UPDATE_INTERVAL_MS)
            );

            continue;
        }

        // Raw angular velocity.
        int16_t gx_raw = read_int16(&raw[0]);
        int16_t gy_raw = read_int16(&raw[2]);
        int16_t gz_raw = read_int16(&raw[4]);

        // Raw acceleration.
        int16_t ax_raw = read_int16(&raw[6]);
        int16_t ay_raw = read_int16(&raw[8]);
        int16_t az_raw = read_int16(&raw[10]);

        // Convert to physical units.
        float ax = ax_raw * ACC_SCALE;
        float ay = ay_raw * ACC_SCALE;
        float az = az_raw * ACC_SCALE;

        float gx = gx_raw * GYRO_SCALE;
        float gy = gy_raw * GYRO_SCALE;
        float gz = gz_raw * GYRO_SCALE;

        // Publish all six axes to the Web API.
        imu_web_publish(ax, ay, az, gx, gy, gz);

        // Create text for OLED.
        char line[32];

        snprintf(
            line,
            sizeof(line),
            "X:%+.2f Y:%+.2f",
            ax,
            ay
        );

        oled_draw_line(oled, 1, line);

        snprintf(
            line,
            sizeof(line),
            "Z:%+.2f",
            az
        );

        oled_draw_line(oled, 2, line);

        snprintf(
            line,
            sizeof(line),
            "X:%+.2f Y:%+.2f",
            gx,
            gy
        );

        oled_draw_line(oled, 5, line);

        snprintf(
            line,
            sizeof(line),
            "Z:%+.2f",
            gz
        );

        oled_draw_line(oled, 6, line);

        // Print serial output approximately once per second.
        if (count % 5 == 0) {
            ESP_LOGI(
                TAG,
                "ACC: %.2f %.2f %.2f m/s2",
                ax,
                ay,
                az
            );

            ESP_LOGI(
                TAG,
                "GYRO: %.2f %.2f %.2f deg/s",
                gx,
                gy,
                gz
            );
        }

        count++;

        vTaskDelay(
            pdMS_TO_TICKS(UPDATE_INTERVAL_MS)
        );
    }
}
