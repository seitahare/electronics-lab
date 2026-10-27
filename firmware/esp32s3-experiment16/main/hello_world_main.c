
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "esp_err.h"
#include "esp_event.h"
#include "esp_http_server.h"
#include "esp_netif.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

#include "servo.h"
#include "imu_web.h"
#include "shared_i2c_test.h"

// Development SoftAP configuration. Replace the password before deployment.
#ifndef AP_SSID
#define AP_SSID "ESP32-PANTILT"
#endif

#ifndef AP_PASSWORD
#define AP_PASSWORD "ChangeMe1234"
#endif

// Current servo pulse positions.
static uint32_t pan_us = SERVO_CENTER_US;
static uint32_t tilt_us = SERVO_CENTER_US;

// Initialize the Wi-Fi access point.
static void wifi_init_ap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(
        esp_event_loop_create_default()
    );

    esp_netif_create_default_wifi_ap();

    wifi_init_config_t init_config =
        WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(
        esp_wifi_init(&init_config)
    );

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = AP_SSID,
            .password = AP_PASSWORD,
            .ssid_len = 0,
            .channel = 1,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    ESP_ERROR_CHECK(
        esp_wifi_set_mode(WIFI_MODE_AP)
    );

    ESP_ERROR_CHECK(
        esp_wifi_set_config(
            WIFI_IF_AP,
            &wifi_config
        )
    );

    ESP_ERROR_CHECK(esp_wifi_start());

    printf("Wi-Fi AP started: %s\n", AP_SSID);
}

// Serve the original control page.
static esp_err_t root_handler(httpd_req_t *req)
{
    char html[1024];

    snprintf(
        html,
        sizeof(html),

        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<meta name='viewport' "
        "content='width=device-width,initial-scale=1'>"
        "<title>ESP32 Pan-Tilt</title>"
        "</head>"

        "<body>"
        "<h1>ESP32 Pan-Tilt</h1>"

        "<p><a href='/dashboard'>"
        "Open Robotics Dashboard"
        "</a></p>"

        "<h2>PAN</h2>"
        "<p>Pulse: %lu us</p>"
        "<p><a href='/pan/minus'>PAN -</a></p>"
        "<p><a href='/pan/center'>PAN CENTER</a></p>"
        "<p><a href='/pan/plus'>PAN +</a></p>"

        "<h2>TILT</h2>"
        "<p>Pulse: %lu us</p>"
        "<p><a href='/tilt/minus'>TILT -</a></p>"
        "<p><a href='/tilt/center'>TILT CENTER</a></p>"
        "<p><a href='/tilt/plus'>TILT +</a></p>"

        "</body>"
        "</html>",

        (unsigned long)pan_us,
        (unsigned long)tilt_us
    );

    httpd_resp_set_type(
        req,
        "text/html; charset=utf-8"
    );

    return httpd_resp_sendstr(req, html);
}

// Handle PAN and TILT commands.
static esp_err_t control_handler(httpd_req_t *req)
{
    const char *uri = req->uri;

    if (strcmp(uri, "/pan/minus") == 0) {
        if (pan_us >= SERVO_MIN_US + SERVO_STEP_US) {
            pan_us -= SERVO_STEP_US;
        }

        servo_set_pulse(SERVO_AXIS_PAN, pan_us);
    }
    else if (strcmp(uri, "/pan/plus") == 0) {
        if (pan_us <= SERVO_MAX_US - SERVO_STEP_US) {
            pan_us += SERVO_STEP_US;
        }

        servo_set_pulse(SERVO_AXIS_PAN, pan_us);
    }
    else if (strcmp(uri, "/pan/center") == 0) {
        pan_us = SERVO_CENTER_US;

        servo_set_pulse(SERVO_AXIS_PAN, pan_us);
    }
    else if (strcmp(uri, "/tilt/minus") == 0) {
        if (tilt_us >= SERVO_MIN_US + SERVO_STEP_US) {
            tilt_us -= SERVO_STEP_US;
        }

        servo_set_pulse(SERVO_AXIS_TILT, tilt_us);
    }
    else if (strcmp(uri, "/tilt/plus") == 0) {
        if (tilt_us <= SERVO_MAX_US - SERVO_STEP_US) {
            tilt_us += SERVO_STEP_US;
        }

        servo_set_pulse(SERVO_AXIS_TILT, tilt_us);
    }
    else if (strcmp(uri, "/tilt/center") == 0) {
        tilt_us = SERVO_CENTER_US;

        servo_set_pulse(SERVO_AXIS_TILT, tilt_us);
    }

    httpd_resp_set_status(
        req,
        "303 See Other"
    );

    httpd_resp_set_hdr(
        req,
        "Location",
        "/"
    );

    return httpd_resp_send(req, NULL, 0);
}

// Start the HTTP server.
static void start_webserver(void)
{
    httpd_handle_t server = NULL;

    httpd_config_t config =
        HTTPD_DEFAULT_CONFIG();

    config.max_uri_handlers = 12;

    ESP_ERROR_CHECK(
        httpd_start(&server, &config)
    );

    httpd_uri_t root = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = root_handler,
        .user_ctx = NULL,
    };

    ESP_ERROR_CHECK(
        httpd_register_uri_handler(server, &root)
    );

    static const char *paths[] = {
        "/pan/minus",
        "/pan/center",
        "/pan/plus",
        "/tilt/minus",
        "/tilt/center",
        "/tilt/plus",
    };

    for (size_t i = 0;
         i < sizeof(paths) / sizeof(paths[0]);
         i++) {

        httpd_uri_t handler = {
            .uri = paths[i],
            .method = HTTP_GET,
            .handler = control_handler,
            .user_ctx = NULL,
        };

        ESP_ERROR_CHECK(
            httpd_register_uri_handler(
                server,
                &handler
            )
        );
    }

    // Register the IMU API and dashboard.
    ESP_ERROR_CHECK(
        imu_web_register(server)
    );

    printf("HTTP server ready.\n");
    printf("Open: http://192.168.4.1\n");
    printf("Dashboard: http://192.168.4.1/dashboard\n");
    printf("IMU API: http://192.168.4.1/api/imu\n");
}

// Main application entry point.
void app_main(void)
{
    // Initialize non-volatile storage.
    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
        ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {

        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);

    // Initialize telemetry queue.
    ESP_ERROR_CHECK(imu_web_init());

    // Initialize PWM and both servos.
    servos_init();

    // Initialize Wi-Fi SoftAP.
    wifi_init_ap();

    // Start the HTTP server.
    start_webserver();

    // Continuously update IMU and OLED.
    shared_i2c_test_run();
}
