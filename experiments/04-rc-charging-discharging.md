# Experiment 04 — RC Charging and Discharging

**Date:** 2026-10-12  
**Status:** Completed (qualitative observations; no timed voltage series)

## Objective

Build a resistor-capacitor (RC) circuit and observe capacitor voltage rising during charging and falling during discharge. Compare the behavior with the predicted time constant.

## Reference / theory

The RC time constant is

$$
\tau=RC.
$$

For nominal $R=100\ \mathrm{k\Omega}$ and $C=100\ \mathrm{\mu F}$,

$$
\tau=(100{,}000\ \Omega)(0.0001\ \mathrm F)=10\ \mathrm s.
$$

For an initially discharged ideal capacitor, charging follows $V_C(t)=V_s(1-e^{-t/RC})$. Discharging through a resistor follows $V_C(t)=V_C(0)e^{-t/RC}$.

## Equipment

- Arduino UNO R4 Minima, powered over USB and supplying nominal 5 V
- EIC-801 solderless breadboard and jumper wires
- 100 kΩ resistor (nominal)
- 100 µF, 25 V polarized aluminum electrolytic capacitor (nominal)
- MAS-838 digital multimeter in **DC voltage / 20 V range**

## Circuit

**Charging:**

```text
Arduino 5 V ---[100 kΩ]---+---(+) [100 µF] (-)--- Arduino GND
                         |                       |
                         +---- voltmeter (+)     +-- voltmeter (-)
```

The supply node was at breadboard row 10. The resistor joined rows 10 and 15, and the capacitor joined row 15 (+) to row 16 (-). The voltmeter measured the voltage directly across the capacitor, with positive probe at row 15 and negative probe at row 16. The stripe on the capacitor identified the negative lead.

![RC charging setup](../photos/images/IMG_7735.jpg)

**Discharging:** With USB power removed and the 5 V wire disconnected, the 100 kΩ resistor was moved to connect rows **15 and 16**, in parallel with the capacitor.

```text
row 15 (+) ---+---- (+) [100 µF] (-) ---+--- row 16 (-)
              |                        |
              +--------[100 kΩ]--------+
```

![RC discharge connection](../photos/images/IMG_7737.jpg)

## Predictions

Assuming the nominal components and a 4.90 V source, the **ideal calculated charging voltages** are:

| Time after charging begins | Predicted $V_C$ |
| --- | ---: |
| 0 s | 0.00 V |
| 10 s ($1\tau$) | 3.10 V |
| 20 s ($2\tau$) | 4.24 V |
| 30 s ($3\tau$) | 4.66 V |
| 50 s ($5\tau$) | 4.87 V |

These values are **predictions only**, not measurements recorded at those times.

## Measurements and observations

| Quantity / event | Observation | Instrument / configuration |
| --- | --- | --- |
| Arduino supply voltage | **4.90 V** | MAS-838, DC voltage |
| Initial voltage readout during faulty setup | **4.14 V**, apparently stable | MAS-838, DC voltage; invalid as a charging-curve datum because a capacitor lead was not properly connected |
| Charging after fixing the contact | Capacitor voltage **rose progressively** | MAS-838, 20 V DC range; no timed values were recorded |
| Discharge through 100 kΩ | Voltage eventually displayed **0 V** | MAS-838, DC voltage; elapsed time and display precision not recorded |

![Initial troubleshooting setup](../photos/images/IMG_7736.jpg)

## Analysis

The expected qualitative behavior was observed after correcting the contact: the capacitor voltage increased during charging and fell to a zero reading after discharging through the resistor.

The experiment did **not** measure the time constant directly. The predicted 10 s value follows from nominal $R$ and $C$, but a timed voltage log is still needed to test it quantitatively.

The first seemingly steady **4.14 V** reading was not reliable evidence of capacitor behavior. Investigation revealed that the shorter capacitor lead had not reached the breadboard contact. Meter loading was considered as an explanation, but was **not established** by the experiment.

## Mistakes, safety, and next improvements

- **Contact error:** Unequal capacitor lead lengths prevented one lead from seating. The longer lead was gently bent so both leads reached their respective contacts.
- Confirm both nodes and the capacitor's negative stripe before applying power; a visually plausible arrangement is not necessarily electrically connected.
- Disconnect USB before rewiring. Discharge the capacitor through a resistor; do not directly short its leads.
- Next time, record voltage at fixed intervals from a known initial state to compare measured data with $V_C(t)$.
