#include "backsubst.h"
#include <stdio.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
				/**
				 * Tutaj należy umieścić właściwą implemntację.
				 */

				/* To ponizej jest przepisaniem b do x. Nalezy to poprawic! */


				// Sprawdzenie, czy wskaźniki na macierze i wektory nie są NULL
	if (x == NULL || mat == NULL || b == NULL) {
    	    return 2;
    	}

    	int i, j;
    	int n = mat->r; // Liczba wierszy

		// Sprawdzenie wymiarów
    	// a) mat (A) musi być macierzą kwadratową (mat->r == mat->c)
   	 	// b) wszystkie macierzemuszą mieć tę samą liczbę wierszy (mat->r == b->r == x->r)
    	// c) wektory b i x muszą być wektorami kolumnowymi (b->c == 1 && x->c == 1)
    	if (mat->r != mat->c || mat->r != b->r || mat->r != x->r || b->c != 1 || x->c != 1) {
    	    return 2;
    	}
		// Iterujemy od ostatniego wiersza (n-1) do pierwszego (0)
				for (i = n - 1; i >= 0; i--) {
        double s = 0.0;  // Suma iloczynów (a_ij * x_j) dla j > i

/* Obliczanie sumy elementów */
        // Sumujemy elementy, które już zostały obliczone w poprzednich krokach (x_j, gdzie j > i)
        for (j = i + 1; j < n; j++) {
            s += mat->data[i][j] * x->data[j][0];
        }
/* Dzielenie przez element diagonalny */
        // Sprawdzenie, czy element na diagonali nie jest zerem (warunek osobliwości)
        if (mat->data[i][i] == 0.0) {
            return 1;  // Macierz osobliwa
        }
/* Wyliczenie wyniku x_i */
        // Wzór: x_i = (b_i - Suma(a_ij * x_j)) / a_ii
        x->data[i][0] = (b->data[i][0] - s) / mat->data[i][i];
    }

				return 0;
}


