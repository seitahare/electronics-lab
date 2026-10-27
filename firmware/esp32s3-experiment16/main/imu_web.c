
#include <stdio.h>
#include <stdint.h>

#include "esp_http_server.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "imu_web.h"

typedef struct {
    float ax;
    float ay;
    float az;

    float gx;
    float gy;
    float gz;

    uint32_t sequence;
} imu_sample_t;

static QueueHandle_t imu_queue = NULL;
static uint32_t sample_sequence = 0;

static const char *TAG = "IMU_WEB";

// Create a queue for the latest IMU measurement.
esp_err_t imu_web_init(void)
{
    if (imu_queue != NULL) {
        return ESP_OK;
    }

    imu_queue = xQueueCreate(
        1,
        sizeof(imu_sample_t)
    );

    if (imu_queue == NULL) {
        return ESP_ERR_NO_MEM;
    }

    ESP_LOGI(TAG, "IMU queue initialized");
    return ESP_OK;
}

// Publish the newest measurement.
void imu_web_publish(
    float ax, float ay, float az,
    float gx, float gy, float gz)
{
    if (imu_queue == NULL) {
        return;
    }

    imu_sample_t sample = {
        .ax = ax,
        .ay = ay,
        .az = az,
        .gx = gx,
        .gy = gy,
        .gz = gz,
        .sequence = ++sample_sequence
    };

    xQueueOverwrite(imu_queue, &sample);
}

// Return IMU measurements as JSON.
static esp_err_t imu_api_handler(httpd_req_t *req)
{
    imu_sample_t sample;

    httpd_resp_set_type(
        req,
        "application/json"
    );

    httpd_resp_set_hdr(
        req,
        "Cache-Control",
        "no-store"
    );

    if (imu_queue == NULL ||
        xQueuePeek(imu_queue, &sample, 0) != pdTRUE) {

        return httpd_resp_sendstr(
            req,
            "{\"ready\":false}"
        );
    }

    char json[256];

    snprintf(
        json,
        sizeof(json),
        "{"
        "\"ready\":true,"
        "\"ax\":%.3f,"
        "\"ay\":%.3f,"
        "\"az\":%.3f,"
        "\"gx\":%.3f,"
        "\"gy\":%.3f,"
        "\"gz\":%.3f,"
        "\"sequence\":%lu"
        "}",
        sample.ax,
        sample.ay,
        sample.az,
        sample.gx,
        sample.gy,
        sample.gz,
        (unsigned long)sample.sequence
    );

    return httpd_resp_sendstr(req, json);
}

// HTML page stored in program flash.
static const char dashboard_html[] =
"<!DOCTYPE html>"
"<html lang='en'>"
"<head>"
"<meta charset='utf-8'>"
"<meta name='viewport' content='width=device-width,initial-scale=1'>"
"<title>ESP32 Robotics Dashboard</title>"
"<style>"
"body{font-family:system-ui,sans-serif;background:#111827;"
"color:#f9fafb;max-width:650px;margin:30px auto;padding:16px}"
"h1{font-size:24px}"
"h2{font-size:17px;color:#93c5fd}"
".card{background:#1f2937;padding:18px;border-radius:12px;margin:14px 0}"
".row{display:flex;gap:12px;flex-wrap:wrap}"
".axis{flex:1;min-width:130px}"
"button{background:#2563eb;color:white;border:0;"
"border-radius:8px;padding:12px 18px;margin:3px;cursor:pointer}"
"button:active{background:#1d4ed8}"
".value{font:20px monospace;margin:9px 0}"
".status{color:#86efac;font-size:13px}"
"</style>"
"</head>"
"<body>"
"<h1>ESP32 Robotics Dashboard</h1>"
"<p id='status' class='status'>Connecting...</p>"

"<div class='card'>"
"<h2>PAN Control</h2>"
"<button data-command='/pan/minus'>-</button>"
"<button data-command='/pan/center'>CENTER</button>"
"<button data-command='/pan/plus'>+</button>"
"</div>"

"<div class='card'>"
"<h2>TILT Control</h2>"
"<button data-command='/tilt/minus'>-</button>"
"<button data-command='/tilt/center'>CENTER</button>"
"<button data-command='/tilt/plus'>+</button>"
"</div>"

"<div class='card'>"
"<h2>IMU Live Data</h2>"
"<div class='row'>"
"<div class='axis'>"
"<h2>ACC (m/s2)</h2>"
"<div class='value'>X: <span id='ax'>--</span></div>"
"<div class='value'>Y: <span id='ay'>--</span></div>"
"<div class='value'>Z: <span id='az'>--</span></div>"
"</div>"
"<div class='axis'>"
"<h2>GYRO (deg/s)</h2>"
"<div class='value'>X: <span id='gx'>--</span></div>"
"<div class='value'>Y: <span id='gy'>--</span></div>"
"<div class='value'>Z: <span id='gz'>--</span></div>"
"</div>"
"</div>"
"</div>"

"<script>"
"const statusEl=document.getElementById('status');"

"async function updateIMU(){"
"try{"
"const response=await fetch('/api/imu',{cache:'no-store'});"
"if(!response.ok)throw new Error('HTTP error');"
"const data=await response.json();"
"if(!data.ready){statusEl.textContent='Waiting for IMU...';return;}"
"for(const axis of ['ax','ay','az','gx','gy','gz']){"
"document.getElementById(axis).textContent=Number(data[axis]).toFixed(2);"
"}"
"statusEl.textContent='IMU connected · sample '+data.sequence;"
"}catch(error){statusEl.textContent='IMU connection error';}"
"}"

"async function sendControl(path){"
"try{"
"const response=await fetch(path,{cache:'no-store'});"
"if(!response.ok)throw new Error('Control error');"
"}catch(error){statusEl.textContent='Servo command failed';}"
"}"

"document.querySelectorAll('button[data-command]').forEach(button=>{"
"button.addEventListener('click',()=>sendControl(button.dataset.command));"
"});"

"updateIMU();"
"setInterval(updateIMU,500);"
"</script>"
"</body>"
"</html>";

// Serve the dashboard page.
static esp_err_t dashboard_handler(httpd_req_t *req)
{
    httpd_resp_set_type(
        req,
        "text/html; charset=utf-8"
    );

    return httpd_resp_sendstr(
        req,
        dashboard_html
    );
}

// Register the HTTP endpoints.
esp_err_t imu_web_register(httpd_handle_t server)
{
    httpd_uri_t imu_uri = {
        .uri = "/api/imu",
        .method = HTTP_GET,
        .handler = imu_api_handler,
        .user_ctx = NULL
    };

    esp_err_t err = httpd_register_uri_handler(
        server,
        &imu_uri
    );

    if (err != ESP_OK) {
        return err;
    }

    httpd_uri_t dashboard_uri = {
        .uri = "/dashboard",
        .method = HTTP_GET,
        .handler = dashboard_handler,
        .user_ctx = NULL
    };

    err = httpd_register_uri_handler(
        server,
        &dashboard_uri
    );

    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Dashboard registered");
    }

    return err;
}
