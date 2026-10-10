# 1.7 — Modeling Physical Elements

**Reading:** Agarwal & Lang, Chapter 1, §1.7 (printed pp. 36–40).  
**Status:** Studied.

## A model is a choice about which effects to retain

Section 1.6 defined ideal elements. Section 1.7 applies them to real devices by combining primitives to reproduce the behavior that matters for a specific analysis.

The goal is not to construct the most detailed imaginable description. It is to find a model that is **simple enough to understand** and **accurate enough for its intended use**.

## Model A — A physical wire

An ideal wire has $v=0$. A real copper wire has nonzero resistance and can heat up.

For simple low-frequency analysis, a physical wire can be modeled as

```text
physical wire ≈ ideal conductor + series resistor r_wire
```

The model predicts a voltage drop

$$v_{\mathrm{wire}}=i\,r_{\mathrm{wire}}$$

and power dissipated as heat

$$p_{\mathrm{wire}}=i^2r_{\mathrm{wire}}.$$

But a constant small resistor does not reproduce arbitrary temperature rise, melting, corrosion, skin effect, or failure. If those phenomena matter, the model needs to change.

## Model B — A physical battery

A useful improvement over the ideal constant-voltage source is an **ideal source $V_0$ in series with internal resistance $r$**:

```text
           r (internal resistance)
    + ───[ r ]─────────o── positive output
         ideal V0
    − ──────────────────o── negative output
```

For **positive current $I_{\mathrm{out}}$ delivered out of the battery's positive terminal**, the load terminal voltage is

$$\boxed{V_{\mathrm{terminal}}=V_0-I_{\mathrm{out}}r}.$$

The minus sign matters: the terminal voltage *falls* with increasing discharge current.

The textbook uses the **associated variables** reference direction for its detailed battery characteristic. If the terminal current $i$ is instead defined **into** the positive terminal (charging direction), it writes the equivalent form

$$\boxed{v_t=V_0+i r}.$$

There is no contradiction: $i=-I_{\mathrm{out}}$ when comparing the same physical situation.

### Original numerical example

Let $V_0=5.0\,\mathrm{V}$, $r=0.50\,\Omega$, and $I_{\mathrm{out}}=0.20\,\mathrm{A}$. Then

$$V_{\mathrm{terminal}}=5.0-(0.20)(0.50)=4.90\,\mathrm{V}.$$

This demonstrates load-dependent voltage sag. It is **not** an identification of the actual resistance or circuitry inside my Arduino power supply: those values were chosen for illustration.

### What does the model still omit?

- Battery voltage changing with state of charge.
- Nonlinear electrochemical behavior and temperature dependence.
- Capacity reduction with heavy loads.
- Dynamic behavior and degradation with age.

Adding one resistor captures one effect—voltage drop with load—not the complete device.

## Model C — A microphone or sensor

The book considers a microphone whose terminal signal falls when connected to a load. A basic model is a **time-varying ideal voltage source** in series with an internal resistance.

```text
signal source v_s(t) ──[ r_internal ]── output / load
```

This highlights that circuit models can describe **information processing** as well as energy delivery. A sensor has an electrical output, and the device receiving the signal can influence the measurable output through loading.

A simple resistance may be insufficient if the response depends strongly on signal frequency or other internal dynamics.

## Checking an element model with current–voltage data

The basic idea is to apply multiple operating conditions and record pairs of terminal measurements $(v,i)$:

- **Ideal resistor:** linear $i=v/R$ relationship passing through the origin.
- **Source with series resistance:** approximately linear relation with a nonzero open-circuit voltage and a slope set by internal resistance.
- **Heated resistor:** measured resistance may change as temperature changes; its curve may depart from a constant-$R$ straight line.

The textbook discusses experimental $v$–$i$ plots and explains that physically real components may be adequately modeled over a **limited operating region**. It also ties resistor validity to maximum power dissipation and notes frequency-dependent departures caused by unmodeled capacitance and inductance.

### Open-circuit voltage and short-circuit current

For the source-plus-resistor model, under the discharge-current convention:

$$V_t=V_0-I_{\mathrm{out}}r.$$

- At $I_{\mathrm{out}}=0$, $V_t=V_0$: **open-circuit voltage**.
- Mathematically setting $V_t=0$ gives $I_{\mathrm{sc}}=V_0/r$: **predicted short-circuit current in the linear model**.

The latter is a model extrapolation. **Do not test it by shorting a battery or a power supply**; real short-circuit behavior can be hazardous and the constant-$r$ approximation may fail at high currents.

## Why “simple but useful” matters

Increasing model detail can improve numerical accuracy while making it harder to see *why* the circuit behaves as it does. The textbook emphasizes using appropriately simple circuit models to gain insight, while acknowledging that a more detailed computation may be needed for high accuracy.

This is an engineering trade-off:

1. Ask the question (current? voltage sag? heating? signal timing?).
2. Identify the effects that could meaningfully change the answer.
3. Choose the simplest model retaining those effects.
4. Predict a measurable result.
5. Compare with the real device and refine only when needed.

## My own experiment as a modeling exercise

The Arduino 5 V pin measured approximately $4.91\,\mathrm{V}$ during my basic checks. It is tempting to draw it as a perfect 5 V ideal source, but the measured output alone does **not** characterize its current-dependent voltage, internal resistance, noise, or regulator design.

For the early resistor experiments, an approximately constant low-voltage source was an adequate first approximation. Deviations between predicted and measured current can also arise from resistor tolerance, wiring, or how the meter was inserted into the branch.

In the parallel experiment:

| Quantity | Observation |
| --- | ---: |
| Nominal supply voltage across the parallel network | $4.90\,\mathrm{V}$ |
| Total current | $9.68\,\mathrm{mA}$ |
| First branch current | $4.89\,\mathrm{mA}$ |
| Second branch current | $4.88\,\mathrm{mA}$ |

The branch readings sum to $9.77\,\mathrm{mA}$, a $0.09\,\mathrm{mA}$ difference from the separately measured total. This is consistent with modest changes in setup/contact conditions between measurements. It **does not independently identify** which device or connection caused the difference.

![Reconfigured branch-current circuit](../../../photos/images/IMG_7705.jpg)

See the [parallel-circuit experiment](../../../experiments/03-parallel-circuits.md) for measured versus theoretical values and the row-21 connection error.

## Questions to investigate with future instruments

- How much does the Arduino 5 V output change over a defined range of safe load currents?
- What is the burden voltage of the multimeter when measuring current?
- At what applied power does a given physical resistor depart noticeably from its room-temperature resistance?

These are **future investigation ideas**, not experiments already performed.

**Working conclusion:** Circuit modeling is iterative: choose an abstraction, check it against evidence, and extend it only as the engineering question requires.

[← §1.6](06-ideal-two-terminal-elements.md) · [Chapter 1 index](../chapter-01.md) · [Next: §1.8 →](08-signal-representation-introduction.md)
