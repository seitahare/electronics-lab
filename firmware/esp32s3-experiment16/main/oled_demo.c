#include <stdint.h>
#include <stddef.h>

#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_err.h"
#include "esp_log.h"

#include "oled_demo.h"

#define OLED_ADDR 0x3C
#define OLED_SDA GPIO_NUM_5
#define OLED_SCL GPIO_NUM_6

static const char *TAG = "OLED";

static esp_err_t oled_command(
    i2c_master_dev_handle_t dev,
    uint8_t command)
{
    uint8_t packet[] = {0x00, command};

    return i2c_master_transmit(
        dev, packet, sizeof(packet), 1000
    );
}

static void oled_cursor(
    i2c_master_dev_handle_t dev,
    uint8_t page,
    uint8_t column)
{
    ESP_ERROR_CHECK(oled_command(dev, 0xB0 | page));
    ESP_ERROR_CHECK(oled_command(dev, 0x00 | (column & 0x0F)));
    ESP_ERROR_CHECK(oled_command(dev, 0x10 | (column >> 4)));
}

void oled_demo_run(void)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = OLED_SDA,
        .scl_io_num = OLED_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus;

    ESP_ERROR_CHECK(
        i2c_new_master_bus(&bus_config, &bus)
    );

    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = OLED_ADDR,
        .scl_speed_hz = 100000,
    };

    i2c_master_dev_handle_t dev;

    ESP_ERROR_CHECK(
        i2c_master_bus_add_device(
            bus, &dev_config, &dev
        )
    );

    const uint8_t init[] = {
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

    for (size_t i = 0; i < sizeof(init); i++) {
        ESP_ERROR_CHECK(oled_command(dev, init[i]));
    }

    uint8_t blank[129] = {0x40};

    for (uint8_t page = 0; page < 8; page++) {
        oled_cursor(dev, page, 0);

        ESP_ERROR_CHECK(
            i2c_master_transmit(
                dev, blank, sizeof(blank), 1000
            )
        );
    }

    // 5x7 pixel glyphs with spacing: HELLO!
    const uint8_t glyphs[6][6] = {
        {0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00},
        {0x7F, 0x49, 0x49, 0x49, 0x41, 0x00},
        {0x7F, 0x40, 0x40, 0x40, 0x40, 0x00},
        {0x7F, 0x40, 0x40, 0x40, 0x40, 0x00},
        {0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00},
        {0x00, 0x00, 0x5F, 0x00, 0x00, 0x00}
    };

    uint8_t text[37] = {0x40};

    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 6; j++) {
            text[1 + i * 6 + j] = glyphs[i][j];
        }
    }

    oled_cursor(dev, 3, 46);

    ESP_ERROR_CHECK(
        i2c_master_transmit(
            dev, text, sizeof(text), 1000
        )
    );

    ESP_LOGI(TAG, "HELLO! rendered");

    ESP_ERROR_CHECK(i2c_master_bus_rm_device(dev));
    ESP_ERROR_CHECK(i2c_del_master_bus(bus));
}
