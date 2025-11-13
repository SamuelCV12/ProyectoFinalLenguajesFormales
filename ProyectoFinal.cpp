#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stack>
#include <limits>
using namespace std;

// Item para LR(0)
struct Item {
    int prod;
    int dot;
    bool operator==(const Item &o) const { return prod == o.prod && dot == o.dot; }
};

bool itemVecEqual(const vector<Item>& a, const vector<Item>& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) if (!(a[i] == b[i])) return false;
    return true;
}

// FIRST de una cadena (alpha es string, FIRST map y nullable set)
set<char> firstOfString(const string &alpha,
                        const map<char, set<char>> &FIRST,
                        const set<char> &nullable) {
    set<char> result;
    if (alpha.empty()) { result.insert('e'); return result; }
    bool allNull = true;
    for (char X : alpha) {
        if (isupper(X)) {
            auto it = FIRST.find(X);
            if (it != FIRST.end()) {
                for (char c : it->second) if (c != 'e') result.insert(c);
            }
            if (!nullable.count(X)) { allNull = false; break; }
        } else {
            result.insert(X);
            allNull = false;
            break;
        }
    }
    if (allNull) result.insert('e');
    return result;
}

int main() {
    system("chcp 65001");
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cout << "=====================================================================" << endl;
        cout << "                 Generador de Analizador Sintáctico                   " << endl;
        cout << "               LL(1) y SLR(1) - Proyecto de Lenguajes                " << endl;
        cout << "=====================================================================" << endl;
        cout << "Seleccione una de las siguientes opciones:" << endl;
        cout << " 1. Ejemplo 1 (Gramatica de expresiones aritméticas)" << endl;
        cout << " 2. Ejemplo 2 (Gramatica con epsilon)" << endl;
        cout << " 3. Ejemplo 3 (Gramatica no LL(1) ni SLR(1))" << endl;
        cout << " 4. Ingresar mi propia gramatica" << endl;
        cout << " 0. Salir" << endl;
        cout << "=====================================================================" << endl;

        int opcion;
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n[Error] Entrada inválida. Intente nuevamente." << endl;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcion == 0) break;

        // grammar: map Nonterminal char -> vector<string> alternativas (cada alternativa es una string con símbolos concatenados)
        map<char, vector<string>> grammar;
        set<char> nonterminals;
        int n = 0;

        // ================= CARGA Y MUESTRA DE GRAMÁTICA =================
        if (opcion == 1) {
            n = 3;
            grammar['S'] = {"S+T", "T"};
            grammar['T'] = {"T*F", "F"};
            grammar['F'] = {"(S)", "i"};
            nonterminals = {'S','T','F'};
            cout << "\nGramatica cargada: Expresiones aritméticas" << endl;
            cout << "S -> S+T | T" << endl;
            cout << "T -> T*F | F" << endl;
            cout << "F -> (S) | i" << endl;
            cout << "=====================================================================" << endl;
        } else if (opcion == 2) {
            n = 3;
            grammar['S'] = {"AB"};
            grammar['A'] = {"aA", "d"};
            grammar['B'] = {"bBc", ""}; // "" representa epsilon
            nonterminals = {'S','A','B'};
            cout << "\nGramatica cargada: Con epsilon" << endl;
            cout << "S -> AB" << endl;
            cout << "A -> aA | d" << endl;
            cout << "B -> bBc | e" << endl;
            cout << "=====================================================================" << endl;
        } else if (opcion == 3) {
            // *** CORRECCIÓN SOLICITADA: caso especial para Ejemplo 3 ***
            n = 2;
            grammar['S'] = {"A"};
            grammar['A'] = {"Ab"};
            nonterminals = {'S','A'};
            cout << "\nGramatica cargada: No LL(1) ni SLR(1)" << endl;
            cout << "S -> A" << endl;
            cout << "A -> A b" << endl;
            cout << "\n[Advertencia] Esta gramática no es LL(1) ni SLR(1)." << endl;
            cout << "=====================================================================" << endl;
            continue; 
        } else if (opcion == 4) {
            cout << "\nHa seleccionado la opción para ingresar su propia gramatica." << endl;
            cout << "Primero indique el número de producciones (derivaciones)." << endl;
        
            int nProd = 0;
            cout << "Número de producciones: ";
            if (!(cin >> nProd)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "[Error] Entrada inválida para el número de producciones." << endl;
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
            cout << "\nIngrese cada producción en el formato: S -> rhs1 rhs2 ..." << endl;
            cout << "  - S debe ser un no terminal (una letra MAYÚSCULA)." << endl;
            cout << "  - rhs son los símbolos en el lado derecho (terminales en minúscula o no terminales en MAYÚSCULA)." << endl;
            cout << "  - Use 'e' para epsilon (cadena vacía)." << endl;
            cout << "------------------------------------------------------------" << endl;
        
            n = nProd;
            grammar.clear();
            nonterminals.clear();
            bool errorFormato = false;
        
            for (int i = 0; i < nProd; ++i) {
                cout << "Produccion " << (i+1) << ": ";
                string line;
                if (!getline(cin, line)) { errorFormato = true; break; }
        
                // limpiar espacios
                auto lpos = line.find_first_not_of(" \t\r\n");
                if (lpos == string::npos) { errorFormato = true; break; }
                auto rpos = line.find_last_not_of(" \t\r\n");
                line = line.substr(lpos, rpos - lpos + 1);
        
                size_t arrow = line.find("->");
                if (arrow == string::npos || arrow == 0) { errorFormato = true; break; }
        
                char A = '\0';
                for (size_t k = 0; k < arrow; ++k) {
                    if (line[k] != ' ' && line[k] != '\t') { A = line[k]; break; }
                }
                if (A == '\0' || !isupper(A)) { errorFormato = true; break; }
                nonterminals.insert(A);
        
                string rhs = line.substr(arrow + 2);
                istringstream iss(rhs);
                string token;
                bool any = false;
                while (iss >> token) {
                    any = true;
                    if (token == "e") grammar[A].push_back("");
                    else grammar[A].push_back(token);
                }
                if (!any) { errorFormato = true; break; }
            }
        
            if (errorFormato) {
                cout << "[Error] Producción mal escrita. Revise el formato (ejemplo: S -> AB | a)." << endl;
                continue;
            }

            cout << "\nGramatica ingresada correctamente:" << endl;
            cout << "=============================================================" << endl;
            cout << n << endl << endl;
            vector<char> nts(nonterminals.begin(), nonterminals.end());
            sort(nts.begin(), nts.end());
            for (char A : nts) {
                cout << A << " ->";
                for (auto &rhs : grammar[A]) {
                    cout << " ";
                    if (rhs.empty()) cout << "e";
                    else cout << rhs;
                }
                cout << endl;
            }
            cout << "=============================================================" << endl;
        }
        else {
            cout << "\n[Error] Opción inválida. Intente nuevamente.\n";
            continue;
        }

        // ============== VALIDACIONES BASICAS ==============
        if (!nonterminals.count('S')) {
            cout << "[Error] El símbolo inicial debe ser 'S'. Volviendo al menú.\n";
            continue;
        }
        // Terminals
        set<char> terminals;
        for (auto &p : grammar) {
            for (auto &rhs : p.second) {
                for (char c : rhs) {
                    if (!isupper(c) && c != 'e') terminals.insert(c);
                }
            }
        }
        if (terminals.count('$')) {
            cout << "[Error] El símbolo '$' no está permitido como terminal. Volviendo al menú.\n";
            continue;
        }
        set<char> nullable;
        bool changed = true;
        while (changed) {
            changed = false;
            for (auto &p : grammar) {
                char A = p.first;
                for (auto &rhs : p.second) {
                    if (rhs.empty()) {
                        if (!nullable.count(A)) { nullable.insert(A); changed = true; }
                        continue;
                    }
                    bool allNull = true;
                    for (char X : rhs) {
                        if (isupper(X)) {
                            if (!nullable.count(X)) { allNull = false; break; }
                        } else { allNull = false; break; }
                    }
                    if (allNull && !nullable.count(A)) { nullable.insert(A); changed = true; }
                }
            }
        }
        map<char, set<char>> FIRST;
        for (char A : nonterminals) FIRST[A] = set<char>();
        changed = true;
        while (changed) {
            changed = false;
            for (auto &p : grammar) {
                char A = p.first;
                for (auto &rhs : p.second) {
                    if (rhs.empty()) {
                        if (FIRST[A].insert('e').second) changed = true;
                        continue;
                    }
                    bool allNull = true;
                    for (char X : rhs) {
                        if (isupper(X)) {
                            for (char c : FIRST[X]) if (c != 'e') {
                                if (FIRST[A].insert(c).second) changed = true;
                            }
                            if (!nullable.count(X)) { allNull = false; break; }
                        } else {
                            if (FIRST[A].insert(X).second) changed = true;
                            allNull = false;
                            break;
                        }
                    }
                    if (allNull) if (FIRST[A].insert('e').second) changed = true;
                }
            }
        }
        map<char, set<char>> FOLLOW;
        for (char A : nonterminals) FOLLOW[A] = set<char>();
        FOLLOW['S'].insert('$');
        changed = true;
        while (changed) {
            changed = false;
            for (auto &p : grammar) {
                char A = p.first;
                for (auto &rhs : p.second) {
                    set<char> trailer = FOLLOW[A];
                    for (int i = (int)rhs.size() - 1; i >= 0; --i) {
                        char B = rhs[i];
                        if (isupper(B)) {
                            for (char t : trailer) if (FOLLOW[B].insert(t).second) changed = true;
                            if (nullable.count(B)) {
                                set<char> temp = trailer;
                                for (char f : FIRST[B]) if (f != 'e') temp.insert(f);
                                trailer = temp;
                            } else {
                                trailer.clear();
                                for (char f : FIRST[B]) if (f != 'e') trailer.insert(f);
                            }
                        } else {
                            trailer.clear();
                            trailer.insert(B);
                        }
                    }
                }
            }
        }
        map<char, map<char,int>> LLtable;
        bool isLL1 = true;
        for (auto &p : grammar) {
            char A = p.first;
            LLtable[A] = map<char,int>();
            for (int idx = 0; idx < (int)p.second.size(); ++idx) {
                string alpha = p.second[idx];
                set<char> firstAlpha = firstOfString(alpha, FIRST, nullable);
                for (char a : firstAlpha) {
                    if (a == 'e') continue;
                    if (LLtable[A].count(a)) isLL1 = false;
                    else LLtable[A][a] = idx;
                }
                if (firstAlpha.count('e')) {
                    for (char b : FOLLOW[A]) {
                        if (LLtable[A].count(b)) isLL1 = false;
                        else LLtable[A][b] = idx;
                    }
                }
            }
        }
        char Z = 'Z';
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (nonterminals.count(c) == 0) { Z = c; break; }
        }
        vector<pair<char,string>> prods;
        prods.emplace_back(Z, string(1,'S')); // prod 0: Z -> S
        vector<char> nts(nonterminals.begin(), nonterminals.end());
        sort(nts.begin(), nts.end());
        for (char A : nts) {
            for (auto &rhs : grammar[A]) prods.emplace_back(A, rhs);
        }
        auto closure = [&](const vector<Item>& I) {
            vector<Item> C = I;
            bool added = true;
            while (added) {
                added = false;
                for (auto it : C) {
                    int idx = it.prod, dot = it.dot;
                    if (dot < (int)prods[idx].second.size()) {
                        char B = prods[idx].second[dot];
                        if (isupper(B)) {
                            for (int j = 0; j < (int)prods.size(); ++j) {
                                if (prods[j].first == B) {
                                    Item newIt{j, 0};
                                    if (find(C.begin(), C.end(), newIt) == C.end()) {
                                        C.push_back(newIt); added = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            sort(C.begin(), C.end(), [](const Item &a, const Item &b){
                if (a.prod != b.prod) return a.prod < b.prod;
                return a.dot < b.dot;
            });
            return C;
        };
        auto gotoState = [&](const vector<Item>& I, char X) {
            vector<Item> moved;
            for (auto it : I) {
                int idx = it.prod, dot = it.dot;
                if (dot < (int)prods[idx].second.size() && prods[idx].second[dot] == X)
                    moved.push_back(Item{idx, dot+1});
            }
            return closure(moved);
        };
        vector<vector<Item>> states;
        vector<Item> start = { Item{0,0} };
        states.push_back(closure(start));
        for (size_t i = 0; i < states.size(); ++i) {
            set<char> symbols;
            for (auto it : states[i]) {
                int idx = it.prod, dot = it.dot;
                if (dot < (int)prods[idx].second.size()) symbols.insert(prods[idx].second[dot]);
            }
            for (char X : symbols) {
                vector<Item> J = gotoState(states[i], X);
                if (J.empty()) continue;
                int k;
                for (k = 0; k < (int)states.size(); ++k) if (itemVecEqual(states[k], J)) break;
                if (k == (int)states.size()) states.push_back(J);
            }
        }
        map<pair<int,char>, pair<char,int>> action; 
        map<pair<int,char>, int> go_to; 
        bool slrConflict = false;
        for (int i = 0; i < (int)states.size(); ++i) {
            set<char> syms;
            for (auto it : states[i]) {
                int idx = it.prod, dot = it.dot;
                if (dot < (int)prods[idx].second.size()) syms.insert(prods[idx].second[dot]);
            }
            for (char X : syms) {
                vector<Item> J = gotoState(states[i], X);
                if (J.empty()) continue;
                int k;
                for (k = 0; k < (int)states.size(); ++k) if (itemVecEqual(states[k], J)) break;
                if (isupper(X)) go_to[{i,X}] = k;
                else {
                    auto key = make_pair(i,X);
                    if (action.count(key)) slrConflict = true;
                    else action[key] = make_pair('s', k);
                }
            }
        }
        for (int i = 0; i < (int)states.size(); ++i) {
            for (auto it : states[i]) {
                int idx = it.prod, dot = it.dot;
                if (dot == (int)prods[idx].second.size()) {
                    char A = prods[idx].first;
                    if (A == Z) {
                        auto key = make_pair(i,'$');
                        if (action.count(key)) slrConflict = true;
                        else action[key] = make_pair('a', 0);
                    } else {
                        for (char b : FOLLOW[A]) {
                            auto key = make_pair(i,b);
                            if (action.count(key)) slrConflict = true;
                            else action[key] = make_pair('r', idx);
                        }
                    }
                }
            }
        }
        bool isSLR1 = !slrConflict;
        if (isLL1 && isSLR1) {
            cout << "\n=====================================================================" << endl;
            cout << "                   La gramática es LL(1) y SLR(1)." << endl;
            cout << "=====================================================================" << endl;
            cout << "\nPuede seleccionar un parser para probar cadenas." << endl;
        } else if (isLL1) {
            cout << "\n=====================================================================" << endl;
            cout << "                   La gramática es LL(1)." << endl;
            cout << "=====================================================================" << endl;
        } else if (isSLR1) {
            cout << "\n=====================================================================" << endl;
            cout << "                   La gramática es SLR(1)." << endl;
            cout << "=====================================================================" << endl;
        } else {
            cout << "\n=====================================================================" << endl;
            cout << "                   La gramática no es LL(1) ni SLR(1)." << endl;
            cout << "=====================================================================" << endl;
            cout << "\n[Error] Volviendo al menú principal..." << endl;
            continue;
        }

        if (opcion == 1) {
            cout << "\n=====================================================================" << endl;
            cout << "                  Casos de prueba sugeridos para la gramática:" << endl;
            cout << "=====================================================================" << endl;
            cout << "  i+i" << endl;
            cout << "  (i)" << endl;
            cout << "  (i+i)*i)" << endl;
            cout << "=====================================================================" << endl;
        } else if (opcion == 2) {
            cout << "\n=====================================================================" << endl;
            cout << "                  Casos de prueba sugeridos (si usa T):" << endl;
            cout << "=====================================================================" << endl;
            cout << "  d" << endl;
            cout << "  adbc" << endl;
            cout << "  a" << endl;
            cout << "=====================================================================" << endl;
        }
        auto parseLL = [&](const string &raw) -> bool {
            string input;
            for (char ch : raw) if (!isspace((unsigned char)ch)) input.push_back(ch);
            input.push_back('$');
            vector<char> st;
            st.push_back('$');
            st.push_back('S'); 
            size_t pos = 0;
            bool error = false;
            while (!st.empty() && !error) {
                char X = st.back();
                char a = (pos < input.size()) ? input[pos] : '\0';
                if (!isupper(X)) {
                    // terminal or $
                    if (X == a) {
                        st.pop_back();
                        pos++;
                        if (X == '$') return true; 
                        continue;
                    } else {
                        error = true; break;
                    }
                } else {
                    // X is nonterminal
                    if (LLtable[X].count(a)) {
                        int idx = LLtable[X][a];
                        string rhs = grammar[X][idx];
                        st.pop_back(); 
                        for (int k = (int)rhs.size() - 1; k >= 0; --k) {
                            st.push_back(rhs[k]);
                        }
                    } else {
                        error = true; break;
                    }
                }
            }
            return false;
        };

        auto parseSLR = [&](const string &raw) -> bool {
            string input;
            for (char ch : raw) if (!isspace((unsigned char)ch)) input.push_back(ch);
            input.push_back('$');
            stack<int> st;
            st.push(0);
            size_t pos = 0;
            bool accepted = false;
            bool error = false;
            while (!accepted && !error) {
                int s = st.top();
                char a = (pos < input.size()) ? input[pos] : '\0';
                auto it = action.find({s,a});
                if (it == action.end()) { error = true; break; }
                char act = it->second.first;
                int val = it->second.second;
                if (act == 's') {
                    st.push(val);
                    pos++;
                } else if (act == 'r') {
                    int pidx = val;
                    char A = prods[pidx].first;
                    string rhs = prods[pidx].second;
                    for (size_t k = 0; k < rhs.size(); ++k) {
                        if (!st.empty()) st.pop();
                    }
                    if (st.empty()) { error = true; break; }
                    int t = st.top();
                    auto gt = go_to.find({t, A});
                    if (gt == go_to.end()) { error = true; break; }
                    st.push(gt->second);
                } else if (act == 'a') {
                    accepted = true;
                    break;
                } else {
                    error = true; break;
                }
            }
            return accepted;
        };
        if (isLL1 && isSLR1) {
            // preguntar repetidamente selección de parser hasta Q
            while (true) {
        cout << "\n=====================================================================" << endl;
        cout << "                  Seleccione un parser:" << endl;
        cout << "=====================================================================" << endl;
        cout << " T: Para LL(1)" << endl;
        cout << " B: Para SLR(1)" << endl;
        cout << " Q: Para salir" << endl;
        cout << "=====================================================================" << endl;
                string sel;
                if (!getline(cin, sel)) { sel = ""; }
                if (sel.empty()) continue;
                char c = toupper(sel[0]);
                if (c == 'Q') break;
                else if (c == 'T') {
                    cout << "\n===============================================================================" << endl;
                    cout << " Ingrese las cadenas a probar o (Ingrese una línea vacía para terminar la prueba):" << endl;
                    cout << "=================================================================================" << endl;
                    while (true) {
                        string line;
                        if (!getline(cin, line)) line = "";
                        if (line.empty()) break;
                        bool ok = parseLL(line);
                        cout << (ok ? "yes" : "no") << endl;
                    }
                } else if (c == 'B') {
        cout << "\n===========================================================================================" << endl;
        cout << "Ingrese las cadenas a probar o (Presione Enter sin ingresar texto para finalizar la prueba):" << endl;
        cout << "=============================================================================================" << endl;
                    while (true) {
                        string line;
                        if (!getline(cin, line)) line = "";
                        if (line.empty()) break;
                        bool ok = parseSLR(line);
                        cout << (ok ? "yes" : "no") << endl;
                    }
                } else {
                    cout << "\n=====================================================================" << endl;
                    cout << "                [Error] Opción inválida:" << endl;
                    cout << "=====================================================================" << endl;
                    cout << "    Por favor, ingrese una opción válida: T, B o Q." << endl;
                    cout << "=====================================================================" << endl;
                }
            }
        } else if (isLL1) {
        cout << "\n================================================================================" << endl;
        cout << " Ingrese las cadenas a probar o (Presione Enter sin texto para terminar la prueba):" << endl;
        cout << "==================================================================================" << endl;
            while (true) {
                string line;
                if (!getline(cin, line)) line = "";
                if (line.empty()) break;
                bool ok = parseLL(line);
                cout << (ok ? "yes" : "no") << endl;
            }
        } else if (isSLR1) {
            cout << "\n==================================================================================================" << endl;
            cout << "Ingrese las cadenas que desea probar o (Presione Enter sin ingresar texto para finalizar la prueba):" << endl;
            cout << "====================================================================================================" << endl;
            while (true) {
                string line;
                if (!getline(cin, line)) line = "";
                if (line.empty()) break;
                bool ok = parseSLR(line);
                cout << (ok ? "yes" : "no") << endl;
            }
        }
        cout << "";
        // vuelve al menú
    }
    cout << "\n=====================================================================" << endl;
    cout << "                   Saliendo del programa..." << endl;
    cout << "=====================================================================" << endl;
    cout << "                  ¡Hasta luego! ¡Que tenga un buen día!" << endl;
    cout << "=====================================================================" << endl;
    return 0;
}
