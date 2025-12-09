#include "gauss.h"
#include <math.h> 

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b){
    int i, j, k;
	int n = mat->r;
	double M;
	double max_val;
	int max_row;

	for(k = 0; k < n; k++){
		max_val = 0.0;
		max_row = i;

		for(i = k; i < n; i++){
			if(fabs(mat->data[i][k]) > max_val) {
				max_val = fabs(mat->data[i][k]);
				max_row = i;
			}
		}
		if (max_val < 1e-12){
			return 1;
		}

		if (max_row != k) {
			double *temp_row_A = mat->data[k];
			mat->data[k] = mat->data[max_row];
			mat->data[max_row] = temp_row_A;

			double *temp_row_B = mat->data[k];
			mat->data[k] = mat->data[max_row];
			mat->data[max_row] = temp_row_B;
 
		}

		//Eliminacja Gaussa
		for(i = k + 1; i< n; i++){
			M = mat->data[i][k] / mat->data[k][k];

			for(j = k; j < n; j++) {
				mat->data[i][j] = mat->data[i][j] - M * mat->data[k][j];
			}
			b->data[i][0] = b->data[i][0] - M * b->data[k][0];
		}
	}

		return 0;
}

