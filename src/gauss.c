#include "gauss.h"
#include <math.h> 
#include <stdlib.h>

/**
 * Zwraca 0 - eliminacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */

/* Pomocnicza funkcja do zamiany wierszy miejscami (zamiana wskaźników dla wydajności) */
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

    /* Sprawdzenie poprawności wymiarów: macierz A musi być kwadratowa, 
       a macierz B musi mieć tyle samo wierszy co A */
    if (mat->r != mat->c || b->r != mat->r) {
        return 1;
    }

    const double EPS = 1e-12; // Tolerancja dla zera (błędy numeryczne)

    /* Alokacja tablicy do przechowywania współczynników skalowania */
    double *scale = (double*)malloc(sizeof(double) * n);
    if (!scale) {
        return 1; // Błąd alokacji pamięci
    }

    /* Inicjalizacja tablicy skalowania: dla każdego wiersza znajdujemy 
       największą wartość bezwzględną, aby użyć jej do wyboru elementu głównego */
    for (i = 0; i < n; ++i) {
        double smax = 0.0;
        for (j = 0; j < n; ++j) {
            double val = fabs(mat->data[i][j]);
            if (val > smax) {
                smax = val;
            }
        }
        /* Jeśli cały wiersz składa się z zer, macierz jest osobliwa */
        if (smax == 0.0) {
            free(scale);
            return 1; 
        }
        scale[i] = smax;
    }

    /* Główna pętla eliminacji Gaussa */
    for (k = 0; k < n - 1; ++k) {

        /* Krok 1: Wybór elementu głównego (Scaled Partial Pivoting) */
        int pivot_row = k;
        double max_ratio = fabs(mat->data[k][k]) / scale[k];

        /* Szukamy wiersza z najlepszym elementem głównym poniżej przekątnej */
        for (i = k + 1; i < n; ++i) {
            double ratio = fabs(mat->data[i][k]) / scale[i];
            if (ratio > max_ratio) {
                max_ratio = ratio;
                pivot_row = i;
            }
        }

        /* Sprawdzenie czy macierz nie jest osobliwa (zbyt mały element główny) */
        if (max_ratio * scale[pivot_row] < EPS) {
            free(scale);
            return 1; 
        }

        /* Zamiana wierszy, jeśli znaleziono lepszy kandydat na element główny */
        if (pivot_row != k) {
            swap_rows(mat, k, pivot_row);
            swap_rows(b,   k, pivot_row);

            /* Musimy również zamienić współczynniki skalowania dla tych wierszy */
            double tmp_s = scale[k];
            scale[k] = scale[pivot_row];
            scale[pivot_row] = tmp_s;
        }

        /* Krok 2: Właściwa eliminacja */
        double pivot = mat->data[k][k];

        for (i = k + 1; i < n; ++i) {
            double factor = mat->data[i][k] / pivot;
            mat->data[i][k] = 0.0; // Zerujemy element pod przekątną

            /* Odejmowanie przeskalowanego wiersza k od wiersza i */
            for (j = k + 1; j < n; ++j) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            /* Te same operacje wykonujemy na macierzy wyrazów wolnych B */
            for (j = 0; j < m; ++j) {
                b->data[i][j] -= factor * b->data[k][j];
            }
        }
    }

    /* Sprawdzenie ostatniego elementu na przekątnej po zakończeniu pętli */
    if (fabs(mat->data[n - 1][n - 1]) < EPS) {
        free(scale);
        return 1;
    }

    /* Sprzątanie pamięci */
    free(scale);
    return 0;
}