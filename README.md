# ProyectoFinalLenguajesFormales


LL(1) and SLR(1) Parser Generator
Overview

This project implements a syntax analyzer generator capable of building and testing LL(1) and SLR(1) parsers for context-free grammars.
It allows users to load predefined example grammars or input custom grammars directly, then analyze their properties and test input strings interactively.

The program is written entirely in C++, using standard library components only (no external dependencies).

Features

Grammar Input Options:

Predefined examples:

Arithmetic expression grammar.

Grammar with epsilon (empty string) productions.

Non-LL(1)/non-SLR(1) grammar.

Custom grammar input via console.

Automatic Computation of:

Nullable nonterminals.

FIRST and FOLLOW sets.

LL(1) parsing table.

LR(0) canonical collection.

ACTION and GOTO tables for SLR(1).

Parser Classification:

Determines whether the grammar is LL(1), SLR(1), both, or neither.

Interactive Parsing:

Users can test input strings for acceptance using either LL(1) or SLR(1) parsers.

Example Grammars
Example 1: Arithmetic Expressions
S -> S+T | T
T -> T*F | F
F -> (S) | i

Example 2: Grammar with Epsilon
S -> AB
A -> aA | d
B -> bBc | ε

Example 3: Invalid Grammar
S -> A
A -> A b


This grammar is neither LL(1) nor SLR(1).

How to Use
1. Compile the Program

Use any C++17 (or later) compiler:

g++ -std=c++17 -O2 -o parser main.cpp

2. Run the Program
./parser

3. Select an Option

The menu will appear:

Project: Generador de Analizador sintactico LL(1) y SLR(1)
Select the example to test:
1. Example 1 (arithmetic expression grammar)
2. Example 2 (grammar with epsilon)
3. Example 3 (non-LL(1) and non-SLR(1) grammar)
4. Enter your own grammar
0. Exit

4. Enter a Grammar (Option 4)

Input productions in the following format:

S -> AB
A -> aA | d
B -> bBc | e


Uppercase letters = nonterminals

Lowercase letters = terminals

Use e for epsilon (empty string)

5. Test Strings

If the grammar is LL(1), SLR(1), or both, the program will allow testing input strings:

Enter strings to test (empty line to finish):
i+i
(i)
(i+i)*i)


The program outputs yes or no depending on whether the string is accepted.

File Structure
├── main.cpp      # Core program source code
├── README.md     # Project documentation

Implementation Details

Language: C++17

Dependencies: Standard Template Library (STL) only

Core Components:

Computation of FIRST and FOLLOW sets.

Construction of LL(1) parse table.

Construction of LR(0) items, closure, and goto functions.

SLR(1) parsing table generation.

LL(1) and SLR(1) parsing algorithms.

Example Outputs

Case 1 (LL(1) and SLR(1)):

The grammar is LL(1) and SLR(1).
You can select parser to test strings.


Case 2 (Only LL(1)):

The grammar is LL(1).
Enter strings to test:


Case 3 (Neither LL(1) nor SLR(1)):

The grammar is not LL(1) nor SLR(1).

Author

Developed as part of a compiler construction and syntax analysis project.
Language: C++
