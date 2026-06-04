#include <iostream>
#include <stdexcept>
#include <string>
#include "List.h"
#include "BSTDictionary.h"

using namespace std;

string readLine(string prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

int readInt(string prompt) {
    string input;
    while (true) {
        cout << prompt;
        getline(cin, input);
        try {
            return stoi(input);
        }
        catch (...) {
            cout << "Entrada invalida. Ingrese un numero entero." << endl;
        }
    }
}

void printDictionary(BSTDictionary<int, string>* dict, string name) {
    cout << "\n=== " << name << " (" << dict->getSize() << " elementos) ===" << endl;
    dict->print();
}

void printMenu() {
    cout << "\n---- MENU ----" << endl;
    cout << "  1. insert" << endl;
    cout << "  2. remove" << endl;
    cout << "  3. getValue" << endl;
    cout << "  4. setValue" << endl;
    cout << "  5. contains" << endl;
    cout << "  6. clear" << endl;
    cout << "  7. getKeys" << endl;
    cout << "  8. getValues" << endl;
    cout << "  9. update" << endl;
    cout << " 10. zip" << endl;
    cout << "  0. Salir" << endl;
    cout << "--------------" << endl;
}

int chooseDictionary() {
    while (true) {
        int d = readInt("Sobre cual diccionario? (1 o 2): ");
        if (d == 1 || d == 2) {
            return d;
        }
        cout << "Opcion invalida. Ingrese 1 o 2." << endl;
    }
}

int main() {
    BSTDictionary<int, string> dict1;
    BSTDictionary<int, string> dict2;

    while (true) {
        printDictionary(&dict1, "Diccionario 1");
        printDictionary(&dict2, "Diccionario 2");

        printMenu();
        int opcion = readInt("Seleccione una opcion: ");

        if (opcion == 0) {
            cout << "Saliendo del programa..." << endl;
            break;
        }

        BSTDictionary<int, string>* dict = nullptr;
        BSTDictionary<int, string>* other = nullptr;
        int dictNum = 0;

        if (opcion >= 1 && opcion <= 8) {
            dictNum = chooseDictionary();
            dict = (dictNum == 1) ? &dict1 : &dict2;
            other = (dictNum == 1) ? &dict2 : &dict1;
        }

        try {
            if (opcion == 1) {
                int    key = readInt("Ingrese la llave (int): ");
                string value = readLine("Ingrese el valor (string): ");
                dict->insert(key, value);
                cout << "Par insertado correctamente." << endl;

            }
            else if (opcion == 2) {
                int key = readInt("Ingrese la llave a eliminar (int): ");
                string removed = dict->remove(key);
                cout << "Valor eliminado: " << removed << endl;
            }
            else if (opcion == 3) {
                int key = readInt("Ingrese la llave (int): ");
                string val = dict->getValue(key);
                cout << "Valor asociado: " << val << endl;
            }
            else if (opcion == 4) {
                int    key = readInt("Ingrese la llave (int): ");
                string value = readLine("Ingrese el nuevo valor (string): ");
                dict->setValue(key, value);
                cout << "Valor actualizado correctamente." << endl;

            }
            else if (opcion == 5) {
                int key = readInt("Ingrese la llave a buscar (int): ");
                bool found = dict->contains(key);
                cout << "La llave " << key << (found ? " SI" : " NO")
                    << " se encuentra en el diccionario." << endl;

            }
            else if (opcion == 6) {
                dict->clear();
                cout << "Diccionario " << dictNum << " vaciado correctamente." << endl;

            }
            else if (opcion == 7) {
                List<int>* keys = dict->getKeys();
                cout << "Llaves del diccionario " << dictNum << ": ";
                for (int i = 0; i < keys->getSize(); i++) {
                    keys->goToPos(i);
                    cout << keys->getElement();
                    if (i < keys->getSize() - 1) cout << ", ";
                }
                cout << endl;
                delete keys;

            }
            else if (opcion == 8) {
                auto values = dict->getValues();
                cout << "Valores del diccionario " << dictNum << ": ";
                for (int i = 0; i < values->getSize(); i++) {
                    values->goToPos(i);
                    cout << values->getElement();
                    if (i < values->getSize() - 1) cout << ", ";
                }
                cout << endl;
                delete values;
            }
            else if (opcion == 9) {
                dictNum = chooseDictionary();
                dict = (dictNum == 1) ? &dict1 : &dict2;
                other = (dictNum == 1) ? &dict2 : &dict1;
                dict->update(other);
                cout << "Diccionario " << dictNum << " actualizado con los contenidos del diccionario "
                    << (dictNum == 1 ? 2 : 1) << "." << endl;

            }
            else if (opcion == 10) {
                dictNum = chooseDictionary();
                dict = (dictNum == 1) ? &dict1 : &dict2;

                int n = readInt("Cuantos elementos desea ingresar? ");

                DLinkedList<int>    zipKeys;
                DLinkedList<string> zipValues;

                cout << "Ingrese " << n << " llave(s):" << endl;
                for (int i = 0; i < n; i++) {
                    int k = readInt("  Llave " + to_string(i + 1) + ": ");
                    zipKeys.append(k);
                }

                cout << "Ingrese " << n << " valor(es):" << endl;
                for (int i = 0; i < n; i++) {
                    string v = readLine("  Valor " + to_string(i + 1) + ": ");
                    zipValues.append(v);
                }

                dict->zip(&zipKeys, &zipValues);
                cout << "Operacion zip aplicada al diccionario " << dictNum << "." << endl;

            }
            else {
                cout << "Opcion no valida. Intente de nuevo." << endl;
            }

        }
        catch (...) {
            cout << "Error: No se puede realizar la operacion." << endl;
        }
    }

    return 0;
}