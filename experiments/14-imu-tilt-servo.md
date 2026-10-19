# Experiment 14 — IMU Tilt-Controlled SG90 Servo

**Date:** 2026-10-19  
**Status:** Completed — tilt-linked servo rotation confirmed during the bench test

## Objective

Estimate tilt from the LSM6DSV16X IMU's acceleration readings and command an externally powered SG90 servo to follow the orientation.

## Reference / theory

The test calculated the angle around the IMU X axis using \(\theta = \operatorname{atan2}(a_y,a_z)\times 180/\pi\) [degrees]. It smoothed that estimate with a first-order low-pass filter: \(\theta_f=0.85\theta_{f,previous}+0.15\theta_{current}\). The target servo position was computed as \(90 + \theta_f \times 60/45\) [degrees] then clamped to the 30°–150° command interval.

This is a **mapping from observed acceleration to a servo target**, not a measured-angle feedback loop. Accelerometer-only tilt may be distorted by linear acceleration and may wrap near ±180°.

## Equipment

- XIAO ESP32S3 Sense
- AE-LSM6DSV16X IMU, two nominal 10 kΩ I²C pull-ups
- SG90 servo and separate nominal 5 V / 2 A adapter
- DC jack/screw-terminal converter, breadboard, jumper wires
- Arduino IDE with ESP32 3.x PWM interface

## Circuit

~~~text
XIAO 3V3 ------------ IMU 3V3
XIAO GND ------------ IMU GND
XIAO D4 / GPIO5 ----- IMU SDA -- [10 kΩ] -- 3V3
XIAO D5 / GPIO6 ----- IMU SCL -- [10 kΩ] -- 3V3
XIAO GND ------------ IMU SA0 (I²C address 0x6A)

XIAO D2 / GPIO3 ----- SG90 orange signal
external +5 V ------- SG90 red lead
external GND -------- SG90 brown lead
XIAO GND ------------ external GND (shared ground)
~~~

External +5 V never connects to XIAO's 3V3 pin. The earlier +5.12 V no-load meter reading from Experiment 08 is **not** a new loaded voltage measurement for this experiment.

## Experimental procedure

1. Reconnect the verified IMU circuit at I²C address `0x6A`.
2. Connect the SG90 signal to XIAO D2/GPIO3 while powering the servo from the separate nominal 5 V supply.
3. Join the XIAO and external-supply grounds without connecting external +5 V to XIAO 3V3.
4. Confirm `WHO_AM_I = 0x70`, configure the accelerometer, and start the 50 Hz servo PWM output.
5. Calculate X-axis tilt from `atan2(ay, az)`, apply the first-order filter, map the result into the 30°–150° command range, and move the IMU slowly.
6. Observe whether the servo horn moves with changes in sensor orientation.

## Predictions

With slow sensor movement, tilt and servo target should change together. Example *programmed* mapping: -45° tilt → 30° target, 0° tilt → 90° target, +45° tilt → 150° target. Actual horn angle was not independently measured.

## Measurements and observations

| Check | Expected | Observation | Evidence / limitation |
| --- | --- | --- | --- |
| Servo responds to IMU | Visible coordinated motion | **Servo moved in sync with IMU tilt** | Direct bench observation |
| Control pulse repetition | 50 Hz requested | **50 Hz PWM set in code** | Not checked by oscilloscope |
| Servo command boundaries | 30°–150° | **Programmed bounds** | Shaft degrees not measured |
| Actual tilt-to-angle numerical trace | Serial output updates | **Not retained** | Qualitative movement verified instead |
| Servo supply under load | Nominal 5 V | **Not measured during motion** | Adapter is rated 5 V / 2 A |

## Arduino code

[14-imu-tilt-servo.ino](../sketches/14-imu-tilt-servo/14-imu-tilt-servo.ino) — transcribed from the session code confirmed to move the servo.

## Photos

No sanitized image of the moving servo was provided for this record.

## Troubleshooting

No separate failure sequence was retained for this experiment. The working setup depended on two previously verified conditions: the repaired IMU I²C bus from Experiment 12 and the external-power/common-ground servo arrangement from Experiment 08. If the system is rebuilt, those subsystems should be tested independently before combining them.

## Analysis

This test combined the functional IMU from Experiment 12 with externally powered servo output previously established in Experiment 08. The visible coupling is an initial embedded sensing/actuation milestone. It does not establish stable PID control, sensor fusion, shaft-angle accuracy or servo torque.

## Lessons learned

- Common ground is required for the external-powered servo's signal reference.
- Accelerometer-only tilt is useful for slow orientation changes but is not full inertial navigation.
- Programmed 50 Hz PWM and angle limits are configuration values, not oscilloscope or shaft-angle measurements.
- Testing sensor input and actuator output separately reduces ambiguity when integrating them.

## Next steps

- Disconnect USB and the external adapter before rewiring, and avoid servo stalls or binding.
- Record a numerical tilt/target trace and compare commanded target with measured horn angle.
- Add gyroscope-assisted filtering if dynamic motion becomes important.
- Continue to [Experiment 15](15-esp32-wireless.md), then integrate sensing, display, actuation, and communication.
