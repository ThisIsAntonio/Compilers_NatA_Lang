
# 🧠 NatA Lang – Educational Compiler Front-End in C

## 🌟 Overview

**NatA Lang** is a domain-specific programming language and educational compiler developed as part of the CST8152 - Compilers course at Algonquin College (Fall 2023). Created by Marcos Antonio Astudillo Carrasco and David Burchat, this language project is structured to explore the stages of compiler construction:

- 🧾 **Reader (Buffer)** – Handles file input and buffering
- 🧪 **Scanner (Lexical Analyzer)** – Tokenizes source code into meaningful elements
- 📐 **Parser (Syntax Analyzer)** – Validates structure using BNF-defined grammar

---

## 💡 Language Features

Inspired by Go and C-style languages, **NatA** emphasizes simplicity and educational clarity. Supported constructs include:

- 📦 Variable declarations with types (`int`, `float64`, `string`, `byte`)
- 🔄 Control structures: `if`, `else`, `for`, `while`
- 🧮 Arithmetic and logical operations
- 📤 Output and 📥 input commands
- 🧩 Functions with parameter and return type support

---

## 🗂️ Project Structure

```
NatA_Lang/
│
├── input/                  # Sample .nat files for testing
├── Compilers.c/h          # Shared definitions
├── Reader.c/h             # Reader logic
├── MainReader.c           # Reader test main
├── Scanner.c/h            # Scanner logic (lexical analyzer)
├── MainScanner.c          # Scanner test main
├── Parser.c/h             # Parser logic (syntax analyzer)
├── MainParser.c           # Parser test main
├── Runner.bat             # Batch script for compilation/execution
├── CMakeLists.txt         # CMake configuration
└── CMakePresets.json      # CMake environment presets
```

---

## ⚙️ Building and Running

### 🔧 Requirements

- 🖥️ **C Compiler** (GCC or MSVC)
- 🛠️ **CMake** ≥ 3.20
- 🪟 **Windows (preferred)** or any POSIX-compliant OS

### 🔨 Build Instructions

```bash
cd /path/to/NatA_Lang
cmake -S . -B build
cmake --build build
```

### 🚀 Run Instructions

1. Place `.nat` files in `build/` directory
2. Run `Runner.bat` or manually run the compiled executable
3. Check output `.out` and error `.err` files in the same directory

---

## 🧪 Sample Programs

Available in `input/`:

- `INPUT0_Empty.nat` – Verifies compiler response to an empty file
- `INPUT1_Hello.nat` – Simple "Hello, World!" output
- `INPUT2_Volume.nat` – Calculates sphere volume using expressions
- `INPUT3_Factorial.nat` – Demonstrates recursion and loops
- `INPUT4_Datatypes.nat` – Validates variable declarations
- `INPUT5_Big.nat` – Comprehensive stress test of compiler capabilities

---

## 📆 Project Milestones & Version History

### ✅ A11 – Language Proposal  
`a11-language-proposal` – 📅 Sep 23, 2023  
Initial language specification, keywords, syntax rules, datatypes, and test cases.

### ✅ A12 – Reader (Buffer)  
`a12-reader-buffer` – 📅 Oct 8, 2023  
Dynamic memory reader system built to handle secure and efficient file reading.

### ✅ A21 – Lexical Analysis Model  
`a21-language-model` – 📅 Oct 22, 2023  
Defined REs, token classes, automata diagrams, and transition tables.

### ✅ A22 – Scanner (Lexer)  
`a22-scanner` – 📅 Nov 12, 2023  
Tokenizer for source code, generating token streams and error outputs.

### ✅ A31 – Grammar Specification  
`a31-bnf-grammar` – 📅 Nov 26, 2023  
Created BNF rules for the language to support recursive-descent parsing.

### ✅ A32 – Parser Implementation  
`a32-parser` – 📅 Dec 10, 2023  
Parser validates syntax and handles structural errors.

---

## 👥 Contributors

- **Marcos Antonio Astudillo Carrasco** – Lead Developer  
- **David Burchat** – Co-Developer

---

## 🧾 License

This project is for academic and educational use. No open-source license applies.

---

## 📫 Connect With Me

[![🌍 Portfolio](https://img.shields.io/badge/Website-marcosastudillo.com-blueviolet?style=for-the-badge&logo=google-chrome)](https://www.marcosastudillo.com)
[![💼 LinkedIn](https://img.shields.io/badge/LinkedIn-Marcos%20Astudillo-blue?style=for-the-badge&logo=linkedin)](https://www.linkedin.com/in/marcos-astudillo-c/)
[![🐱 GitHub](https://img.shields.io/badge/GitHub-Marcos%20Astudillo-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/marcos-astudillo)

**Email:** m.astudillo1986@gmail.com
