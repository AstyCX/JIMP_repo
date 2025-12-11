#include "gauss.h"
#include <math.h>
#include <stdlib.h>


/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */

static void swap_rows(Matrix *M, int r1, int r2) {
    if (r1 == r2) return;
    double *tmp = M->data[r1];
    M->data[r1] = M->data[r2];
    M->data[r2] = tmp;
}

int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r;
    int m = b->c;
    int i, j, k;

    if (mat->r != mat->c || b->r != mat->r) {
        return 1;
    }

    const double EPS = 1e-12;

    // wektor skalowania
    double *scale = (double*)malloc(sizeof(double) * n);
    if (!scale) {
        return 1;
    }

    // obliczamy max |a_ij| w kazdym wierszu
    for (i = 0; i < n; ++i) {
        double smax = 0.0;
        for (j = 0; j < n; ++j) {
            double val = fabs(mat->data[i][j]);
            if (val > smax) {
                smax = val;
            }
        }
        if (smax == 0.0) {
            free(scale);
            return 1; // wiersz zerowy -> macierz osobliwa
        }
        scale[i] = smax;
    }

    for (k = 0; k < n - 1; ++k) {
        // skalowany wybór pivotu
        int pivot_row = k;
        double max_ratio = fabs(mat->data[k][k]) / scale[k];

        for (i = k + 1; i < n; ++i) {
            double ratio = fabs(mat->data[i][k]) / scale[i];
            if (ratio > max_ratio) {
                max_ratio = ratio;
                pivot_row = i;
            }
        }

        if (max_ratio * scale[pivot_row] < EPS) {
            free(scale);
            return 1; // praktycznie brak pivotu
        }

        if (pivot_row != k) {
            swap_rows(mat, k, pivot_row);
            swap_rows(b,   k, pivot_row);

            // skalowanie też trzeba przestawić
            double tmp_s = scale[k];
            scale[k] = scale[pivot_row];
            scale[pivot_row] = tmp_s;
        }

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

    if (fabs(mat->data[n - 1][n - 1]) < EPS) {
        free(scale);
        return 1;
    }

    free(scale);
    return 0;
}