#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r;
    int m = b->c;
    int i, j, k;

    // kontrola wymiarów
    if (mat->r != mat->c || b->r != mat->r) {
        return 1;
    }

    const double EPS = 1e-12;

    for (k = 0; k < n - 1; ++k) {
        // Wybór elementu głównego w kolumnie k
        int p = k;
        double max_val = fabs(mat->data[k][k]);

        for (i = k + 1; i < n; ++i) {
            double val = fabs(mat->data[i][k]);
            if (val > max_val) {
                max_val = val;
                p = i;
            }
        }

        // brak pivotu -> macierz osobliwa
        if (max_val < EPS) {
            return 1;
        }

        // Zamiana wierszy k i p, jezeli trzeba
        if (p != k) {
            // zamiana wierszy w A
            double *tmp_row = mat->data[k];
            mat->data[k] = mat->data[p];
            mat->data[p] = tmp_row;

            // zamiana wierszy w b
            double *tmp_b_row = b->data[k];
            b->data[k] = b->data[p];
            b->data[p] = tmp_b_row;
        }

        // eliminacоф z użyciem nowego pivotu
        double pivot = mat->data[k][k];

        for (i = k + 1; i < n; ++i) {
            double factor = mat->data[i][k] / pivot;

            mat->data[i][k] = 0.0;

            for (j = k + 1; j < n; ++j) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            for (j = 0; j < m; ++j) {
                b->data[i][j] -= factor * b->data[k][j];
            }
        }
    }

    // ostatni pivot
    if (fabs(mat->data[n - 1][n - 1]) < EPS) {
        return 1;
    }

    return 0;
}