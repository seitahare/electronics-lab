# 1.2 — The Lumped Circuit Abstraction

**Reading:** Agarwal & Lang, Chapter 1, §1.2 (printed pp. 5–9).  
**Status:** Studied.

## From an object to a circuit element

The textbook motivates the abstraction with a battery powering a lightbulb. A full electromagnetic analysis of the bulb, wires, and battery would be cumbersome if the only questions are the overall current or power.

Instead, I can replace the physical objects with terminal models:

```text
         ┌────────[ R (bulb model) ]────────┐
         │                                  │
         └────────( V source )──────────────┘
```

The resistor is a **model of the bulb's electrical behavior**, not a claim that the bulb is literally a fixed resistor under all conditions. In a real filament, resistance can change substantially with temperature.

## Two-terminal black box

A lumped two-terminal element exposes two electrical terminals. Its internal construction is hidden; what matters to the surrounding circuit is the **terminal voltage** and **terminal current**.

```text
        i →       ┌──────────────┐
       + o────────│   element    │────────o −
          v       └──────────────┘
```

The `+` and `−` marks define the *chosen reference polarity* for $v$, not necessarily the actual polarity. The arrow defines the *chosen positive direction* for $i$. A negative numerical result later tells me that the physical direction or polarity is opposite to the reference.

A circuit model needs an **element law** that relates the terminal variables. For an ideal linear resistor:

$$v=iR.$$

Consequently, if $R$ is constant,

$$i=\frac{v}{R}.$$

For other elements, $v/i$ need not be constant, so a single constant resistance is not a universal description.

## Ideal wires and circuit topology

When a wire is ideal, it has zero voltage drop no matter what current passes through it. Therefore:

- All points along one uninterrupted ideal wire have the same potential.
- The drawing's *shape* is often irrelevant; electrical connectivity (topology) is what matters.
- Two wires that cross in a sketch are **not** automatically connected; schematic conventions and junction marks matter.

In the breadboard, holes A10–E10 lie within one connected strip, but A10 and F10 are separated by the center gap. That physical structure determines whether two leads belong to the same electrical node.

![Breadboard used to test connectivity](../../../photos/images/IMG_7666.jpg)

The model becomes wrong if I accidentally insert a lead into E21 when the intended node is row 20. That is a wiring/connectivity error, not a violation of Ohm's law.

## The full abstraction is more than Ohm's law

The circuit abstraction combines:

1. Lumped elements, with defined terminal voltages and currents.
2. Element-specific relationships between those variables.
3. Ideal wires that connect the element terminals.
4. Assumptions that prevent appreciable external field coupling and distributed propagation effects.

The next section makes those assumptions precise. The important insight is that *elements only interact through their terminals* in this model. If magnetic or electric fields make two apparently separate elements interact directly, their independent models may need to be changed or combined.

## What the model can and cannot answer

| Question | A source–resistor model can answer? |
| --- | --- |
| Approximate load current at a specified voltage | Yes, if the chosen resistance is valid |
| Approximate power in the resistor | Yes, using $p=vi$ |
| Exact filament temperature distribution | No |
| Battery chemistry and remaining lifetime | Not with an ideal voltage source alone |
| Effect of a long cable at very high frequency | Not without a richer model |

## Connection to my lab

The measured Arduino supply was approximately $4.91\,\mathrm{V}$. The predicted current through one nominal $1\,\mathrm{k\Omega}$ resistor was about $4.91\,\mathrm{mA}$. My first direct current measurement had unreliable probe contact, so I treated the result as uncertain rather than redefining the resistor model to fit it.

- [Experiment 01: voltage and current measurement](../../../experiments/01-measurements.md)
- [Experiment 03: why correct branch connections matter](../../../experiments/03-parallel-circuits.md)

## Check my understanding

1. What information is visible at a lumped element's terminals?
2. Why is the shape of an ideal wire usually irrelevant to simple circuit analysis?
3. What changed when I moved the misplaced resistor lead from row 21 to row 20?

**Working conclusion:** A circuit schematic is a compact model of terminal behavior and connectivity; its usefulness depends on both the element laws and the assumptions behind them.

[← §1.1](01-power-of-abstraction.md) · [Chapter 1 index](../chapter-01.md) · [Next: §1.3 →](03-lumped-matter-discipline.md)
