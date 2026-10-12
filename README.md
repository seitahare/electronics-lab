# Electronics Lab

**Studying circuits, building them, measuring what actually happens, and documenting the difference.**

This repository is my independent electronics engineering notebook. I study circuit theory using an MIT-associated textbook, then build small circuits on a breadboard to test predictions with a multimeter. Over time, I hope to apply the same approach to embedded systems, sensors, motor control, custom circuit boards, and robotics.

<img src="photos/images/IMG_7705.jpg" alt="Two-resistor breadboard experiment" width="520" />

## Learning resources

**Primary textbook:** Anant Agarwal and Jeffrey H. Lang, *Foundations of Analog and Digital Electronic Circuits* (2005), a textbook associated with MIT's **6.002 — Circuits and Electronics**.

- [Chapter 1 — Circuit abstractions and elementary components (in progress)](study-notes/foundations-of-circuits/chapter-01.md)
- The goal is to explain each idea in my own words, derive useful relationships, and connect the theory to measurements.

> This is an independent study project. It is **not** an official MIT project, course enrollment record, credential, or endorsement. Textbook passages and diagrams are not reproduced here.

## Hands-on experiments

| Experiment | Topic | Selected measurements |
| --- | --- | --- |
| [01 — Basic measurements](experiments/01-measurements.md) | Resistance, breadboard continuity, voltage, current | 1 kΩ resistor ≈ 1.000 kΩ; Arduino supply ≈ 4.91 V |
| [02 — Series circuits](experiments/02-series-circuits.md) | Voltage division and Kirchhoff's Voltage Law (KVL) | Equal resistors: 2.45 V and 2.44 V; current: 2.41 mA |
| [03 — Parallel circuits](experiments/03-parallel-circuits.md) | Equivalent resistance and Kirchhoff's Current Law (KCL) | 490 Ω equivalent resistance; 9.68 mA total; 4.89 mA and 4.88 mA branch currents |
| [04 — RC charging and discharging](experiments/04-rc-charging-discharging.md) | Time constant, capacitor polarity, charge/discharge paths | 4.90 V measured supply; qualitative voltage rise; discharge reading reached 0 V |
| [05 — LED and Arduino blink](experiments/05-led-blink.md) | LED polarity, current limiting, GPIO output and timed blinking | Red LED lit; sketch uploaded; visible 1 s on/off sequence programmed |
| [06 — Button and digital input](experiments/06-button-digital-input.md) | `INPUT_PULLUP`, `digitalRead()`, two-lead switch wiring | Circuit and sketch prepared; upload error observed; press-to-light response pending verification |
| [07 — PWM LED brightness](experiments/07-pwm-led-voltage.md) | PWM duty cycle, LED fade, D9-to-GND DC voltage | `128`: **2.40 V**; `64`: **1.20 V**; calculated comparisons **2.46 V / 1.23 V** |
| [08 — Servo position control](experiments/08-servo-position-control.md) | External motor power, common GND, Servo library | External supply: **+5.12 V** unloaded; SG90 visibly moved among requested positions |
| [09 — Button-controlled servo](experiments/09-button-servo-toggle.md) | `INPUT_PULLUP`, state variables, debounce and toggle | Button-controlled motion and press-to-toggle behavior confirmed; angles not independently measured |

**Experiment dates:** October 10–13, 2026. Values are transcribed from readings observed during the experiments; calculations and measurements are labeled separately. Some measurements were affected by unstable probe contact. Experiment 06 remains in progress with respect to its original LED press-to-light trial; the same style of switch input was successfully demonstrated later in Experiment 09.

## Photo documentation

**50 photographs and other images** from these experiments are available in the [photo gallery](photos/README.md); the [one-page overview](photos/overview.jpg) still covers the first 29 photos. Media include video-frame montages, wiring photographs, power-supply polarity markings, and an Arduino IDE screenshot. The experiment notes also link directly to photographs of the relevant equipment and circuit iterations. Photographs show the actual bench setups, including intermediate and occasionally incorrect wiring configurations; they should be used alongside the verified schematic, not as unqualified wiring instructions.

<div align="center">
<img src="photos/images/IMG_7669.jpg" alt="Arduino UNO R4 Minima" width="31%" />
<img src="photos/images/IMG_7697.jpg" alt="Series circuit with a 1 kΩ and a 10 kΩ resistor" width="31%" />
<img src="photos/images/IMG_7702.jpg" alt="Two-resistor breadboard arrangement" width="31%" />
</div>

## Equipment

- Arduino UNO R4 Minima, powered via USB and used as an approximately 5 V supply
- EIC-801 solderless breadboard and jumper wires
- MASTECH MAS-838 digital multimeter
- Discrete resistors, primarily 1 kΩ, 10 kΩ, and 100 kΩ
- 100 µF polarized electrolytic capacitor, LED, and two-lead pushbutton
- Arduino IDE for code upload and GPIO experiments
- SG90 servo motor, servo horn, 5 V / 2 A external adapter, and DC jack/screw-terminal converter

## Engineering workflow

1. **Model:** Identify nodes, elements, and assumptions.
2. **Predict:** Use equations to estimate voltage, current, and resistance.
3. **Build:** Assemble the circuit and verify connections before applying power.
4. **Measure:** Record actual readings with their units and measurement configuration.
5. **Investigate:** Compare prediction and observation, including wiring mistakes and sources of uncertainty.
6. **Document:** Preserve diagrams, values, photos, and what I learned.

A reusable [experiment template](templates/experiment-template.md) keeps future entries consistent.

## Arduino sketches

Reproducible Arduino IDE sketches for Experiments 07–09 are in [`sketches/`](sketches/), with a separate folder for each buildable `.ino` sketch. The relevant experiment pages explain the wiring, measured results, and limitations.

## Next topics

HC-SR04 ultrasonic distance measurement → distance-driven servo target selection → IMU-based orientation measurements → I²C/OLED readout → multi-component robot mechanisms. Revisit non-blocking `millis()`-based switch debouncing and continue deeper capacitor, diode, transistor, MOSFET, and operational-amplifier theory alongside practical experiments.

## Safety notes

- Disconnect power before making wiring changes and before measuring resistance or continuity.
- Connect a voltmeter **in parallel** with the component being measured.
- Insert an ammeter **in series** with the branch being measured; never connect an ammeter directly across the supply's 5 V and GND terminals.
- Confirm multimeter input jacks and ranges before reconnecting power.
- Check LED and electrolytic-capacitor polarity and use a current-limiting resistor for the LED.
- Use properly fitting connectors; do not force wide component leads into breadboard sockets.
- When using external motor supplies, verify polarity with a voltmeter, share the signal ground, and **do not connect the separate supply's +5 V to Arduino's 5 V rail**.
- Power down both the USB-powered Arduino and external motor adapter before changing servo wiring.
