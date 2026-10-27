#include <stdint.h>
#include <stdio.h>

#include "driver/ledc.h"
#include "esp_err.h"

#include "servo.h"

// Hardware pin configuration.
#define PAN_GPIO          3
#define TILT_GPIO         4

// PWM configuration.
#define SERVO_FREQ_HZ     50
#define SERVO_TIMER       LEDC_TIMER_0
#define SERVO_MODE        LEDC_LOW_SPEED_MODE
#define SERVO_RESOLUTION  LEDC_TIMER_14_BIT

#define PAN_CHANNEL       LEDC_CHANNEL_0
#define TILT_CHANNEL      LEDC_CHANNEL_1

// Convert pulse width to LEDC duty.
static uint32_t pulse_to_duty(uint32_t pulse_us)
{
    return (uint32_t)(
        ((uint64_t)pulse_us *
         (1U << 14) *
         SERVO_FREQ_HZ)
        / 1000000U
    );
}

// Resolve a logical axis to an LEDC channel.
static ledc_channel_t servo_channel(
    servo_axis_t axis)
{
    if (axis == SERVO_AXIS_PAN) {
        return PAN_CHANNEL;
    }

    return TILT_CHANNEL;
}

// Set the pulse width for one servo.
void servo_set_pulse(
    servo_axis_t axis,
    uint32_t pulse_us)
{
    if (axis != SERVO_AXIS_PAN &&
        axis != SERVO_AXIS_TILT) {
        return;
    }

    if (pulse_us < SERVO_MIN_US) {
        pulse_us = SERVO_MIN_US;
    }

    if (pulse_us > SERVO_MAX_US) {
        pulse_us = SERVO_MAX_US;
    }

    ledc_channel_t channel = servo_channel(axis);

    uint32_t duty = pulse_to_duty(pulse_us);

    ESP_ERROR_CHECK(
        ledc_set_duty(
            SERVO_MODE,
            channel,
            duty
        )
    );

    ESP_ERROR_CHECK(
        ledc_update_duty(
            SERVO_MODE,
            channel
        )
    );
}

// Initialize one LEDC channel.
static void servo_init(
    int gpio,
    ledc_channel_t channel)
{
    ledc_channel_config_t config = {
        .gpio_num = gpio,
        .speed_mode = SERVO_MODE,
        .channel = channel,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = SERVO_TIMER,
        .duty = pulse_to_duty(SERVO_CENTER_US),
        .hpoint = 0,
    };

    ESP_ERROR_CHECK(
        ledc_channel_config(&config)
    );
}

// Initialize the LEDC timer and both servos.
void servos_init(void)
{
    ledc_timer_config_t timer = {
        .speed_mode = SERVO_MODE,
        .duty_resolution = SERVO_RESOLUTION,
        .timer_num = SERVO_TIMER,
        .freq_hz = SERVO_FREQ_HZ,
        .clk_cfg = LEDC_AUTO_CLK,
    };

    ESP_ERROR_CHECK(
        ledc_timer_config(&timer)
    );

    servo_init(
        PAN_GPIO,
        PAN_CHANNEL
    );

    servo_init(
        TILT_GPIO,
        TILT_CHANNEL
    );

    servo_set_pulse(
        SERVO_AXIS_PAN,
        SERVO_CENTER_US
    );

    servo_set_pulse(
        SERVO_AXIS_TILT,
        SERVO_CENTER_US
    );

    printf("PAN/TILT servos initialized.\n");
}
