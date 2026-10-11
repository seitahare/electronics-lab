# Experiment 05 — LED Current Limiting and Arduino Blink

**Date:** 2026-10-12  
**Status:** Completed

## Objective

Light an external LED from a current-limited DC supply, then replace the fixed supply connection with an Arduino GPIO output and make the LED blink under program control.

## Reference / theory

An LED conducts primarily in one direction. A resistor in series limits the current. With a nominal 4.90 V supply and 1 kΩ resistance, the upper-bound estimate ignoring the LED voltage drop would be $4.90\ \mathrm{mA}$. The actual current is lower because the LED has a forward voltage; current through this LED was **not measured** in this experiment.

A digital output set to `HIGH` provides a logic-high voltage; `LOW` brings it near 0 V. The Arduino sketch uses these states to control a physical LED.

## Equipment

- Arduino UNO R4 Minima with USB connection to a Mac
- EIC-801 breadboard and jumper wires
- Red LED, with polarity checked before power-on
- Nominal 1 kΩ current-limiting resistor
- Arduino IDE 2.3.10, Arduino UNO R4 board support

## Circuit

### Manual, always-on LED

```text
Arduino 5 V ---[1 kΩ]--- LED anode (+) |>| cathode (-) --- Arduino GND
```

The resistor joined breadboard rows 10 and 15, the LED occupied rows 15 (+) and 16 (-), and Arduino GND connected to row 16. The long and short LED leads were checked for polarity.

![Red LED illuminated with the series resistor](../photos/images/IMG_7741.jpg)

### Program-controlled LED

The 5 V supply lead was removed from the circuit and replaced by digital **D8**. The LED and its 1 kΩ resistor remained in series, with the other side connected to GND.

```text
Arduino D8 ---[1 kΩ]--- LED anode (+) |>| cathode (-) --- Arduino GND
```

![D8 connection at the Arduino header](../photos/images/IMG_7742.jpg)

## Predictions

- With a fixed supply and correctly oriented LED, the LED should remain lit.
- With D8 configured as an output and the program below, the LED should alternate **on for 1 s** and **off for 1 s**.

## Arduino sketch

```cpp
void setup()
{
    pinMode(8, OUTPUT);
}

void loop()
{
    digitalWrite(8, HIGH);
    delay(1000);

    digitalWrite(8, LOW);
    delay(1000);
}
```

The `setup()` function configures D8 once at startup. The `loop()` function repeats indefinitely. `delay(1000)` waits approximately 1000 ms.

## Measurements and observations

| Event | Prediction | Observation |
| --- | --- | --- |
| 5 V-powered, resistor-limited LED | Steady illumination | **Red LED illuminated steadily** |
| Code compilation | Successful build | **Succeeded** in Arduino IDE |
| Sketch upload | Target accepts the binary | IDE output showed **`Download done.`** and **`Done!`** |
| D8-driven blink | 1 s on, 1 s off | **LED visibly blinked** in a short video; exact intervals were not instrumented |

![Successful sketch upload in Arduino IDE](../photos/images/arduino-upload-success.jpg)

![Selected video frames showing the LED blinking](../photos/images/led-blink-frames.jpg)

## Analysis

This was the first experiment in this lab that combined a C/C++-style program, GPIO configuration, and an external circuit. The LED's state was controlled by output voltage from D8, rather than by manually connecting and disconnecting power.

The blinking video confirms visible switching; the exact 1 s timing was specified by the code, not independently measured.

## Mistakes, safety, and next improvements

- Keep the current-limiting resistor in series with the LED; do not connect the LED directly across a 5 V supply.
- Turn off USB power before moving the wire from 5 V to D8.
- Keep disconnected jumper-wire ends from touching adjacent terminals or conductive objects.
- Next: read a physical button on a separate GPIO pin and choose the LED output state accordingly.
