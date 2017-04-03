# Assertion-structure representation of a pattern

The assertion-structure representation is a new way to represent false positive
patterns. This representation has two parts:

 1. Structure: based on the program flow graph.

 2. Assertions: conditions that must hold in various points along the program graph.

Until now we have been considering only structure for representing patterns, but
this may not be complete. Our false positive checkers have been giving some
false positive themselves. Perhaps including assertions will help us more fully
represent false positive patterns.
