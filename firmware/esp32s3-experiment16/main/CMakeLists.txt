idf_component_register(
    SRCS
        "hello_world_main.c"
        "servo.c"
        "i2c_probe.c"
        "oled_demo.c"
        "shared_i2c_test.c"
        "imu_web.c"

    INCLUDE_DIRS "."

    PRIV_REQUIRES
        esp_driver_ledc
        esp_driver_i2c
        esp_driver_gpio
        esp_wifi
        esp_event
        esp_netif
        esp_http_server
        nvs_flash
        freertos
)
