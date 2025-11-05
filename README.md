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

---
## Running the C++ Code (Visual Studio Code + MinGW)

### Prerequisites

Before running the project, make sure you have the following installed and configured:

1. **Visual Studio Code**  
   [Download VS Code](https://code.visualstudio.com/)

2. **C++ Compiler: MinGW (g++)**  
   - Download and install MinGW from:  
     [https://sourceforge.net/projects/mingw/](https://sourceforge.net/projects/mingw/)
   - During installation, make sure to include the component:
     ```
     mingw32-gcc-g++
     ```
   - Add the MinGW path to your system environment variables (PATH).  
     Example:
     ```
     C:\MinGW\bin
     ```
   - Verify the installation by opening a terminal and typing:
     ```bash
     g++ --version
     ```
     If everything is set up correctly, you’ll see the installed version (for example: `g++ (MinGW.org GCC-6.3.0-1)`).

3. **C++ Extension for Visual Studio Code**  
   Install the official C++ extension from the Marketplace.
   
### Initial Project Setup

1. Open **Visual Studio Code**.  
2. Create a folder for your project.  
3. Inside that folder, create a file named:  
   `main.cpp`
4. Copy and paste the source code from the file `ProyectoFinal.cpp` (from this GitHub repository) into `main.cpp`.
5. Save the changes (`Ctrl + S`).
6. Compile the program. (If there are no errors, a `main.exe` file will be created in the same folder.)

### Running the Program

When you start the program, you’ll see a menu similar to this:
```
Proyecto: Generador de Analizador sintactico  LL(1) y SLR(1)
Seleccione el ejemplo a probar:
1. Ejemplo 1 (gramatica de expresiones aritmeticas)
2. Ejemplo 2 (gramatica con epsilon)
3. Ejemplo 3 (gramatica no LL(1) ni SLR(1))
4. Ingresar mi propia gramatica
0. Salir

```

Enter the number of the option you want to run and press Enter.

- If the program displays *Invalid input*, enter only a valid number (0–4).
- Option 4 allows you to enter your own grammar following this format:
```
S -> AB
A -> aA | d
B -> bBc | e

```
When asked to test strings:
- Type one string per line.  
- Press Enter to analyze it.  
- Leave the line empty and press Enter to end the test.  
- The program will indicate whether the string is accepted (`yes`) or rejected (`no`) according to the selected parser type.

---
## Execution Examples

Below are some examples of the expected program behavior with different grammars.

---

### Example 1

**Input**
```
3
S -> S+T T
T -> T*F F
F -> (S) i
```
**The program should print:**   
Grammar is SLR(1).

Then, assume it is given the strings (one at a time):
```
i+i
(i)
(i+i)*i)
```
**It should print**
- yes
- yes
- no

### Example 2

**Input**
```
3
S -> AB
A -> aA d
B -> bBc e
```

**The program should print:**  
Select a parser (T: for LL(1), B: for SLR(1), Q: quit):

Assume **T** is given. Then, assume it is given the strings (one at a time):

```
d
adbc
a
```
**It should print**:
- yes
- yes
- no

### Example 3

**Input**

```
2
S -> A
A -> A b
```

**The program should print:**  
Grammar is neither LL(1) nor SLR(1).


---
## Examples Included
1. **Example 1:** Arithmetic expressions grammar (SLR(1))  
2. **Example 2:** Grammar with epsilon transitions (LL(1) and SLR(1))  
3. **Example 3:** Grammar that is neither LL(1) nor SLR(1)  
4. **Option to input a custom grammar manually**

---
## References
1. **Pdf:** 
   - Explanation of the project(https://drive.google.com/drive/folders/1PdU6It2ukd3Y5SR6j15NgUm5RaS1ZOl0)
2. **Book**
   - Aho, Alfred V. et al. Compilers: Principles, Techniques, and Tools (2nd Edition). USA: Addison-Wesley Longman
3. **AI Tools:**
   - ChatGPT for code organization and explanation of the project.
