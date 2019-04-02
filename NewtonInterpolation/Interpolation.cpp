#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

void read_from_file(double *&tabX, double *&tabY, int &n) {
	fstream file;
	file.open("points.txt");

	if (file.good()) {
		double *tmpX = new double[n];
		double *tmpY = new double[n];

		for (int i = 0; i < n; i++) {
			file >> tmpX[i] >> tmpY[i];
		}
		
		tabX = tmpX;
		tabY = tmpY;
	}
	else cout << "Unable to open the file!" << endl;

	file.close();
}

void print_data(double *tabX, double *tabY, int n) {
	cout << "\npoints:" << endl;
	for (int i = 0; i < n; i++) {
		cout << "(" << tabX[i] << "," << tabY[i] << ")" << endl;
	}
}

void show_coefficients(double *tabW, int n) {
	cout << "\ncoefficients of newtons polynominal:" << endl;
	for (int i = 0; i < n; i++) {
		cout << tabW[i] << endl;
	}
}

double* Newton_polynominal_coefficients(double *tabX, double *tabY, int n) {
	double *tab = new double[n];
	double *tmp = new double[n];
	
	tab[0] = tabY[0];

	for (int i = 0; i < n; i++) {
		tmp[i] = tabY[i];
	}

	for (int i = 0; i < n - 1; i++) {

		for (int j = 0; j < n - i; j++) {
			tmp[j] = (tmp[j + 1] - tmp[j]) / (tabX[j + 1 + i] - tabX[j]);
		}

		tab[i + 1] = tmp[0];
	}

	return tab;
}

double NewtonsInterpolation(double *tabX, double *tabW, double x, int n)
{
	double result = 0;

	for (int i = 0; i < n; i++)
	{
		double tmp = tabW[i];

		for (int j = 0; j < i; j++)
		{
			tmp *= x - tabX[j];
		}
		result += tmp;
	}
	cout << "Newton's interpolation: " << result << endl;
	return result;
}

double LagrangeInterpolation(double *tabX, double *tabY, double x, int n) {

	double tmp, result = 0;

	for (int i = 0; i < n; i++) {
		tmp = 1;
		for (int j = 0; j < n; j++) {
			if (j != i) {
				tmp *= (x - tabX[j]) / (tabX[i] - tabX[j]);
			}
		}
		result += tmp * tabY[i];
	}
	cout << "Lagrange interpolation: " << result << endl;
	return result;
}

int main() {

	//// INTERPOLATION ///////////////

	double *tabX = NULL;
	double *tabY = NULL;
	double *tabW = NULL;
	int n = 5;

	read_from_file(tabX, tabY, n);
	print_data(tabX, tabY, n);

	tabW = Newton_polynominal_coefficients(tabX, tabY, n);
	show_coefficients(tabW, n);
	
	double x = -0.5;
	cout << "\nx = " << n << endl;
	NewtonsInterpolation(tabX, tabW, x, n);
	LagrangeInterpolation(tabX, tabY, x, n);
	
	 
	system("pause");
	return 0;
}