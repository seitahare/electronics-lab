# 1.6 — Ideal Two-Terminal Elements

**Reading:** Agarwal & Lang, Chapter 1, §1.6 (printed pp. 29–36).  
**Status:** Studied, including §§1.6.1–1.6.3.

## Why create ideal elements?

A real battery has internal losses; a real wire has resistance; physical components behave differently outside their rated ranges. Circuit analysis becomes simpler if I first define **ideal primitives** with precise terminal relations and later combine them to model real devices.

The book motivates circuits as models for information- and energy-processing systems. A system needs ways to represent sources, transmission, losses, control, and storage. This chapter establishes source/flow/loss primitives; control and storage receive fuller treatment in later chapters.

## 1.6.1 — Ideal Voltage Sources, Wires, and Resistors

### Independent ideal voltage source

An ideal independent source imposes its specified voltage regardless of current:

$$\boxed{v=V_s(t)}.$$

For a DC source, $V_s(t)=V_s$ is constant. For a signal source the voltage may vary with time. The current is **not** determined by this source law alone; it depends on the rest of the connected circuit.

**Key distinction:** The assigned terminal variable $v$ and the source's specified value $V_s$ are not interchangeable if my voltage reference is reversed. Under the illustrated matching polarity, $v=V_s$; reversing the voltage reference gives $v=-V_s$.

**Independent** means the source's prescribed value does not depend on another electrical variable elsewhere in the circuit. A *dependent* (controlled) source is instead governed by some other circuit signal; the textbook introduces this idea here and develops examples later.

### Ideal wire / perfect conductor

$$\boxed{v=0\quad\text{for any }i}.$$

Any current allowed by the rest of the circuit may pass through the wire, but the wire contributes zero voltage drop and dissipates no power in the ideal model.

A real wire that exhibits a relevant voltage drop can be represented as an ideal wire plus a series resistance (when that is a sufficient model).

### Ideal linear resistor

$$\boxed{v=iR}.$$

The resistor voltage and current are proportional for all amplitudes in the **ideal** model; physical resistors have limits such as temperature, power rating, and breakdown.

### Conductance

The inverse of resistance is **conductance**:

$$\boxed{G=\frac1R},\qquad [G]=\mathrm{S}\;\text{(siemens)}.$$

Using conductance, Ohm's law is

$$\boxed{i=Gv}.$$

For a $1\,\mathrm{k\Omega}$ resistor,

$$G=\frac1{1000\,\Omega}=0.001\,\mathrm{S}=1\,\mathrm{mS}.$$

Conductance is particularly convenient when reasoning about parallel paths, because branch currents scale with $G$ at a shared voltage. My parallel-resistor experiments are practical extensions; the book's formal network analysis occurs later.

## 1.6.2 — Element Laws

An **element law** (also called a constituent/constitutive relation) specifies the allowed relationship between current and voltage at the element's terminals. A circuit is not completely defined by connection lines alone; it must also specify what each element does.

With the reference conventions established in §1.5, the basic laws are:

| Ideal element | Relation | What is constrained? |
| --- | --- | --- |
| Resistor | $v=iR$ | Voltage and current together |
| Voltage source | $v=V_s$ | Voltage; current depends on network |
| Short circuit | $v=0$ | Voltage; current depends on network |
| Open circuit | $i=0$ | Current; voltage depends on network |
| Current source | $i=I_s$ | Current; voltage depends on network |

### Reading the $i$–$v$ graph

If $v$ is horizontal and $i$ vertical:

- Resistor: $i=v/R$, a straight line through the origin with slope $1/R$.
- Ideal voltage source: $v=V_s$, a vertical line.
- Ideal current source: $i=I_s$, a horizontal line.
- Ideal wire: $v=0$ (vertical axis).
- Ideal open circuit: $i=0$ (horizontal axis).

This distinction is useful because a power source is **not** a resistor with some fixed ratio $v/i$. Its defining behavior is which terminal quantity it can maintain.

## 1.6.3 — The Current Source: Another Ideal Two-Terminal Element

An ideal independent current source enforces a specified current, no matter what terminal voltage results:

$$\boxed{i=I_s(t)}.$$

In a physically realizable device, the allowed terminal voltage is limited. Ideal current sources omit that limitation for analytical simplicity.

### Comparing impossible limiting conditions

- Shorting an **ideal nonzero voltage source** demands unbounded current because the ideal source insists on a voltage while an ideal short insists on zero voltage. The model has no finite solution under these contradictory constraints.
- Leaving a **nonzero ideal current source** open similarly conflicts with the open-circuit condition of zero current. The ideal model cannot sustain a physically finite voltage under that condition.

These are warnings about an idealized **model**, not suggestions to perform such tests. **Never short a real supply to see what happens.**

## The terminal-interface point of view

A complex circuit may be represented externally as a one-port or multi-port black box. An amplifier, for instance, can be described by input and output ports without reproducing its entire internal design in every higher-level diagram.

This illustrates the same abstraction principle as §1.1: the outside world needs a useful relationship between interface variables, not necessarily the internal microscopic details.

## Original worked comparison

Imagine three independent ideal two-terminal devices:

1. A $4.90\,\mathrm{V}$ voltage source connected to a $1\,\mathrm{k\Omega}$ resistor: the resistor current is predicted to be $4.90\,\mathrm{mA}$.
2. A $4.90\,\mathrm{mA}$ current source connected to a $1\,\mathrm{k\Omega}$ resistor: the resistor voltage is predicted to be $4.90\,\mathrm{V}$.
3. An ideal short: its terminal voltage is $0\,\mathrm{V}$ no matter what finite current flows as determined by a valid surrounding circuit.

Different source laws can produce the same operating point **with a particular load**, but the sources are not interchangeable under arbitrary loads.

## Connection to my experiments

- [Breadboard continuity and ideal-wire approximations](../../../experiments/01-measurements.md)
- [Equivalent resistance and conductance of parallel resistors](../../../experiments/03-parallel-circuits.md)

With two identical $1\,\mathrm{k\Omega}$ resistors in parallel, the conductances add:

$$G_{\mathrm{eq}}=1\,\mathrm{mS}+1\,\mathrm{mS}=2\,\mathrm{mS}.$$

Thus the **theoretical** equivalent resistance is $1/G_{\mathrm{eq}}=500\,\Omega$. My **measured** equivalent resistance, with power disconnected, was approximately $490\,\Omega$.

Note that the theoretical network result here is a lab connection to the concepts, not a claim that I have already read the entirety of Chapter 2.

## Check my understanding

1. Which terminal quantity does an ideal voltage source prescribe? What does it leave free?
2. What does the slope $1/R$ mean on an $i$-versus-$v$ plot?
3. Why can't an ideal source's unlimited behavior be expected from an Arduino output pin?
4. Why might a multi-terminal physical device still be modeled using combinations of two-terminal elements?

**Working conclusion:** Ideal element laws are simple, composable building blocks. Real devices are approximations to these primitives within specified ranges.

[← §1.5](05-practical-two-terminal-elements.md) · [Chapter 1 index](../chapter-01.md) · [Next: §1.7 →](07-modeling-physical-elements.md)
