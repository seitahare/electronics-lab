# Repository Recording Rules

These instructions apply to the entire repository.

## Language and scope

- Write all study notes, experiment logs, captions, filenames, commit messages, and repository documentation in English.
- Keep explanations in the author's own words. Do not reproduce textbook passages or diagrams.
- State clearly when work is incomplete, exploratory, or not part of an official course or credential.

## Measurement integrity

- Preserve recorded measurements and experimental outcomes exactly as observed. Never adjust a value to better match theory.
- Distinguish measured values, nominal component values, predictions, and calculated results explicitly.
- Include units, instrument range or configuration when known, and relevant uncertainty such as unstable probe contact.
- If an earlier record is demonstrably wrong, retain the original value and add a dated correction explaining the evidence; do not silently replace it.
- Record failed attempts, wiring mistakes, and unexpected results when they are useful to understanding the experiment.

## Experiment records

- Base new experiment logs on `templates/experiment-template.md`.
- Give each experiment a sequential number, descriptive title, date, objective, equipment list, circuit description, predictions, measurements, analysis, mistakes, safety notes, and next steps as applicable.
- Describe electrical nodes and meter placement precisely. Treat photographs as supporting evidence, not as substitutes for a verified circuit description or schematic.
- Use ISO dates (`YYYY-MM-DD`) for new records unless a prose date is needed for readability.

## Photos and links

- Store experiment photographs in `photos/images/` and document them in `photos/README.md` with accurate English captions and alt text.
- Remove EXIF/GPS metadata from published photographs while preserving the visible experimental evidence.
- Use repository-relative links. Before committing, verify that every local Markdown link and image target exists with the exact filename and letter case.
- Do not delete or replace existing photographs or records unless the change is an explicitly documented correction.

## Repository maintenance

- Preserve the structure and content of the existing `README.md`; extend it only when new records require navigation or summary updates.
- Avoid unnecessary rewrites of existing files. Keep commits focused on the new study material or documented correction.
- Before committing, review the diff for accidental changes to dates, units, measurements, equations, and experimental conclusions.
