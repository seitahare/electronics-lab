# Experiment 06 — Two-Lead Button and Digital Input

**Date:** 2026-10-12  
**Status:** In progress — circuit and code prepared; press-to-LED correspondence awaits an explicit retest

## Objective

Read a pushbutton on Arduino digital pin D2 and use the reading to control the external red LED on D8. Learn about `digitalRead()` and the microcontroller's internal pull-up resistor.

## Reference / theory

A digital input needs a defined voltage when a switch is open. `INPUT_PULLUP` enables an internal resistor pulling D2 HIGH when unpressed. When the switch closes between D2 and GND, the input reads LOW. In this circuit, **LOW means pressed**, which is the opposite of a naive HIGH-equals-pressed assumption.

## Equipment

- Arduino UNO R4 Minima and USB-connected Mac
- Arduino IDE 2.3.10
- Two-lead momentary pushbutton with relatively wide, flat leads
- Two male-to-female jumper wires for the button
- Existing 1 kΩ resistor, red LED, and breadboard

## Circuit

```text
OUTPUT: Arduino D8 ---[1 kΩ]--- LED (+) |>| LED (-) --- GND
INPUT:  Arduino D2 ---[normally open pushbutton]--- GND
```

One button lead connects to D2, and the other connects to the breadboard GND node used by the LED. No external pull-up resistor is needed for the D2 input because the internal pull-up is enabled.

The switch's flat metal leads were too wide to insert comfortably into the solderless breadboard, so **male-to-female jumpers** were used instead of forcing the leads into the breadboard contacts.

![Two-lead pushbutton](../photos/images/IMG_7748.jpg)

![Male-to-female jumper wire set](../photos/images/IMG_7750.jpg)

![Arduino, LED, and two-lead switch wiring](../photos/images/IMG_7751.jpg)

## Predictions

| Button | D2 with `INPUT_PULLUP` | Expected LED at D8 |
| --- | --- | --- |
| Released (open) | HIGH | OFF |
| Pressed (closed to GND) | LOW | ON |

## Arduino sketch

```cpp
const int ledPin = 8;
const int buttonPin = 2;

void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }
}
```

## Observations

- The button was identified as a **two-lead** part rather than the initially assumed four-lead tact switch.
- The flat contacts did not fit the breadboard easily. The user found the already-purchased blue male-to-female jumper wires, and these did fit onto the switch leads.
- The switch was wired toward D2 and the existing GND node, while the LED output circuit remained on D8. Exact header seating could not be verified from the wide photo alone.
- The Arduino IDE reported **successful compilation** of the sketch, followed by an upload error:

```text
dfu-util: No DFU capable USB device available
Failed uploading: uploading error: exit status 74
```

- The subsequent video shows the LED illuminated in some frames and not illuminated in others. However, the frames do not independently establish **whether button press/release caused the changes** or whether the new sketch successfully uploaded. This remains an **unconfirmed functional outcome**.

![Selected frames from the follow-up test video](../photos/images/switch-test-frames.jpg)

## Analysis

The input/output logic is straightforward: `digitalRead(D2)` produces HIGH or LOW, and the program maps that input to `digitalWrite(D8)`. The pull-up resistor provides a defined idle state even when the pushbutton is open.

The `dfu-util` message is an **upload/USB discovery problem, not a source-code compilation error**. It does not by itself prove that the sketch was installed. Reconnecting USB and selecting the correct UNO R4 Minima port are reasonable troubleshooting steps.

## Mistakes, safety, and next improvements

- Do not force oversized component leads into breadboard contacts; use properly fitting connectors or an appropriate mounting method.
- Disconnect USB power before rewiring the switch.
- Confirm D2 and GND physically, then verify the sketch's upload success.
- **Next session:** observe at least two clear button-pressed and button-released transitions. The expected result is **ON only while pressed**.
- Following this verification: vary LED brightness with PWM and eventually drive a servo motor.
