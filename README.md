# Matrix Library (C++)

A C++ implementation of a matrix class with exact arithmetic based on rational numbers.

## Features
- Matrix addition, subtraction, multiplication
- REF / RREF computation
- Rank, null space, column space
- Matrix inverse and determinant
- Solving linear systems

## Project Structure
- `Matrix.hpp / Matrix.cpp` — matrix class
- `Rational.hpp / Rational.cpp` — rational number class
- `main.cpp` — simple usage example

## Notes
This project was refactored to follow standard C++ header/source separation.

## Build
```bash
g++ -std=c++17 main.cpp Matrix.cpp Rational.cpp -o matrix
./matrix
