# Formal Languages Project (LL(1) and SLR(1) Parser Generator)
---

## Samuel Correa Velasquez — Class # 5730  
## Thomas Bedoya Rendon — Class # 5730

---

## Environment and Tools Used

- **Operating System:** Windows 11  
- **C++ Compiler:** g++ (MinGW.org GCC-6.3.0-1) 6.3.0  
- **Programming Language:** C++17
- **Visual Studio Code** (IDE) 

---

## Project Description
This project was developed for the **Formal Languages** course.  
The goal is to design and implement algorithms to compute **FIRST** and **FOLLOW** sets, and to build both **LL(1)** (Top-Down) and **SLR(1)** (Bottom-Up) parsers for context-free grammars.  
The program analyzes grammars, determines whether they are **LL(1)**, **SLR(1)**, both, or neither, and allows users to test input strings interactively.

## Features
- Interactive text-based menu for selecting predefined examples or entering a custom grammar.  
- Automatic computation of **nullable**, **FIRST**, and **FOLLOW** sets.  
- Construction of the **LL(1)** parsing table and **SLR(1)** parsing automaton using **LR(0) items**.  
- Detection of conflicts to classify the grammar.  
- Parsing of input strings with either LL(1) or SLR(1).  
- Output aligned with the expected format from the course project specifications.  
- Fully implemented in **C++17**, using only standard libraries.

## Examples Included
1. **Example 1:** Arithmetic expressions grammar (SLR(1))  
2. **Example 2:** Grammar with epsilon transitions (LL(1) and SLR(1))  
3. **Example 3:** Grammar that is neither LL(1) nor SLR(1)  
4. **Option to input a custom grammar manually**

## Technologies Used
- **Programming Language:** C++17  
- **Compiler:** g++ (GNU C++ 11.4.0) or any modern C++ compiler  
- **Libraries:** iostream, vector, string, map, set, stack, algorithm, limits  
- **Tested On:** Windows 10 and Ubuntu 22.04

## How to Compile and Run
### 1. Clone the Repository
 - https://github.com/SamuelCV12/ProyectoFinalLenguajesFormales

### 2. Compile the Program
g++ -std=c++17 -O2 -o parser ProyectoFinal.cpp  

### 3. Run the Program
./parser  

### 4. Program Menu
When executed, the following menu appears:
Proyecto: Generador de Analizador sintactico LL(1) y SLR(1)  
Seleccione el ejemplo a probar:  
1. Ejemplo 1 (gramatica de expresiones aritmeticas)  
2. Ejemplo 2 (gramatica con epsilon)  
3. Ejemplo 3 (gramatica no LL(1) ni SLR(1))  
4. Ingresar mi propia gramatica  
0. Salir  

## How It Works
1. **Grammar Input**  
   The user can select a predefined grammar or input a custom one using the format:  
   S -> AB  
   A -> aA d  
   B -> bBc e  
   - Epsilon is represented by `e`.  
   - `S` is always the start symbol.  
   - `$` is not allowed as a terminal.  

2. **Computation of Nullable, FIRST, and FOLLOW Sets**  
   The program iteratively computes the nullable nonterminals and the FIRST and FOLLOW sets for each nonterminal.

3. **LL(1) Table Construction**  
   The LL(1) parsing table is built based on FIRST and FOLLOW sets.  
   If a conflict (multiple entries) occurs, the grammar is not LL(1).

4. **SLR(1) Automaton Construction**  
   Using LR(0) items, the program constructs the canonical collection and derives ACTION and GOTO tables.  
   Conflicts in ACTION entries mark the grammar as non-SLR(1).

5. **Grammar Classification**  
   Depending on conflicts detected:  
   - Both LL(1) and SLR(1):  
     "La gramatica es LL(1) y SLR(1)."  
   - Only LL(1):  
     "La gramatica es LL(1)."  
   - Only SLR(1):  
     "La gramatica es SLR(1)."  
   - Neither:  
     "La gramatica no es LL(1) ni SLR(1)."

6. **Parsing Strings**  
   - For grammars that are LL(1) or SLR(1), the user can input strings to verify whether they belong to the language.  
   - The program prints “yes” if accepted, “no” otherwise.  
   - Input ends when an empty line is entered.

## Example Sessions

### Example 1
Input Grammar:  
S -> S+T T  
T -> T*F F  
F -> (S) i  

Output:  
Grammar is SLR(1).  

Test Strings:  
i+i      → yes  
(i)      → yes  
(i+i)*i) → no  

### Example 2
Input Grammar:  
S -> AB  
A -> aA d  
B -> bBc e  

Output:  
Select a parser (T: for LL(1), B: for SLR(1), Q: quit):  

Test Strings (LL(1)):  
d     → yes  
adbc  → yes  
a     → no  

### Example 3
Input Grammar:  
S -> A  
A -> A b  

Output:  
Grammar is neither LL(1) nor SLR(1).

## Repository Structure
 Project Root  
│  
├── ProyectoFinal.cpp   # Full implementation of LL(1) and SLR(1) parsers  
├── README.md           # Project documentation  

---
## References
1. **Pdf:** 
   - Explanation of the project(https://drive.google.com/drive/folders/1PdU6It2ukd3Y5SR6j15NgUm5RaS1ZOl0)
2. **Book**
   - Aho, Alfred V. et al. Compilers: Principles, Techniques, and Tools (2nd Edition). USA: Addison-Wesley Longman
3. **AI Tools:**
   - ChatGPT for code organization and explanation of the project.
