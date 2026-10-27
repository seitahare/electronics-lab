# Experiment 16 ESP32-S3 Firmware

This directory contains the last-tested ESP-IDF source from Experiment 16, copied from the local bench project after the servo module was separated into `servo.c` and `servo.h` on 2026-10-27.

The firmware combines:

- two 50 Hz SG90 servo channels on GPIO3 and GPIO4;
- an LSM6DSV16X IMU at I²C address `0x6A`;
- an SSD1306-compatible OLED at I²C address `0x3C`;
- a Wi-Fi SoftAP and ESP-IDF HTTP server;
- PAN/TILT browser controls and a live six-axis JSON/dashboard view.

See the [Experiment 16 report](../../experiments/16-esp32s3-integrated-pan-tilt-robotics.md) for wiring, observations, troubleshooting, measurements, and limitations.

## Build

Use ESP-IDF v6.1:

```sh
idf.py set-target esp32s3
idf.py build
```

The sanitized repository copy was configured for `esp32s3` and built successfully with ESP-IDF v6.1 on 2026-10-27. This confirms source-level build consistency; it does not replace the recorded physical bench tests or claim that this public copy was reflashed after sanitization.

The repository intentionally excludes generated `build/` output, local `sdkconfig` files, backups, and development-machine paths.

## SoftAP configuration

`main/hello_world_main.c` contains the public development defaults:

```c
#define AP_SSID "ESP32-PANTILT"
#define AP_PASSWORD "ChangeMe1234"
```

`ChangeMe1234` is a non-secret placeholder. Replace it before using the firmware outside a controlled bench setup. Do not commit a private Wi-Fi password or other credential.

## Hardware notes

- PAN signal: XIAO D2 / GPIO3
- TILT signal: XIAO D3 / GPIO4
- I²C SDA: XIAO D4 / GPIO5
- I²C SCL: XIAO D5 / GPIO6
- Servo supply: separate nominal 5 V supply with common ground to the XIAO
- Sensor/display supply: XIAO 3V3

For the tested servo hardware, brown was ground, orange was external +5 V, and yellow was the PWM signal. Verify the actual leads before powering different hardware.

The configured `1450–1550 µs` pulse range was used successfully in this mounted setup. It is not a universal SG90 limit or a calibrated shaft-angle range.
