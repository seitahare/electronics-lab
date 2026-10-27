#ifndef SERVO_H
#define SERVO_H

#include <stdint.h>

// Safe pulse range verified in the current setup.
#define SERVO_MIN_US     1450U
#define SERVO_CENTER_US  1500U
#define SERVO_MAX_US     1550U
#define SERVO_STEP_US    10U

// Servo axes.
typedef enum {
    SERVO_AXIS_PAN,
    SERVO_AXIS_TILT
} servo_axis_t;

// Initialize PWM and both servo channels.
void servos_init(void);

// Apply a pulse width to the selected servo.
void servo_set_pulse(
    servo_axis_t axis,
    uint32_t pulse_us
);

#endif
