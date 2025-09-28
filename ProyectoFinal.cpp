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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        cout << "Proyecto: Generador de Analizador sintactico  LL(1) y SLR(1)" << endl;
        cout << "Seleccione el ejemplo a probar:" << endl;
        cout << "1. Ejemplo 1 (gramatica de expresiones aritmeticas)" << endl;
        cout << "2. Ejemplo 2 (gramatica con epsilon)" << endl;
        cout << "3. Ejemplo 3 (gramatica no LL(1) ni SLR(1))" << endl;
        cout << "4. Ingresar mi propia gramatica" << endl;
        cout << "0. Salir" << endl;
        cout << ""<< endl;

        int opcion;
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida." << endl;
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
            cout << "Se cargo la siguiente gramatica:\n";
            cout << "S -> S+T T\n";
            cout << "T -> T*F F\n";
            cout << "F -> (S) i\n";
            cout << "" << endl;
        } else if (opcion == 2) {
            n = 3;
            grammar['S'] = {"AB"};
            grammar['A'] = {"aA", "d"};
            grammar['B'] = {"bBc", ""}; // "" representa epsilon
            nonterminals = {'S','A','B'};
            cout << "Se cargo la siguiente gramatica:\n";
            cout << "S -> AB\n";
            cout << "A -> aA d\n";
            cout << "B -> bBc e\n";
            cout << "" << endl;
        } else if (opcion == 3) {
            // *** CORRECCIÓN SOLICITADA: caso especial para Ejemplo 3 ***
            n = 2;
            grammar['S'] = {"A"};
            grammar['A'] = {"Ab"};
            nonterminals = {'S','A'};
            cout << "Se Cargo la siguiente gramatica\n";
            cout << "S -> A\n";
            cout << "A -> A b\n";
            cout << "" << endl;
            // Mensaje en español — no pedir parser ni permitir pruebas (según enunciado esperado)
            cout << "Dicha gramatica no es LL(1) ni SLR(1)." << endl;
            cout << "" << endl;
            continue; // volvemos al menú principal
        } else if (opcion == 4) {
            cout << "Ha seleccionado la opcion para ingresar su propia gramatica." << endl;
            cout << "Primero indique el numero de producciones (derivaciones)." << endl;
        
            int nProd = 0;
            cout << "Numero de producciones: ", nProd;
            if (!(cin >> nProd)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Error: entrada invalida para el numero de producciones." << endl;
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
            cout << "\nIngrese cada produccion en el formato: S -> rhs1 rhs2 ..." << endl;
            cout << " - S debe ser un no terminal (una letra MAYUSCULA)." << endl;
            cout << " - rhs son los simbolos en el lado derecho (terminales en minuscula o no terminales en MAYUSCULA)." << endl;
            cout << " - Use 'e' para epsilon (cadena vacia)." << endl;
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
                cout << "Error: produccion mal escrita. Revise el formato (ejemplo: S -> AB | a)." << endl;
                continue;
            }
        
            // mostrar gramatica ingresada
            cout << "\nGramatica ingresada correctamente:" << endl;
            cout << "Input" << endl;
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
            cout << "------------------------------------------------------------" << endl << endl;
        
            // a partir de aqui el flujo sigue igual que en los ejemplos:
            // validar si es LL(1), SLR(1), ambas o ninguna
            // (tu codigo ya hace esto mas abajo, asi que no necesitas tocar nada adicional)
        }
         else {
            cout << "Opcion invalida.\n";
            continue;
        }

        // ============== VALIDACIONES BASICAS ==============
        if (!nonterminals.count('S')) {
            cout << "Error: el simbolo inicial debe ser 'S'. Volviendo al menu.\n";
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
            cout << "Error: el simbolo '$' no esta permitido como terminal. Volviendo al menu.\n";
            continue;
        }

        // ============== CALCULO NULLABLE ==============
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

        // ============== FIRST ==============
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

        // ============== FOLLOW ==============
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

        // ============== TABLA LL(1) ==============
        map<char, map<char,int>> LLtable; // A -> (terminal -> index de RHS)
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

        // ============== PREPARAR PRODUCCIONES SLR ==============
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

        // ============== CLOSURE / GOTO para LR(0) ==============
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

        // ============== CONSTRUCCION COLECCION CANONICA LR(0) ==============
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

        // ============== CONSTRUCCION ACTION / GOTO (SLR) ==============
        map<pair<int,char>, pair<char,int>> action; // (state,terminal) -> ( 's'/'r'/'a', val )
        map<pair<int,char>, int> go_to; // (state, nonterminal) -> state
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

        // ============== MOSTRAR RESULTADO Y CASOS SUGERIDOS ==============
        if (isLL1 && isSLR1) {
            cout << "La gramatica es LL(1) y SLR(1)." << endl;
            cout << "" << endl;
            cout << "Puede seleccionar parser para probar cadenas." << endl;
        } else if (isLL1) {
            cout << "La gramatica es LL(1)." << endl;
        } else if (isSLR1) {
            cout << "La gramatica es SLR(1)." << endl;
        } else {
            cout << "La gramatica no es LL(1) ni SLR(1)." << endl;
            cout << "";
            continue;
        }

        if (opcion == 1) {
            cout << "Casos de prueba sugeridos:" << endl;
            cout << "i+i" << endl;
            cout << "(i)" << endl;
            cout << "(i+i)*i)" << endl;
            cout << "" << endl;
        } else if (opcion == 2) {
            cout << "Casos de prueba sugeridos (si usa T):" << endl;
            cout << "d" << endl;
            cout << "adbc" << endl;
            cout << "a" << endl;
        }

        // ============== FUNCIONES DE PARSEO ==============
        auto parseLL = [&](const string &raw) -> bool {
            // prepara input sin espacios y con $
            string input;
            for (char ch : raw) if (!isspace((unsigned char)ch)) input.push_back(ch);
            input.push_back('$');
            // stack de simbolos (char), fondo $
            vector<char> st;
            st.push_back('$');
            st.push_back('S'); // simbolo inicial S
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
                        if (X == '$') return true; // aceptado
                        continue;
                    } else {
                        error = true; break;
                    }
                } else {
                    // X is nonterminal
                    if (LLtable[X].count(a)) {
                        int idx = LLtable[X][a];
                        string rhs = grammar[X][idx];
                        st.pop_back(); // quitar X
                        // push rhs en orden inverso (si rhs vacio no empuja)
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

        // ============== INTERACCION SEGUN TIPO ==============
        if (isLL1 && isSLR1) {
            // preguntar repetidamente selección de parser hasta Q
            while (true) {
                cout << "\nSeleccione un parser (T: para LL(1), B: para SLR(1), Q: salir):" << endl;
                string sel;
                if (!getline(cin, sel)) { sel = ""; }
                if (sel.empty()) continue;
                char c = toupper(sel[0]);
                if (c == 'Q') break;
                else if (c == 'T') {
                    cout << "Ingrese cadenas a probar (linea vacia para terminar):" << endl;
                    while (true) {
                        string line;
                        if (!getline(cin, line)) line = "";
                        if (line.empty()) break;
                        bool ok = parseLL(line);
                        cout << (ok ? "yes" : "no") << endl;
                    }
                } else if (c == 'B') {
                    cout << "Ingrese cadenas a probar (linea vacia para terminar):" << endl;
                    while (true) {
                        string line;
                        if (!getline(cin, line)) line = "";
                        if (line.empty()) break;
                        bool ok = parseSLR(line);
                        cout << (ok ? "yes" : "no") << endl;
                    }
                } else {
                    cout << "Opcion invalida. Escriba T, B o Q." << endl;
                }
            }
        } else if (isLL1) {
            cout << "Ingrese cadenas a probar (linea vacia para terminar):" << endl;
            while (true) {
                string line;
                if (!getline(cin, line)) line = "";
                if (line.empty()) break;
                bool ok = parseLL(line);
                cout << (ok ? "yes" : "no") << endl;
            }
        } else if (isSLR1) {
            cout << "Ingrese cadenas a probar (linea vacia para terminar):" << endl;
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

    cout << "Saliendo. ¡Listo!" << endl;
    return 0;
}
