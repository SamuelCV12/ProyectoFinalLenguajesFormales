# ProyectoFinalLenguajesFormales


# LL(1) and SLR(1) Parser Generator

## Overview
This project implements a **syntax analyzer generator** that builds and tests **LL(1)** and **SLR(1)** parsers for context-free grammars.  
It allows users to load predefined grammars or input their own, analyze their properties, and test input strings interactively.

The program is written entirely in **C++**, using only the standard library (no external dependencies).

---

## Features
- **Grammar Input Options**
  - Predefined examples:
    1. Arithmetic expression grammar  
    2. Grammar with epsilon (empty string)  
    3. Non-LL(1)/non-SLR(1) grammar  
  - Custom grammar input via console
- **Automatic Computation of**
  - Nullable nonterminals  
  - FIRST and FOLLOW sets  
  - LL(1) parsing table  
  - LR(0) canonical collection  
  - ACTION and GOTO tables for SLR(1)
- **Parser Classification**
  - Detects whether the grammar is LL(1), SLR(1), both, or neither
- **Interactive Parsing**
  - Users can test input strings using LL(1) or SLR(1) parsers

---

## Example Grammars

### Example 1: Arithmetic Expressions

S -> S+T | T
T -> T*F | F
F -> (S) | i



### Example 2: Grammar with Epsilon


S -> AB
A -> aA | d
B -> bBc | ε



### Example 3: Invalid Grammar

S -> A
A -> A b


This grammar is neither LL(1) nor SLR(1).

---

## How to Use

### 1. Compile the Program
Use any C++17 (or later) compiler:

g++ -std=c++17 -O2 -o parser main.cpp

2. Run the Program
./parser

3. Select an Option

When the program starts, a menu will appear:

```

Project: Generador de Analizador sintactico LL(1) y SLR(1)
Select the example to test:
1. Example 1 (arithmetic expression grammar)
2. Example 2 (grammar with epsilon)
3. Example 3 (non-LL(1) and non-SLR(1) grammar)
4. Enter your own grammar
0. Exit
```

# 4. Enter a Grammar (Option 4)

You can input your own grammar using this format:

Example:
S -> AB
A -> aA | d
B -> bBc | e

## Rules
- **Uppercase letters** = nonterminals  
- **Lowercase letters** = terminals  
- Use **`e`** for epsilon (empty string)

---

# 5. Test Strings

If the grammar is **LL(1)**, **SLR(1)**, or both, the program will allow testing input strings.

### Example Input
Enter strings to test (empty line to finish):
i+i
(i)
(i+i)*i)

### Example Output
yes
no

Each result indicates whether the string is **accepted** (`yes`) or **rejected** (`no`) by the parser.

---

# File Structure
├── main.cpp      # Core program source code
├── README.md     # Project documentation

---

# Implementation Details
- **Language:** C++17  
- **Dependencies:** Standard Template Library (STL) only  

### Core Components
- Computation of FIRST and FOLLOW sets  
- Construction of LL(1) parse table  
- Construction of LR(0) items, closure, and goto functions  
- SLR(1) parsing table generation  
- LL(1) and SLR(1) parsing algorithms  

---

# Example Outputs

### Case 1 – Grammar is LL(1) and SLR(1)
The grammar is LL(1) and SLR(1).  
You can select parser to test strings.

### Case 2 – Grammar is only LL(1)
The grammar is LL(1).  
Enter strings to test:

### Case 3 – Grammar is neither LL(1) nor SLR(1)
The grammar is not LL(1) nor SLR(1).

---

# Author
Developed as part of a **compiler construction and syntax analysis** project.  
Language: **C++**





