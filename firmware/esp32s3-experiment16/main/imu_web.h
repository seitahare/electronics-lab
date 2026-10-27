#ifndef IMU_WEB_H
#define IMU_WEB_H

#include "esp_err.h"
#include "esp_http_server.h"

esp_err_t imu_web_init(void);

void imu_web_publish(
    float ax, float ay, float az,
    float gx, float gy, float gz
);

esp_err_t imu_web_register(httpd_handle_t server);

#endif
