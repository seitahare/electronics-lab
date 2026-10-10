# Experiment 01 — Basic Measurements

**Date:** October 10–11, 2026  
**Topics:** Resistance, continuity, voltage, current, and breadboard connections

## Objective

Learn to use a digital multimeter and confirm the electrical connections of a breadboard before building more complex circuits.

## Equipment

Arduino UNO R4 Minima, MASTECH MAS-838 multimeter, EIC-801 breadboard, jumper wires, 1 kΩ and 10 kΩ resistors.

<div align="center">
<img src="../photos/images/IMG_7664.jpg" alt="Digital multimeter" width="31%" />
<img src="../photos/images/IMG_7667.jpg" alt="Jumper wires and storage box" width="31%" />
<img src="../photos/images/IMG_7669.jpg" alt="Arduino UNO R4 Minima" width="31%" />
</div>

## Observations

| Measurement | Configuration | Observed result |
| --- | --- | ---: |
| 1 kΩ resistor, removed from powered circuit | 2 kΩ resistance range | ≈ 1.000 kΩ |
| 10 kΩ resistor, removed from powered circuit | 20 kΩ resistance range | ≈ 10.00 kΩ |
| Breadboard A10 ↔ E10 | Continuity, unpowered | Beeper activated |
| Breadboard A10 ↔ F10 | Continuity, unpowered | No beep |
| Arduino 5 V ↔ GND | 20 V DC voltage range | ≈ 4.91 V |
| Voltage across a 1 kΩ load | 20 V DC voltage range | ≈ 4.9 V |
| Voltage across a 10 kΩ load | 20 V DC voltage range | ≈ 5 V |
| Current through one 1 kΩ load | 20 mA DC current range, series insertion | ≈ 3.9 mA, **unstable** |

**Note:** The approximately 3.9 mA direct-current reading was obtained while probe contact was unreliable. It should not be treated as a precise measurement.

## Measurement configurations

### Measuring voltage

The voltmeter is placed **across** the resistor:

	top node ----[ 1 kΩ ]---- bottom node
	    |                        |
	    +------[ voltmeter ]-----+

### Measuring current

The ammeter is inserted **into** the current path:

	5 V ----[ ammeter ]----[ 1 kΩ ]---- GND

The supply was provided by the Arduino's 5 V pin when USB-powered.

![Breadboard and Arduino test setup](../photos/images/IMG_7670.jpg)

![Single-resistor wiring test](../photos/images/IMG_7677.jpg)

## Prediction and interpretation

For approximately 4.91 V across a nominal 1 kΩ resistor:

$$
I = \frac{V}{R} \approx \frac{4.91\ \mathrm{V}}{1000\ \Omega} = 4.91\ \mathrm{mA}.
$$

The intermittent 3.9 mA indication is not enough to conclude that Ohm's law failed: holding the probes against loose wire ends introduced uncertainty into the circuit. Later, more stable measurements with multiple resistors produced results close to theoretical predictions.

The continuity tests confirmed that physically nearby holes are not necessarily on the same electrical node. The breadboard's middle gap separates the two sets of contacts.

## Troubleshooting and lessons learned

- Check that probe tips touch the exposed conductor, not the insulation.
- Loose hand-held probe connections can interrupt a current measurement.
- Map breadboard nodes first; do not infer connections from appearance alone.
- Never measure resistance or continuity in an energized circuit.
- Never place the meter in current mode directly across 5 V and GND.

Further images: [full photo gallery](../photos/README.md).
