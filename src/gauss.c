#include "gauss.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int n = mat->r;    
    int i, j, k;

	// Sprawdzamy czy macierz jest kwardratowa i czy wektor b ma odpowiedni wymiar
	if (mat->r != mat->c || b->r != mat->r) {
        return 1;
    }

	for (int k = 0; k < n-1; ++k) {
		if (mat->data[k][k] == 0.0) {
			return 1; // Macierz osobliwa
		}

		for (int i = k + 1; i < n; ++i) {
			double factor = mat->data[i][k] / mat->data[k][k];
			for (j = k; j < n; ++j) {
				mat->data[i][j] -= factor * mat->data[k][j];
			}

			// Aktualizujemy wektor b
			b->data[i][0] -= factor * b->data[k][0];
		}
	}

	return 0;
}

