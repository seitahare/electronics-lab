# Experiment 03 — Parallel Circuits and Current Division

**Date:** October 10–11, 2026  
**Topics:** Parallel equivalent resistance, branch currents, and Kirchhoff's Current Law (KCL)

## Objective

Connect two nominal 1 kΩ resistors in parallel, measure their equivalent resistance and individual branch currents, and compare the results with circuit-theory predictions.

## Circuit model

	                 +----[ 1 kΩ ] R1----+
	Arduino 5 V -----+                    +----- Arduino GND
	                 +----[ 1 kΩ ] R2----+

The voltage is common to both branches. The total current equals the sum of the two branch currents.

![Two-resistor breadboard setup](../photos/images/IMG_7702.jpg)

## Predictions

For two ideal 1 kΩ resistors:

$$
\frac{1}{R_{\mathrm{eq}}}=\frac{1}{R_1}+\frac{1}{R_2}
$$

$$
R_{\mathrm{eq}} = 500\ \Omega
$$

With a supply of approximately 4.9 V:

$$
I_1 \approx I_2 \approx 4.9\ \mathrm{mA}, \qquad I_{\mathrm{total}} \approx 9.8\ \mathrm{mA}.
$$

## Measured results

| Quantity | Predicted | Measured |
| --- | ---: | ---: |
| Voltage across the parallel network | ≈ 4.9 V | **4.90 V** |
| Equivalent resistance, **power disconnected** | 500 Ω | **490 Ω** |
| Total supply current | ≈ 9.8 mA | **9.68 mA** |
| Current through upper resistor branch | ≈ 4.9 mA | **4.89 mA** |
| Current through lower resistor branch | ≈ 4.9 mA | **4.88 mA** |

**Important:** These were sequential measurements; the same circuit was rewired between some measurements. This is not a simultaneous measurement of all three currents.

## KCL check

Kirchhoff's Current Law states that current entering a junction equals the current leaving that junction:

$$
I_{\mathrm{total}} = I_1 + I_2.
$$

Adding the two independently measured branch currents:

$$
4.89 + 4.88 = 9.77\ \mathrm{mA}.
$$

The difference from the earlier total-current reading is:

$$
9.77 - 9.68 = 0.09\ \mathrm{mA},
$$

or approximately **0.9% of the recorded total current**. The results are consistent with KCL within the limitations of this simple experiment; they are not evidence that KCL itself is violated.

## How the current was measured

To measure total current, the ammeter was inserted in series **before the current split**. To measure one branch, the meter was inserted only in that branch, while the other resistor remained connected to the supply.

One arrangement used separate breadboard rows for the branches: the 5 V connection was at row 10, one resistor was connected from row 10 to row 20, and the other from row 12 to row 20. The ammeter bridged rows 10 and 12 to close the second branch. For the next branch measurement, the power and probe polarity were moved so the ammeter instead lay in series with the other resistor.

<div align="center">
<img src="../photos/images/IMG_7704.jpg" alt="Current-measurement circuit iteration" width="48%" />
<img src="../photos/images/IMG_7705.jpg" alt="Reconfigured circuit for branch-current measurement" width="48%" />
</div>

## Troubleshooting: One wrong hole

One attempt initially produced no useful current reading. The resistor leg had been inserted into **E21 instead of E20**. Breadboard row 21 is not electrically connected to row 20, so this accidentally opened the intended circuit. Moving the leg to row 20 restored the path and enabled the **4.89 mA** reading.

Additional measurement difficulties came from making contact between hand-held probes and exposed jumper-wire ends.

**Lesson:** A circuit should be analyzed as a set of **electrical nodes**, not as a picture of neighboring holes. A one-row placement error can completely change the circuit topology.

## Safety and measurement integrity

- Disconnect USB power and remove the supply connections before measuring equivalent resistance.
- Disconnect power before rewiring current-measurement branches.
- The ammeter belongs **in series** with the intended branch. Never connect it directly across 5 V and GND.
- Use stable electrical contacts and, where possible, record source voltage at the time of each current measurement.

Additional wiring iterations are preserved in the [photo gallery](../photos/README.md).
