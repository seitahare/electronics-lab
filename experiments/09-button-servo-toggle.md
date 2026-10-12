# Experiment 09 — Pushbutton-Controlled Servo and Stateful Toggle

**Date:** 2026-10-13  
**Status:** Completed (user confirmed both button-controlled movement and press-to-toggle behavior)

## Objective

Use a momentary pushbutton as a digital input to command servo positions. Extend the simple hold-to-move behavior into a **press-to-toggle state machine** that retains its angle after the button is released.

## Reference / theory

With `INPUT_PULLUP` enabled, Arduino D2 normally reads HIGH. Pressing the button connects D2 to shared GND, causing a LOW reading. The `Servo` object's `write()` method then receives a desired target angle.

Two input behaviors were tested:

1. **Level-controlled:** when pressed, request 90°; when released, request 30°.
2. **Event-style toggle:** start at 30°; each distinct button press toggles the requested angle between 30° and 90°; releasing the button does not undo the change.

The toggle stores software state in a `bool` variable. A 30 ms delay and a wait-until-release loop are used as a simple **debounce** strategy. The implementation is blocking and is not a fully characterized debounce circuit or timing algorithm.

## Equipment

- Arduino UNO R4 Minima, USB power and Arduino IDE
- SG90 servo with a white plastic servo horn
- External 5 V / 2 A supply, barrel-jack adapter and common-ground jumper wiring, as in Experiment 08
- Two-lead momentary pushbutton with male-to-female jumper wires
- EIC-801 breadboard for the common-ground node

## Circuit

```text
Arduino D9 ----------- SG90 signal (yellow/orange)
External +5 V -------- SG90 red power wire
Shared GND ----------- SG90 brown ground wire
                      |
Arduino GND ----------+
                      |
Arduino D2 --[button]-+
```

The button connects **D2 to common GND when pressed**. The servo signal and motor supply remain separate, and Arduino's 5 V output is **not connected** to the external supply's +5 V node. No separate external resistor is needed for D2 because the MCU's internal pull-up resistor is enabled.

## Predictions

| Test | Button condition | Programmed target angle |
| --- | --- | ---: |
| Hold-to-move | Released | 30° |
| Hold-to-move | Pressed | 90° |
| Toggle | Initial state (`is90 = false`) | 30° |
| Toggle | First completed press | 90° |
| Toggle | Second completed press | 30° |
| Toggle | Third completed press | 90° |

## Measurements and observations

| Observation | Result | Evidence / limitation |
| --- | --- | --- |
| Servo reacts to pushbutton | **Confirmed** | Video showed a change in visible horn orientation associated with the button test; user confirmed operation |
| Toggle behavior | **Confirmed by user** | User reported the press-to-toggle program working; no quantitative timing / angular calibration recorded |
| Target angle accuracy | **Not measured** | Only commanded 30° and 90° values are known |
| Bounce rate / debounce reliability | **Not measured** | Delays were chosen heuristically (30 ms) |

## Arduino code

- [09-servo-button-hold.ino](../sketches/09-servo-button-hold/09-servo-button-hold.ino) — 30° released / 90° pressed.
- [09-servo-button-toggle.ino](../sketches/09-servo-button-toggle/09-servo-button-toggle.ino) — alternating targets on successive presses.

### Line-by-line concepts in the toggle sketch

| Expression | Role |
| --- | --- |
| `#include <Servo.h>` | Include the Servo class declaration. |
| `Servo myServo;` | Construct the servo-controller object. |
| `const int servoPin = 9;` | Define the servo signal pin. |
| `const int buttonPin = 2;` | Define the input pin. |
| `bool is90 = false;` | Retain the commanded state across successive calls to `loop()`. |
| `myServo.attach(servoPin);` | Assign D9 for servo signals. |
| `pinMode(buttonPin, INPUT_PULLUP);` | Enable a stable default HIGH input. |
| `myServo.write(30);` | Set the initial target. |
| `digitalRead(buttonPin) == LOW` | Detect a pressed button. |
| `delay(30);` | Wait for contact bounce to settle before confirming the press. |
| `is90 = !is90;` | Invert the stored state exactly once per accepted press. |
| `if (is90) ... else ...` | Choose 90° or 30° from the saved state. |
| `while (digitalRead(buttonPin) == LOW)` | Prevent another toggle while the button remains held. |
| `delay(1);` | Short pause inside the release-wait loop. |
| Final `delay(30);` | Reduce false retriggers immediately after release. |

`is90` has static storage duration because it is declared outside any function. Declaring `bool is90 = false;` as an ordinary local variable inside `loop()` would reinitialize it every call and lose the stored toggle state. A function-local `static bool` would also retain state, but was not used here.

## Photos

![Selected frames from the servo pushbutton demonstration](../photos/images/servo-button-frames.jpg)

The earlier [two-lead button and jumper setup](../photos/images/IMG_7751.jpg) is documented in Experiment 06. Experiment 09 demonstrates that the button can be used as an Arduino input, although the original **LED press-to-light test** in Experiment 06 was not separately re-verified.

## Analysis

The first sketch maps a **current input level** to a target. The second uses **stored state**, a useful introductory example of finite-state behavior. The release-wait loop is a simple way to avoid multiple toggles from a long press, but it blocks other program work and may be unsuitable when multiple sensors or actuators need responsive servicing.

## Mistakes, safety, and next improvements

- `LOW` means *pressed* in this circuit because `INPUT_PULLUP` is enabled.
- A single press can produce contact bounce; the 30 ms delays are a practical approximation, not a guarantee.
- Keep external servo power separate from the Arduino 5 V rail while sharing ground; disconnect the power supplies before rewiring.
- A future revision should use **edge detection with `millis()`-based debounce** so that the loop can remain responsive.
- Next: measure distance using the HC-SR04 ultrasonic module, then use sensed distance to choose servo targets.
