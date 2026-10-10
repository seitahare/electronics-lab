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

**Experiment dates:** October 10–11, 2026. Values are transcribed from readings observed during the experiments; calculations and measurements are labeled separately. Some measurements were affected by unstable probe contact.

## Photo documentation

All **29 photographs** from these experiments are available in the [photo gallery](photos/README.md) and on the [one-page overview](photos/overview.jpg). The experiment notes also link directly to photographs of the relevant equipment and circuit iterations. Photographs show the actual bench setups, including intermediate and occasionally incorrect wiring configurations; they should be used alongside the verified schematic, not as unqualified wiring instructions.

<div align="center">
<img src="photos/images/IMG_7669.jpg" alt="Arduino UNO R4 Minima" width="31%" />
<img src="photos/images/IMG_7697.jpg" alt="Series circuit with a 1 kΩ and a 10 kΩ resistor" width="31%" />
<img src="photos/images/IMG_7702.jpg" alt="Two-resistor breadboard arrangement" width="31%" />
</div>

## Equipment

- Arduino UNO R4 Minima, powered via USB and used as an approximately 5 V supply
- EIC-801 solderless breadboard and jumper wires
- MASTECH MAS-838 digital multimeter
- Discrete resistors, primarily 1 kΩ and 10 kΩ

## Engineering workflow

1. **Model:** Identify nodes, elements, and assumptions.
2. **Predict:** Use equations to estimate voltage, current, and resistance.
3. **Build:** Assemble the circuit and verify connections before applying power.
4. **Measure:** Record actual readings with their units and measurement configuration.
5. **Investigate:** Compare prediction and observation, including wiring mistakes and sources of uncertainty.
6. **Document:** Preserve diagrams, values, photos, and what I learned.

A reusable [experiment template](templates/experiment-template.md) keeps future entries consistent.

## Next topics

Capacitors and diodes → transistors, MOSFETs, and operational amplifiers → Arduino I/O → sensors → servo/motor control → custom circuits → robotics.

## Safety notes

- Disconnect power before making wiring changes and before measuring resistance or continuity.
- Connect a voltmeter **in parallel** with the component being measured.
- Insert an ammeter **in series** with the branch being measured; never connect an ammeter directly across the supply's 5 V and GND terminals.
- Confirm multimeter input jacks and ranges before reconnecting power.
