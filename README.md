# Guessing Game Implementation in ANSI-C

Implementation of a simple guessing game in ANSI-C.

The program uses a list of "things" (in `thing_sheet`) as well as their traits to determine yes/no questions to ask. It chooses the question whose answer would give it the most information.

## Building

Use the provided makefile to build the project. `make` will build the `guesser` executable, which can be run with `./guesser`.

