# Experiment 10 — HC-SR04 Ultrasonic Distance Measurement

**Date documented:** 2026-10-20  
**Test date:** By 2026-10-19 (exact session date not preserved)  
**Status:** Completed — retrospective record; original numerical readings and source file were not archived

## Objective

Use the HC-SR04 ultrasonic distance module to obtain a distance estimate from the round-trip echo time.

## Reference / theory

The ultrasonic signal travels to the target and back. With an assumed sound speed \(v\) [m/s] and measured round-trip interval \(t\) [s], the estimated one-way distance is \(d = vt/2\) [m]. The factor of two is needed because the path includes the outgoing and returning sound. A typical assumed sound speed of 343 m/s near room temperature is a model input, **not a value measured in this session**.

## Equipment

- Arduino UNO R4 Minima
- HC-SR04 ultrasonic sensor
- EIC-801 solderless breadboard and jumper wires
- USB power and Arduino IDE

## Circuit

The HC-SR04 uses VCC, GND, TRIG, and ECHO. The exact tested pin allocation was not saved, so this record intentionally provides **no inferred GPIO numbers**. On a future 3.3 V ESP32 experiment, a 5 V ECHO output must be divided or level-shifted before reaching the MCU GPIO.

## Experimental procedure

The surviving record supports only a high-level reconstruction:

1. The HC-SR04 was connected to the Arduino UNO R4 Minima and powered for a basic ranging exercise.
2. A program triggered the sensor and converted an echo interval into a distance estimate.
3. Target-responsive distance behavior was sufficient to mark the exercise completed in the learning roadmap.

The original GPIO assignment, source code, serial output, target placement, and step-by-step bench notes were not retained. They are intentionally not reconstructed here.

## Predictions

In the usable range, longer echo duration should correspond to larger target distance. Surface orientation, absorption, temperature, and missing echoes introduce limitations.

## Measurements and observations

| Quantity or event | Prediction | Observation | Source / limitation |
| --- | --- | --- | --- |
| Basic ultrasonic distance exercise | Distance estimate responds to a target | **Marked completed** in the user's experiment roadmap | Retrospective progress report |
| Echo duration [µs] | Depends on target distance | **Not retained** | No numerical values invented |
| Estimated target distance [cm] | \(vt/2\) | **Not retained** | No accuracy claim possible |
| Wiring / GPIO numbers | Connected per sensor pinout | **Not retained** | Must be rechecked to reproduce |

## Photos

No verified Experiment 10 photograph is archived in this update.

## Analysis

This was the introductory range-sensing experiment before using distance to command a servo (Experiment 11). Completion is recorded, but quantitative accuracy and repeatability cannot be reconstructed from the available notes.

## Troubleshooting

No detailed failure or repair sequence was retained for this experiment. A repeat should begin by verifying VCC, GND, TRIG, ECHO, and the tested GPIO mapping. If the sensor is moved to a 3.3 V controller, the ECHO voltage must also be checked before connection.

## Lessons learned

- Do not confuse theoretical assumed sound speed with an observed measurement.
- A completion record without the original sketch or numerical readings is not enough for later accuracy or repeatability analysis.
- The round-trip echo path requires the factor of two in the distance calculation.

## Next steps

- Repeat the experiment with a documented GPIO map and known target distances.
- Save the tested sketch, raw echo duration, calculated distance, and environmental assumptions.
- Continue to [Experiment 11](11-distance-servo-control.md), which uses distance as a servo-control input.
