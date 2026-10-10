# 1.8 — Signal Representation (Introduction Only)

**Reading:** Agarwal & Lang, Chapter 1, §1.8, *opening discussion* (printed pp. 40–41).  
**Status:** **Introduction reached; §1.8.1 and §1.8.2 not yet studied.**

## Why discuss signals after elements?

Previous sections established that a lumped circuit can be described in terms of element-terminal **voltages** and **currents**. This section begins connecting those electrical quantities to the physical things we care about:

- **Energy:** supplying energy, transferring it through a system, and converting or dissipating it.
- **Information:** representing measurements or messages so they can be communicated, transformed, stored, or computed with.

Electronic circuits process both, often simultaneously.

## Voltage and current are signals

A voltage or current can carry a useful physical quantity. Examples of connections I want to investigate later:

- A microphone may create an electrical voltage representing sound.
- A sensor may produce a voltage or current related to a measured physical variable.
- A power circuit may use voltage and current primarily to transfer energy to a load.

The crucial perspective shift is that $v(t)$ and $i(t)$ are not merely symbols in Ohm's law; they are also the **signals a circuit operates on**.

## The same electrical interface can serve different purposes

Consider two abstract tasks:

| Task | Signal at the circuit interface | What matters |
| --- | --- | --- |
| Powering a resistive load | Supply voltage and load current | Current, dissipated power, delivered energy |
| Reading a sensor | Output voltage or current representing a changing quantity | How faithfully that signal represents the information |

In both cases, the terminal quantities are voltages and currents. What differs is the function assigned to those signals and the performance criteria of the circuit.

## Progress boundary: do not pretend later sections are complete

The next textbook subsection is **§1.8.1 — Analog Signals**. It introduces specific time-varying signal shapes and concepts. **That subsection has not yet been covered in these study sessions**. After that comes §1.8.2, the digital-signal discussion, which is also still pending.

I will add detailed notes for both only after studying them, instead of summarizing unread material and marking it complete.

## Bridge to my longer-term projects

This theme helps connect basic circuits with planned sensor and embedded-system work. A robot receives information from sensors and uses circuits to act on that information, while power circuits supply energy to processors and actuators. Understanding which quantities are modeled as signals is a necessary step toward that system-level design.

These are **motivation and forward-looking applications**, not a claim that I have built or characterized those systems already.

## Questions to carry into §1.8.1

1. What makes a signal an *analog* signal?
2. How can information be expressed through a changing voltage or current?
3. Which properties of a signal matter for an electronic system to recover its information reliably?

**Next reading:** **§1.8.1 — Analog Signals**. Start there in the next textbook session.

[← §1.7](07-modeling-physical-elements.md) · [Chapter 1 index](../chapter-01.md)
