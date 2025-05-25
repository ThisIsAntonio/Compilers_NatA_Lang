
# NatA Lang – Custom Language and Compiler Front-End

## Project Overview

**NatA Lang** is a domain-specific programming language designed and implemented as part of the CST8152 - Compilers course at Algonquin College (Fall 2023). The language and its compiler front-end were developed collaboratively by Marcos Antonio Astudillo C. and David Burchat. The project aims to demonstrate core compiler construction concepts across three main stages: **Reader (Buffer)**, **Scanner (Lexical Analyzer)**, and **Parser (Syntax Analyzer)**.

## Language Overview

NatA is inspired by the syntax and semantics of Go and C-style languages, targeting readability and minimalism for educational purposes. It includes support for:
- Variable declarations and arithmetic operations
- Control flow (`if`, `else`, `while`, `for`)
- Input/output operations
- Functions and return types
- Built-in datatypes like `int`, `float64`, `string`, and `byte`

## File Structure

```
NatA_Lang/
│
├── input/                  # Sample NatA source files (.nat)
├── Compilers.c/h          # Main definitions shared across Reader, Scanner, Parser
├── Reader.c/h             # Reader (buffer) implementation
├── MainReader.c           # Entry point for Reader testing
├── Scanner.c/h            # Lexical analyzer
├── MainScanner.c          # Entry point for Scanner testing
├── Parser.c/h             # Syntax analyzer
├── MainParser.c           # Entry point for Parser testing
├── Runner.bat             # Windows batch file to run test cases
├── CMakeLists.txt         # Build system configuration
└── CMakePresets.json      # Preset configurations for CMake
```

## How to Build and Run

### Requirements
- **C Compiler** (GCC or MSVC)
- **CMake** (3.20 or higher recommended)
- **Windows (preferred)** or any system supporting standard C

### Build Instructions

```bash
cd /path/to/NatA_Lang
cmake -S . -B build
cmake --build build
```

### Running the Compiler

1. Copy the `.nat` files from `input/` into the `build` output directory.
2. Use the included `Runner.bat` script to run the compiler:
   - Replace `testfile.nat` with your input file name.
3. The output and errors will be saved in `.out` and `.err` files, respectively.

---

## Example Programs

Located in `input/`:

- `INPUT0_Empty.nat`: Empty file test
- `INPUT1_Hello.nat`: Prints "Hello, World!"
- `INPUT2_Volume.nat`: Volume of a sphere calculation
- `INPUT3_Factorial.nat`: Factorial using loops
- `INPUT4_Datatypes.nat`: Shows supported data types
- `INPUT5_Big.nat`: Stress test with complex logic

---

## Project Milestones & Version History

### ✅ A11 – Language Proposal and Specification  
**Commit:** `a11-language-proposal`  
**Date:** Sep 23, 2023  
Defined NatA language structure, keywords, syntax rules, and datatypes. Initial `.nat` programs included.

### ✅ A12 – Reader (Buffer) Implementation  
**Commit:** `a12-reader-buffer`  
**Date:** Oct 8, 2023  
Developed a dynamic memory buffer system (`Reader.c/h`) to process source code files securely using defensive programming.

### ✅ A21 – Lexical Model (RE/Automata)  
**Commit:** `a21-language-model`  
**Date:** Oct 22, 2023  
Created Regular Expressions, Transition Diagrams, and Transition Tables for lexical tokens used in the Scanner.

### ✅ A22 – Scanner (Lexical Analyzer) Implementation  
**Commit:** `a22-scanner`  
**Date:** Nov 12, 2023  
Implemented the `Scanner.c` logic to tokenize source files, classify keywords, literals, identifiers, and output token streams.

### ✅ A31 – Grammar Specification (BNF)  
**Commit:** `a31-bnf-grammar`  
**Date:** Nov 26, 2023  
Defined the full grammar for the NatA language using BNF notation. This grammar forms the base for the parser logic.

### ✅ A32 – Parser (Syntax Analyzer) Implementation  
**Commit:** `a32-parser`  
**Date:** Dec 10, 2023  
Implemented top-down parsing logic for validating NatA syntax, using the BNF from A31 and tokens from the Scanner.

---

## Contributors

- **Marcos Antonio Astudillo Carrasco** – Lead Developer  
- **David Burchat** – Co-Developer

---

## License

This project is for academic and educational purposes only. No specific open-source license applies.

---

## 📫 Connect With Me

[![🌍 Portfolio](https://img.shields.io/badge/Website-marcosastudillo.com-blueviolet?style=for-the-badge&logo=google-chrome)](https://www.marcosastudillo.com)
[![💼 LinkedIn](https://img.shields.io/badge/LinkedIn-Marcos%20Astudillo-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/marcos-antonio-astudillo-carrasco)
[![🐱 GitHub](https://img.shields.io/badge/GitHub-ThisIsAntonio-181717?style=for-the-badge&logo=github)](https://github.com/ThisIsAntonio)

**Email:** m.astudillo1986@gmail.com
