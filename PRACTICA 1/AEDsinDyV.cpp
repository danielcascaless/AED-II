#include <iostream>
#include <string>
#include <climits>

using namespace std;

pair<int, int> encontrarMaximaDiferenciaSubcadena(const string& A, const string& B, int m) {
    int max_diff = INT_MIN;
    int best_start = -1;
    int n = A.size();
    
    for (int i = 0; i <= n - m; ++i) {
        int current_diff = 0;
        int chars_counted = 0;
        int j = i;
        
        // Contamos m caracteres válidos (ignorando espacios)
        while (chars_counted < m && j < n) {
            if (A[j] != ' ' && B[j] != ' ') {
                current_diff += abs(A[j] - B[j]);
                chars_counted++;
            }
            j++;
        }
        
        // Solo consideramos si encontramos m caracteres válidos
        if (chars_counted == m && current_diff > max_diff) {
            max_diff = current_diff;
            best_start = i;
        }
    }
    
    return {best_start, max_diff};
}

int main() {
    string A, B;
    int m;

    cout << "Introduce la cadena A: ";
    getline(cin, A);
    cout << "Introduce la cadena B: ";
    getline(cin, B);
    cout << "Introduce el valor de m: ";
    cin >> m;

    if (A.size() != B.size()) {
        cout << "Las cadenas deben tener la misma longitud." << endl;
        return 1;
    }

    pair<int, int> resultado = encontrarMaximaDiferenciaSubcadena(A, B, m);
    
    // Mostrar índice base 1 (para coincidir con el ejemplo)
    cout << "Posición de inicio: " << resultado.first << ", Diferencia total: " << resultado.second << endl;
    
    return 0;
}