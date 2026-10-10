# Chapter 1 — Circuit Abstractions and Basic Elements

**Status:** In progress; this is **not** a claim that I have completed the entire chapter.

**Reference:** Anant Agarwal and Jeffrey H. Lang, *Foundations of Analog and Digital Electronic Circuits* (2005), associated with MIT 6.002 (*Circuits and Electronics*).

These are original study notes in my own words, linked to my experiments. They are not a reproduction of the textbook.

## 1. Why do we use a circuit abstraction?

Real electronic devices are governed by electromagnetic fields. Nevertheless, when the physical dimensions and operating conditions make distributed effects negligible, many practical circuits can be represented by a network of **lumped elements** connected by ideal wires. This makes it possible to reason about circuit behavior in terms of voltages and currents rather than the full electromagnetic field everywhere.

Key quantities:

- **Electric current** $i = dq/dt$: the rate at which charge passes a point, in amperes (A).
- **Voltage**: electric potential difference between two nodes, in volts (V).
- **Terminal**: a connection point through which an element interacts with the rest of a circuit.
- **Node**: a group of points modeled as electrically connected by ideal conductors.

**Model limitations:** At sufficiently high frequencies or for long wires, effects such as propagation delay, parasitic capacitance, and inductance may matter. The lumped-element model is an approximation with a range of validity, not a universal description.

## 2. Two-terminal elements and sign conventions

A two-terminal element can be described by a relationship between the voltage across its terminals and the current through it. Assigning reference directions matters: negative values are meaningful and indicate a direction opposite to the chosen reference.

For a passive element under the **passive sign convention**, $p=vi$ is the power absorbed by that element.

## 3. Resistors and Ohm's law

For an ideal ohmic resistor:

$$
V = IR
$$

where $V$ is the voltage across the resistor, $I$ is the current through it, and $R$ is its resistance in ohms (Ω).

Rearranging the equation gives:

$$
I = \frac{V}{R}, \qquad R = \frac{V}{I}.
$$

A nominal 1 kΩ resistor supplied with 4.91 V should carry approximately $4.91\text{ mA}$, provided there are no additional series resistances or significant meter effects.

The [basic measurement experiment](../../experiments/01-measurements.md) tested resistance, continuity, voltage, and a first attempt at current measurement.

![Resistor package used in the experiments](../../photos/images/IMG_7663.jpg)

## 4. Short circuits, open circuits, and breadboard nodes

- **Ideal short circuit:** two points are connected with negligible resistance, so the voltage between them is approximately zero.
- **Ideal open circuit:** a broken current path, so current through that path is zero.

I tested the breadboard with a multimeter. Within a numbered row on the same side of the center gap, holes are electrically connected. Across the center gap, corresponding row numbers are not connected. This is a simple physical demonstration of what a **node** is.

![EIC-801 breadboard](../../photos/images/IMG_7666.jpg)

## 5. Connecting theory to larger circuits

The hands-on exercises also introduced circuit relationships that I am studying alongside the textbook:

- **Series resistors:** the same current flows through each resistor; the voltage drops add. See [Experiment 02](../../experiments/02-series-circuits.md).
- **Parallel resistors:** each branch shares the same terminal voltage; branch currents add. See [Experiment 03](../../experiments/03-parallel-circuits.md).
- **Kirchhoff's laws:** they help constrain currents at nodes (KCL) and voltage changes around closed loops (KVL).

These experiments are organized for practical learning rather than to claim they exactly match the textbook's chapter order.

## Questions to investigate next

- What quantitative conditions determine when the lumped-circuit approximation is justified?
- How much of a measured deviation comes from resistor tolerance, source variation, probe contact, or the meter itself?
- How does the circuit change when we add a capacitor and consider **time-dependent** behavior?

**Next reading:** Continue Chapter 1, including the discussion of signals.
