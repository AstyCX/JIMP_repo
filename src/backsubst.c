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
	if (x == NULL || mat == NULL || b == NULL) {
    	    return 2;
    	}

    	int i, j;
    	int n = mat->r;

    	
    	if (mat->r != mat->c || mat->r != b->r || mat->r != x->r || b->c != 1 || x->c != 1) {
    	    return 2;
    	}
				int i;
				for (i =0; i < x->r; i++) {
								x->data[i][0] = b->data[i][0];
				}

				return 0;
}


