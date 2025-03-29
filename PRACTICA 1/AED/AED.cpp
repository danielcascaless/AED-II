#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric> // Incluir para usar accumulate
#include <chrono>

using namespace std;

vector<int> calcularDiferencia(const vector<int> &A, const vector<int> &B) {
    vector<int> diferencias(A.size());
    for (int i = 0; i < A.size(); ++i) {
        diferencias[i] = abs(A[i] - B[i]);
    }

    return diferencias;
}


pair<int, int> combinar(const pair<int, int> &izquierda, const pair<int, int> &derecha, const vector<int> &diferencias, int s, int t, int h, int m) {
    int mejorInicio = -1;
    int maximaSuma = -1;

    // Buscar en la mitad izquierda extendiéndose a la derecha si es necesario
    for (int i = s; i <= h; ++i) {
        int fin = min(i + m - 1, t); // Limitar el extremo derecho al límite del array
        if (fin - i + 1 == m) { // Asegurarse de que tenga tamaño m
            int sumaActual = accumulate(diferencias.begin() + i, diferencias.begin() + fin + 1, 0);
            if (sumaActual > maximaSuma) {
                maximaSuma = sumaActual;
                mejorInicio = i;
            }
        }
    }

    // Buscar en la mitad derecha extendiéndose a la izquierda si es necesario
    for (int i = h + 1; i <= t; ++i) {
        int inicio = max(i - m + 1, s); // Limitar el extremo izquierdo al límite del array
        if (i - inicio + 1 == m) { // Asegurarse de que tenga tamaño m
            int sumaActual = accumulate(diferencias.begin() + inicio, diferencias.begin() + i + 1, 0);
            if (sumaActual > maximaSuma) {
                maximaSuma = sumaActual;
                mejorInicio = inicio;
            }
        }
    }

    // Devolver el mejor resultado encontrado
    return {mejorInicio, maximaSuma};
}


pair<int, int> divideYvenceras(const vector<int> &diferencias, int s, int t, int m) {
    if (s == t && m == 1) {
        return {s, diferencias[s]};
    }
    if ((t - s + 1) < m) {
        return {-1, -1};
    }
    if ((t - s + 1) == m) {
        int diferenciaTotal = accumulate(diferencias.begin() + s , diferencias.begin() + s + m, 0);
        return {s,diferenciaTotal};
    }

    int h = (s + t) / 2;
    pair<int, int> izquierda = divideYvenceras(diferencias, s, h, m);
    pair<int, int> derecha = divideYvenceras(diferencias, h + 1, t, m);
    //return combinar(izquierda, derecha, diferencias, s, t, h, m);
    pair<int, int> combinado = combinar(izquierda, derecha, diferencias, s, t, h, m);


    //Devolver la mejor opción entre izquierda, derecha y combinada
    if (izquierda.second >= derecha.second && izquierda.second >= combinado.second) return izquierda;
    if (derecha.second >= izquierda.second && derecha.second >= combinado.second) return derecha;
    return combinado;
}

pair<int, int> encontrarMaximaDiferenciaSubcadena(const vector<int> &A, const vector<int> &B, int m) {
    vector<int> diferencias = calcularDiferencia(A, B);
    return divideYvenceras(diferencias, 0, diferencias.size() - 1, m);
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Uso: " << argv[0] << " archivo_entrada.txt" << endl;
        return 1;
    }

    ifstream archivo(argv[1]);
    if (!archivo) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string strA, strB;
    int m;

    // Leer datos desde el archivo
    getline(archivo, strA);
    getline(archivo, strB);
    archivo >> m;

    archivo.close();

    auto start = chrono::high_resolution_clock::now();

    // Eliminar espacios de las cadenas
    strA.erase(remove(strA.begin(), strA.end(), ' '), strA.end());
    strB.erase(remove(strB.begin(), strB.end(), ' '), strB.end());

    vector<int> A(strA.begin(), strA.end());
    vector<int> B(strB.begin(), strB.end());

    pair<int, int> resultado = encontrarMaximaDiferenciaSubcadena(A, B, m);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Posición de inicio: " << resultado.first << ", Diferencia total: " << resultado.second << endl;
    cout << "Tiempo de ejecución: " << duration << " microsegundos" << endl;

    return 0;
}
