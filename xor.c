#include <stdlib.h>
#include <stdio.h>

// A simple XOR net with one hidden layer

// Modifies a matrix so each cell is either b_ij or a depending on which is
// greater.
void max(int a, int *b, int bhei, int bwid) {
	for (int i = 0; i < bhei; i++) {
		for (int j = 0; j < bwid; j++) {
			if (*(b+i*bwid+j) < a) {
				*(b+i*bwid+j) = a;
			}
		}
	}
}

// Calulate the content of field in matrix
int cfiel(int *a, int *b, int awid, int bwid, int i, int j) {
	int s = 0;
	for (int k = 0; k < awid; k++) {
		s += *(a+awid*i+k) * *(b+bwid*k+j);
	}

	return s;
}

struct mtret {
	int *mtx;
	int hei;
	int wid;
};

// Returns 1 on error (when awid != bhei) and 0 on success.
int matml(int *a, int ahei, int awid, int *b, int bhei, int bwid, struct mtret* ret) {
	if (awid != bhei) return 1;

	ret->hei = ahei;
	ret->wid = bwid;
	int **mtx = malloc(sizeof(int*) * ret->hei);
	for (int i = 0; i < ret->hei; i++) {
		mtx[i] = malloc(sizeof(int*)*ret->wid);
	}
	ret->mtx = &mtx[0][0];
	
	for (int i = 0; i < ret->hei; i++) {
		for (int j = 0; j < ret->wid; j++) {
			 *(ret->mtx+i*ret->wid+j) = cfiel(a, b, awid, bwid, i, j);
		}
	}

	return 0;
}

// Modifies matrix a with the result of adding a and b together.
void matad(int *a, int *b, int hei, int wid) {
	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			*(a+i*wid+j) = *(a+i*wid+j) + *(b+i*wid+j);
		}
	}
}

void prmtx(int *mtx, int hei, int wid) {
	for (int i = 0; i < hei; i++) {
		for (int j = 0; j < wid; j++) {
			printf("%d", *(mtx+i*wid+j));
			if (j%2) {
				printf("\n");
			} else {
				printf(" ");
			}
		}
	}
	printf("\n");
}

int main() {
	int x[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}}; // Inputs to the net. Every row is a point.
	int hwei[2][2] = {{1, 1}, {1, 1}}; // A weight matrix representing mapping from x to h
	int bias[4][2] = {{0, -1}, {0, -1}, {0, -1}, {0, -1}}; // Bias matrix
	int ywei[2][1] = {{1}, {-2}}; // Weight vector. A mapping from h to output.
								  
	struct mtret h = {};
	struct mtret y = {};
									
	matml(&x[0][0], 4, 2, &hwei[0][0], 2, 2, &h);
	matad(h.mtx, &bias[0][0], 4, 2);
	max(0, h.mtx, h.hei, h.wid);
	matml(h.mtx, h.hei, h.wid, &ywei[0][0], 2, 1, &y);
	prmtx(y.mtx, y.hei, y.wid);

	return 0;
}
