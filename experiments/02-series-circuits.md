# Experiment 02 — Series Circuits and Voltage Division

**Date:** October 10–11, 2026  
**Topics:** Equivalent resistance, voltage division, and Kirchhoff's Voltage Law (KVL)

## Objective

Build two-resistor series circuits and test whether the same current passes through both resistors and whether their voltage drops add up to the supply voltage.

## Setup A — 1 kΩ + 1 kΩ

The circuit can be modeled as:

	Arduino 5 V
	    |
	  [1 kΩ] R1
	    |
	  node between resistors
	    |
	  [1 kΩ] R2
	    |
	Arduino GND

For a supply near 4.9 V:

$$
R_{\mathrm{eq}} = R_1 + R_2 = 2\ \mathrm{k}\Omega
$$

$$
I_{\mathrm{predicted}} = \frac{4.9\ \mathrm{V}}{2\ \mathrm{k}\Omega} \approx 2.45\ \mathrm{mA}
$$

| Quantity | Predicted | Measured |
| --- | ---: | ---: |
| Current through the series path | ≈ 2.45 mA | **2.41 mA** |
| Voltage across R1 | ≈ 2.45 V | **2.45 V** |
| Voltage across R2 | ≈ 2.45 V | **2.44 V** |
| Sum of two voltage readings | ≈ 4.90 V | **4.89 V** |

![Two-resistor breadboard construction](../photos/images/IMG_7696.jpg)

## Setup B — 1 kΩ + 10 kΩ

The resistors were replaced with different values to test how the voltage division ratio changes.

$$
R_{\mathrm{eq}} = 1\ \mathrm{k}\Omega + 10\ \mathrm{k}\Omega = 11\ \mathrm{k}\Omega
$$

With a supply of approximately 4.9 V, the predicted current is about 0.445 mA. The expected voltage drops are approximately 0.45 V and 4.45 V, respectively.

| Quantity | Predicted | Measured |
| --- | ---: | ---: |
| Voltage across the 1 kΩ resistor | ≈ 0.45 V | **0.42 V** |
| Voltage across the 10 kΩ resistor | ≈ 4.45 V | **4.46 V** |
| Sum of two voltage readings | ≈ 4.90 V | **4.88 V** |

![1 kΩ and 10 kΩ resistor setup](../photos/images/IMG_7697.jpg)

## Interpretation: Voltage division and KVL

In a series path, the current is common to all elements. From $V=IR$, a resistor with greater resistance has a larger voltage drop when the current is the same:

$$
V_1 = V_{\mathrm{s}} \frac{R_1}{R_1+R_2},\qquad
V_2 = V_{\mathrm{s}} \frac{R_2}{R_1+R_2}.
$$

Both experiments produced voltage sums close to the approximately 4.9 V source voltage, consistent with **Kirchhoff's Voltage Law**:

$$
V_{\mathrm{s}}-V_1-V_2=0.
$$

The mismatch in the 0.42 V reading cannot be assigned to one cause using the available measurements alone. Possible factors include actual component values, supply variations between readings, and probe contact.

## Lessons learned

- **Series** is a property of how components connect, not how they look on a breadboard.
- To measure voltage across an individual resistor in a series circuit, the **voltmeter** still connects in parallel with that resistor.
- The sum 4.89 V in Setup A and 4.88 V in Setup B was **calculated by adding two separate readings**, not by directly measuring the supply at the same instant.
