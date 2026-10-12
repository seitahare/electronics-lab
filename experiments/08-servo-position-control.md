# Experiment 08 — SG90 Servo Position Control with External Power

**Date:** 2026-10-12 to 2026-10-13 (session across midnight)  
**Status:** Completed (servo shaft rotation confirmed; commanded angles not independently measured)

## Objective

Power an SG90 hobby servo from a separate regulated 5 V supply and command several target positions from an Arduino UNO R4 Minima, while correctly sharing the signal ground.

## Reference / theory

A hobby position servo uses repeated control pulses to represent a requested position. The Arduino Servo library generates the pulses and provides a high-level angle interface. This differs from the LED experiment, where `analogWrite()` adjusted brightness by changing a PWM duty cycle. The exact shaft travel and pulse-width-to-angle calibration depend on the servo and were **not measured** in this experiment.

## Equipment

- Arduino UNO R4 Minima, powered by the Mac via USB
- SG90-class micro servo (nominally a small 5 V-class hobby servo)
- ADAPTER TECH ATS012S-W050U AC adapter, labeled **DC 5 V, 2 A**, center positive
- DC-barrel-jack-to-screw-terminal adapter with marked positive and negative terminals
- EIC-801 breadboard, jumper wires, screw driver
- MAS-838 multimeter, **DC voltage / 20 V range**
- White plastic servo horn and fastening screw

## Circuit

```text
Mac USB ------ Arduino UNO R4 Minima
                   D9  ---------------- SG90 signal wire (yellow/orange)
                   GND ----+
                           |
External PSU (-) ----------+------ SG90 ground wire (brown)
External PSU (+5 V) --------------- SG90 supply wire (red)
```

The servo's **red lead is not powered from Arduino's 5 V pin**. The external supply feeds the servo directly. A separate connection joins Arduino GND, servo GND, and supply negative at one breadboard row. The 5 V supply node is kept separate from the shared GND and from Arduino's 5 V rail.

Initial assembly used direct jumpers into the SG90's female three-position connector. The wiring was then arranged to share a single ground node on the breadboard. Power was disconnected during rewiring.

## Predictions

- The regulated adapter should produce about **5 V DC**, positive relative to its marked negative output, when unloaded.
- With the control wire on D9 and a common ground, commanding `30`, `90`, `150`, then `90` should cause the servo to move among several distinct shaft positions.
- Each command is followed by a **1,500 ms** pause in the program, so each target should be held for approximately 1.5 seconds before the next command.

## Measurements and observations

| Quantity / event | Expected | Observation | Instrument / context |
| --- | --- | --- | --- |
| Adapter output voltage | Approximately +5 V | **+5.12 V** | MAS-838, DC 20 V, external PSU positive-to-negative; measured before loading with servo |
| Adapter rated capacity | 5 V, 2 A | **5 V, 2 A** on label | Manufacturer label, not a measured current |
| Initial multi-position servo program | Shaft moves between commanded positions | **Rotation confirmed by user** | Visual observation/video |
| Horn attached | Rotation becomes easier to see | White servo horn fitted; movement observed | Visual observation |
| Exact shaft angles | 30° / 90° / 150° targets | **Not measured** | No angle scale or encoder test |

The **+5.12 V** reading is a measured no-load voltage and should not be reported as the voltage across the servo during motion.

## Arduino code

[08-servo-sweep.ino](../sketches/08-servo-sweep/08-servo-sweep.ino)

- `#include <Servo.h>` makes the Servo library declarations available.
- `Servo myServo;` creates a servo-control object.
- `myServo.attach(9);` sets the servo signal connection to D9.
- `myServo.write(angle);` requests a target shaft position.
- `delay(1500);` holds the current request for approximately 1.5 seconds.

## Photos

![Servo power components arranged for the experiment](../photos/images/IMG_7756.jpg)
![Rated output and polarity printed on the AC adapter](../photos/images/IMG_7757.jpg)
![Polarity markings on the DC screw-terminal adapter](../photos/images/IMG_7758.jpg)
![Green and yellow leads inserted into DC screw-terminal adapter](../photos/images/IMG_7761.jpg)
![Arduino, servo, external supply and common-ground breadboard node](../photos/images/IMG_7765.jpg)
![Servo horn attached to the SG90 shaft](../photos/images/IMG_7768.jpg)

A selected video-frame montage is available in the [photo gallery](../photos/README.md).

## Analysis

The control program and verified ground-sharing arrangement produced visible servo motion. The main engineering milestone was separating **motor power** from **microcontroller control** while preserving a common ground reference. This general wiring pattern will be useful for additional actuators.

Because there was no protractor or feedback encoder measurement, reported degrees are **commanded target angles**, not confirmed actual mechanical angles.

## Mistakes, safety, and next improvements

- Terminal markings and positive meter polarity were checked rather than assuming the wire colors alone proved polarity.
- Fasten screw-terminal connections securely; keep exposed conductors apart and disconnect **both USB and AC power** before rewiring.
- Avoid powering the servo through Arduino's 5 V pin for this experiment; keep the external supply's +5 V disconnected from Arduino's +5 V rail.
- Observe for sustained buzzing, stalls, or overheating and disconnect the external adapter if these occur.
- Next: control target positions with a two-lead pushbutton and test stateful toggling.
