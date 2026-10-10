# 1.5 — Practical Two-Terminal Elements

**Reading:** Agarwal & Lang, Chapter 1, §1.5 (printed pp. 15–29).  
**Status:** Studied, including §§1.5.1–1.5.3.

A **two-terminal element** connects to its environment through two terminals forming one **port**. Two fundamental real-world examples are batteries and resistors. This section also establishes how to assign signs to terminal variables and power.

## 1.5.1 — Batteries

### Three properties of a real battery

At the introductory circuit level, the textbook identifies three especially useful battery specifications:

1. **Nominal voltage** (V): the approximate potential difference delivered by the electrochemical system.
2. **Stored energy** (J or Wh): the total energy available under specified conditions.
3. **Internal resistance** (Ω): a factor that makes terminal voltage depend on load current.

This subsection begins by neglecting internal resistance; §1.7 restores it in a more realistic model.

### Power is a rate; energy is an accumulated quantity

If a source provides voltage $V$ while delivering positive current $I$ **out of its positive terminal**, the magnitude of power delivered is

$$P_{\mathrm{delivered}}=VI.$$

Its energy delivery is the integral of power:

$$W=\int_{t_1}^{t_2}P(t)\,dt.$$

If power is constant,

$$W=PT.$$

Units tell an important story:

- $1\,\mathrm{W}=1\,\mathrm{J/s}$.
- $1\,\mathrm{Wh}=3600\,\mathrm{J}$.
- $1\,\mathrm{A\cdot h}=3600\,\mathrm{C}$, a charge-capacity unit, **not automatically an energy unit**.

If terminal voltage remains approximately constant, I can convert a battery rating to energy using

$$E_{\mathrm{Wh}}\approx V_{\mathrm{nominal}}\,Q_{\mathrm{Ah}}.$$

**Original worked example:** a nominal $3.7\,\mathrm{V}$, $2.0\,\mathrm{Ah}$ cell corresponds to approximately

$$E\approx3.7\times2.0=7.4\,\mathrm{Wh} \approx 26{,}640\,\mathrm{J}.$$

The conversion assumes nominal voltage adequately approximates voltage during discharge; usable energy depends on conditions, chemistry, temperature, and cutoff limits.

### Series and parallel batteries

**Series cells:** their voltages add when their polarities are oriented consistently. The same branch current must pass through each cell. Cell imbalance must be considered in real packs.

**Parallel cells:** their voltages are constrained to be approximately equal. Parallel connection increases available capacity/current capability in a properly designed pack, but directly joining cells with different terminal voltages can cause dangerously large circulating currents.

These relationships are conceptual, **not instructions to construct battery packs**. My lab used the Arduino's low-voltage power output rather than joining battery cells.

## 1.5.2 — Linear Resistors

### Ohm's law and its domain

Over a suitable operating range, a linear resistor has a current–voltage relationship

$$v=iR.$$

A **linear, time-invariant** resistor has constant $R$. Linear does not necessarily imply time-invariant: the book notes that resistance can vary with temperature, even while a linear relation describes its behavior at each instant under appropriate assumptions.

For a nominal $1\,\mathrm{k\Omega}$ load with $v=4.90\,\mathrm{V}$,

$$i=\frac{4.90}{1000}=4.90\,\mathrm{mA}.$$

This is a **prediction**. Real readings should be recorded separately with the test configuration.

### From material and geometry to resistance

For a uniform conductor of length $\ell$, cross-sectional area $A$, and resistivity $\rho$:

$$\boxed{R=\rho\frac{\ell}{A}}$$

with SI units $\rho$ in $\Omega\cdot\mathrm{m}$, $\ell$ in m, and $A$ in $\mathrm{m^2}$.

Consequences of the model (same material, temperature, and cross-section assumptions):

- Doubling length approximately doubles resistance.
- Doubling cross-sectional area approximately halves resistance.
- For a circular wire, $A=\pi r^2$; doubling its radius makes area four times larger and resistance one-fourth as large.

For a rectangular conductor with width $w$ and thickness $h$:

$$R=\rho\frac{\ell}{wh}.$$

The physical explanation is that a longer conducting path creates more resistance while a larger cross-section offers more area for current to pass.

### Sheet resistance (planar resistors)

When a rectangular film has **uniform thickness** $h$, the expression can be regrouped:

$$
R=\left(\frac{\rho}{h}\right)\frac{\ell}{w}.
$$

Define sheet resistance

$$R_{\square}=\frac{\rho}{h}\qquad\text{(ohms per square, }\Omega/\square\text{)}.$$

Then

$$\boxed{R=R_{\square}\frac{\ell}{w}}.$$

For any square-shaped piece of the same uniform film, $\ell/w=1$, so its resistance between opposite full-width edges is $R_{\square}$. Different-sized squares of that same film share this resistance under the simplified geometric model.

**Original example:** A rectangular film with $R_{\square}=150\,\Omega/\square$, length $\ell=12\,\mathrm{mm}$, and width $w=3\,\mathrm{mm}$ has

$$R=150\times\frac{12}{3}=600\,\Omega.$$

The ratio $\ell/w$ is dimensionless, and the physical dimensions must use matching units. This abstraction helps explain how integrated circuits can define resistor ratios through layout geometry.

### Resistance ratios and geometric scaling

For two rectangular films made in the same process (same $\rho$ and $h$),

$$
\frac{R_1}{R_2}=\frac{\ell_1/w_1}{\ell_2/w_2}.
$$

This ratio does not require knowing $\rho$ or $h$ separately. If both in-plane dimensions of each resistor change by the *same* factor, its $\ell/w$ stays constant. Even under a broader uniform process scaling, common changes can cancel from the **ratio** of two resistor values. The key is **relative geometry**, not claiming every individual resistance remains unchanged under every manufacturing change.

### Open and short circuits as limiting cases

| Element | Terminal relation | Resistor analogy |
| --- | --- | --- |
| Open circuit | $i=0$ for any finite $v$ | $R\rightarrow\infty$ |
| Short circuit / ideal wire | $v=0$ for any finite $i$ | $R\rightarrow0$ |

For ideal open and short elements, $p=vi=0$. In practice, contact resistance, leakage, and insulation breakdown are reasons not to treat these ideals as exact physical statements.

### General resistors, not just fixed ohmic components

The book uses **general resistor** for an element whose *instantaneous* terminal current and voltage are related algebraically. The relationship may be nonlinear or time varying. A capacitor or inductor is not a general resistor in this sense because its defining terminal relationship introduces time integration/differentiation and stored energy.

This is a modeling classification, not a claim that all “resistors” in the general mathematical sense look like the physical resistors in my parts box.

## 1.5.3 — Associated Variables Convention

### Picking a reference polarity and current direction

To use voltage and current signs consistently, choose the current reference arrow **into the terminal labeled positive** for the element voltage:

```text
                  +             −
       i  ──────→ o──[ element ]─o
                  <----- v ----->
```

The diagram defines positive reference directions. Actual voltage and current can each be negative.

The textbook calls this the **associated variables convention**. Many modern courses also call it the **passive sign convention**.

### Why negative quantities are useful

Suppose I define $i$ from left to right, but the physical current is $2\,\mathrm{mA}$ from right to left. My answer is simply

$$i=-2\,\mathrm{mA}.$$

I do not need to redraw the circuit. Likewise, a $-3\,\mathrm{V}$ value means the actual terminal polarity is opposite to the reference chosen for $v$.

### Absorbed versus delivered power

With the associated-variables convention,

$$\boxed{p_{\mathrm{absorbed}}=vi}.$$

- $p>0$: the element absorbs power.
- $p<0$: the element delivers power to the rest of the circuit.

For a positive resistor $R$,

$$p=i^2R=\frac{v^2}{R}\ge0.$$

A normal ideal passive resistor dissipates energy; it does not generate it.

**Original example:** A resistor has terminal references $v=-2.0\,\mathrm{V}$ and $i=-1.0\,\mathrm{mA}$. Then

$$p=(-2.0)(-0.001)=+2.0\,\mathrm{mW}.$$

The negatives are not a paradox. Both reference directions were opposite to the physical directions, and the resistor still **absorbs** power.

For a source, power can be negative under the same reference convention. For example, $v=5\,\mathrm{V}$ and $i=-10\,\mathrm{mA}$ imply $p=-50\,\mathrm{mW}$, or $50\,\mathrm{mW}$ delivered.

### Energy over time

The energy absorbed between two instants is

$$\boxed{w_{\mathrm{absorbed}}=\int_{t_1}^{t_2}v(t)i(t)\,dt}.$$

For constant absorbed power $P$, this simplifies to $w=P(t_2-t_1)$.

### Power-rating check for my bench setup

A nominal $1\,\mathrm{k\Omega}$ resistor across $4.90\,\mathrm{V}$ dissipates approximately

$$
P=\frac{(4.90)^2}{1000}=0.02401\,\mathrm{W}\approx24\,\mathrm{mW}.
$$

This is **below** the nominal $0.25\,\mathrm{W}$ rating of the 1-kΩ parts used in this experiment (assuming the component rating and ordinary operating conditions are applicable). This is a calculated safety check, not a thermal measurement.

For perspective, increasing voltage across a fixed resistor raises power *quadratically*:

$$P\propto V^2\quad\text{at fixed }R.$$

## Connection to my experiments

![The resistor package](../../../photos/images/IMG_7663.jpg)

![Multimeter used for measurements](../../../photos/images/IMG_7664.jpg)

- [Experiment 01 — resistance, continuity, and basic electrical quantities](../../../experiments/01-measurements.md)
- [Experiment 02 — voltage division in series circuits](../../../experiments/02-series-circuits.md)

The measured $1\,\mathrm{k\Omega}$ resistor was approximately $1.000\,\mathrm{k\Omega}$; the $10\,\mathrm{k\Omega}$ resistor was approximately $10.00\,\mathrm{k\Omega}$ in the meter ranges used. These checks connect component labels to the resistance model, but they do not independently measure resistivity or sheet resistance.

## Check my understanding

1. How are ampere-hours and watt-hours related, and what extra assumption is required to convert between them?
2. How does resistor geometry appear in $R=\rho\ell/A$?
3. Why does the ratio of two same-process planar resistors depend on $\ell/w$?
4. What is the meaning of $p=vi<0$ with the associated-variables convention?
5. Why is a battery's nominal voltage not always its loaded terminal voltage?

**Working conclusion:** A physical component is characterized by terminal behavior, material constraints, and energy transfer. Reference signs are part of the analysis, not properties imposed by nature.

[← §1.4](04-limitations.md) · [Chapter 1 index](../chapter-01.md) · [Next: §1.6 →](06-ideal-two-terminal-elements.md)
