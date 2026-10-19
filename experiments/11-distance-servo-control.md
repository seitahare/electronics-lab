# Experiment 11 — Distance-Dependent SG90 Servo Control

**Date documented:** 2026-10-20  
**Test date:** By 2026-10-19 (exact session date not preserved)  
**Status:** Completed — retrospective record; original thresholds, angles, and sketch were not archived

## Objective

Use the HC-SR04 distance input to choose a target position for an SG90 servo.

## Reference / theory

First estimate target distance from the ultrasonic pulse's round-trip delay, \(d=vt/2\). A program maps that estimate to a requested servo angle or category. The servo's shaft position was **not measured by an encoder**, so this is sensor-driven actuation rather than measured-angle feedback control.

## Equipment

- Arduino UNO R4 Minima and Arduino IDE
- HC-SR04 ultrasonic sensor
- SG90 servo motor
- Nominal 5 V / 2 A external adapter and DC jack/screw-terminal converter (servo power method used in Experiment 08)
- EIC-801 breadboard, wires, USB host

## Circuit

~~~text
HC-SR04 TRIG/ECHO ---- microcontroller ---- SG90 signal
external +5 V ----------------------------- SG90 supply (red)
external GND ------------------------------ SG90 ground (brown)
microcontroller GND ----------------------- shared external ground
~~~

This is a functional diagram, **not a recovered pin-by-pin wiring diagram**. The original threshold distances and servo target angles were not preserved. Keep external 5 V away from 3.3 V GPIO and the MCU's 3V3 node.

## Experimental procedure

The retained record supports the following functional sequence, but not exact pin numbers or constants:

1. The HC-SR04 supplied a distance estimate to the microcontroller.
2. The program classified or mapped that estimate to an SG90 target position.
3. The servo used the external-power and shared-ground arrangement established in Experiment 08.
4. Distance-responsive servo behavior was sufficient to mark the roadmap exercise completed.

The original threshold distances, commanded angles, sketch, and serial readings were not retained and are not recreated here.

## Predictions

If the sensor gives different distance readings and the mapping has multiple outputs, the servo should visibly change position when a target is moved. Specific thresholds and output angles cannot be predicted without the original code.

## Measurements and observations

| Test | Expected | Observation | Evidence / limitation |
| --- | --- | --- | --- |
| Distance-responsive servo | Servo changes target when distance changes | **Marked completed** in the user's roadmap | Retrospective report |
| Distance thresholds | Code-defined [cm] | **Not retained** | Values not inferred |
| Requested servo angles | Code-defined [degrees] | **Not retained** | No source recovered |
| Actual shaft angle | Near requested target | **Not measured** | No protractor/encoder test |

## Photos

No verified Experiment 11 photograph is archived in this update.

## Analysis

This combines the distance sensor from Experiment 10 with the externally powered SG90 wiring established in Experiments 08–09. The observed completion indicates the exercise was carried out, but the surviving record is insufficient for a quantitative calibration or exact code reproduction.

## Troubleshooting

No detailed troubleshooting log was retained. A rebuild should verify the sensor pin map, distance output, threshold decisions, servo signal connection, separate motor supply, and common ground one stage at a time.

## Lessons learned

- Sensor-driven actuation combines a measurement model with a software mapping; both must be preserved to reproduce the behavior.
- Commanded servo targets are not measured shaft angles.
- Separate motor power still requires a common signal ground.

## Next steps

- Repeat the experiment while recording GPIO assignments, thresholds, requested angles, and representative distance readings.
- Disconnect both power sources before rewiring, and condition the HC-SR04 ECHO line before using a 3.3 V controller if it produces 5 V logic.
- Continue to [Experiment 12](12-imu-acceleration-gyroscope.md), which introduces a six-axis IMU over I²C.
