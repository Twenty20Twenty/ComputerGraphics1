#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>

using namespace std;

double* setMatrix(double* M, int len) {
	for (int i = 0; i < len * len; i++)
		M[i] = ((int)(rand() % 100));

	return M;
}

void printMatrix(double* M, int len) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++)
			cout << M[i * len + j] << "\t";
		cout << endl;
	} cout << "-------------------" << endl;
}


double det(double* M, int len) {

	double det = M[0 + 0];
	if (len > 1) {
		for (int i = 0; i < len - 1; i++)
			for (int j = i + 1; j < len; j++) {
				double tmp = M[j*len+i];
				for (int k = i; k < len; k++)
					M[j*len+k] -= ((M[i*len+k] / M[i*len+i]) * tmp);
			}
	}
	for (int i = 1; i < len; i++)
		det *= M[i*len+i];
	return det;
}



void laba1() {
	int lenArr[11] = { 2,4,8,16,32,64,128,256,512, 1024, 2048 };
	int iterations = 11;
	double* Matrix;
	int len;
	ofstream f;
	f.open("resultsCPU.txt");
	if (f.is_open()) {
		f << "len: \tTime:\n";
		cout << "len: \tTime:\n";
		for (int k = 0; k < iterations; k++) {

			len = lenArr[k];

			Matrix = new double[len*len];
			Matrix = setMatrix(Matrix, len);
			//printMatrix(Matrix, len);

			auto start1 = chrono::high_resolution_clock::now();
			//cout << "det is " << det(Matrix, len) << endl;
			det(Matrix, len);
			auto end1 = chrono::high_resolution_clock::now();

			double time_taken1 = chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count();
			time_taken1 *= 1e-9;

			cout << len << " \t" << time_taken1 << endl;
			f << len << " \t" << time_taken1 << endl;

			delete[] Matrix;
		}
	}
}

int main() {
	laba1();
}