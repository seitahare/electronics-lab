#include <stdint.h>
#include <stddef.h>

#include "driver/i2c_master.h"
#include "esp_err.h"
#include "esp_log.h"

#include "i2c_probe.h"

#define I2C_SDA_PIN GPIO_NUM_5
#define I2C_SCL_PIN GPIO_NUM_6

static const char *TAG = "I2C_PROBE";

void i2c_probe_run(void)
{
    i2c_master_bus_config_t bus_config = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2C_SDA_PIN,
        .scl_io_num = I2C_SCL_PIN,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus;

    esp_err_t err = i2c_new_master_bus(
        &bus_config,
        &bus
    );

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C init failed: %s",
                 esp_err_to_name(err));
        return;
    }

    const uint8_t addresses[] = {
        0x3C,
        0x3D,
        0x6A
    };

    for (size_t i = 0;
         i < sizeof(addresses) / sizeof(addresses[0]);
         i++) {

        err = i2c_master_probe(
            bus,
            addresses[i],
            100
        );

        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Device found: 0x%02X",
                     addresses[i]);
        } else if (err == ESP_ERR_NOT_FOUND) {
            ESP_LOGI(TAG, "No ACK: 0x%02X",
                     addresses[i]);
        } else {
            ESP_LOGW(TAG, "Probe 0x%02X: %s",
                     addresses[i],
                     esp_err_to_name(err));
        }
    }

    ESP_ERROR_CHECK(i2c_del_master_bus(bus));
}
