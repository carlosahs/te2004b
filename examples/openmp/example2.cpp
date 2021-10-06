// =================================================================
//
// File: example2.cpp
// Author: Pedro Perez
// Description: This file implements the multiplication of a matrix
//				by a vector using OpenMP.
//              To compile: g++ example2.cpp -fopenmp
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <climits>
#include <omp.h>
#include "utils.h"

const int RENS = 30000; //1e5
const int COLS = 30000;

using namespace std;

void matrixXVector(int *m, int *b, int *c) {
	int i, j, acum;

	for (i = 0; i < RENS; i++) {
		acum = 0;
		#pragma omp parallel for shared(m, b, i) reduction(+:acum)
		for (j = 0; j < COLS; j++) {
			acum += (m[(i * COLS) + j] * b[i]);
		}
		c[i] = acum;
	}
}

int main(int argc, char* argv[]) {
	int i, j, *m, *b, *c;
	double ms;

	m = new int[RENS* COLS];
	b = new int[RENS];
	c = new int[RENS];

	for (i = 0; i < RENS; i++) {
		for (j = 0; j < COLS; j++) {
			m[(i * COLS) + j] = (j + 1);
		}
		b[i] = 1;
	}

	std::cout << "Starting...\n";
	ms = 0;
	for (i = 0; i < N; i++) {
		start_timer();

		matrixXVector(m, b, c);

		ms += stop_timer();
	}
	display_array("c:", c);
	std::cout << "avg time =  " << setprecision(5) << (ms / N) << "\n";

	delete [] m;
	delete [] b;
	delete [] c;
	return 0;
}
