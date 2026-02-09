#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>

#include "error.h"

using namespace std;

// ALGORITHM 3
double fun3(double x, double y, double z)
{
	return 1.3498 * z + 2.2362 * y - 2.348 * x * y;
}

// LOAD TU
void loadTU(double x, double &Tout, double &Uout)
{
	string filename;

	if (fabs(x) <= 1)
		filename = "data/dat_X_1_1.dat";
	else if (x < -1)
		filename = "data/dat_X00_1.dat";
	else
		filename = "data/dat_X1_00.dat";

	ifstream file(filename);
	if (!file.is_open())
		throw ErrorNoFile(filename);

	vector<double> X, T, U;
	double a, b, c;
	while (file >> a >> b >> c)
	{
		X.push_back(a);
		T.push_back(b);
		U.push_back(c);
	}

	int n = X.size();

	for (int i = 0; i < n; i++)
		if (X[i] == x)
		{
			Tout = T[i];
			Uout = U[i];
			return;
		}

	for (int i = 0; i < n - 1; i++)
		if (X[i] <= x && x <= X[i + 1])
		{
			double k = (x - X[i]) / (X[i + 1] - X[i]);
			Tout = T[i] + (T[i + 1] - T[i]) * k;
			Uout = U[i] + (U[i + 1] - U[i]) * k;
			return;
		}

	throw ErrorRange("X outside table");
}

// T / U wrappers
double Trz(double x, double X, double Y, double Z)
{
	try
	{
		double T, U;
		loadTU(x, T, U);
		return T;
	}
	catch (...)
	{
		return fun3(X, Y, Z);
	}
}

double Urz(double x, double X, double Y, double Z)
{
	try
	{
		double T, U;
		loadTU(x, T, U);
		return U;
	}
	catch (...)
	{
		return fun3(X, Y, Z);
	}
}

// SRZ
double Srz(double x, double y, double z, double X, double Y, double Z)
{
	if (x > y)
		return Trz(x, X, Y, Z) + Urz(z, X, Y, Z) - Trz(y, X, Y, Z);
	else
		return Trz(y, X, Y, Z) + Urz(y, X, Y, Z) - Urz(z, X, Y, Z);
}

// ALGORITHM 2
double Gold1(double x, double y)
{
	if (x > y && fabs(y) > 0.1)
		return x / y;
	if (x <= y && fabs(x) > 0.1)
		return y / x;
	if (x < y && fabs(x) > 0.1)
		return 0.15;
	if (y == 0)
		return 0.1;
	return 0.1;
}

double Glr1(double x, double y)
{
	return (fabs(x) < 1) ? x : y;
}

double Grs1(double x, double y, double X, double Y, double Z)
{
	return 0.14 * Srz(x + y, Gold1(x, y), Glr1(x, x * y), X, Y, Z) +
	       1.83 * Srz(x - y, Gold1(y, x / 5), Glr1(4 * x, x * y), X, Y, Z) +
	       0.83 * Srz(x, Glr1(y, x / 4), Gold1(4 * y, y), X, Y, Z);
}

double fun2(double x, double y, double z)
{
	return x * Grs1(x, y, x, y, z) +
	       y * Grs1(y, z, x, y, z) +
	       z * Grs1(z, x, x, y, z);
}

// ALGORITHM 1
double Gold(double x, double y)
{
	if (x > y && y != 0)
		return x / y;
	if (x < y && x != 0)
		return y / x;
	throw ErrorRange("Division not possible in Gold");
}

double Glr(double x, double y)
{
	if (fabs(x) < 1)
		return x;
	if (fabs(x) >= 1 && fabs(y) < 1)
		return y;

	double val = x * x + y * y - 4;
	if (val <= 0)
		throw ErrorRange("sqrt negative in Glr");

	double r = sqrt(val);
	if (fabs(x) >= 1 && fabs(y) >= 1 && r > 0.1)
		return y / r;

	throw ErrorRange("Glr threshold not satisfied");
}

double Grs(double x, double y, double X, double Y, double Z)
{
	return 0.1389 * Srz(x + y, Gold(x, y), Glr(x, x * y), X, Y, Z) +
	       1.8389 * Srz(x - y, Gold(y, x / 5), Glr(5 * x, x * y), X, Y, Z) +
	       0.83 * Srz(x - 0.9, Glr(y, x / 5), Gold(5 * y, y), X, Y, Z);
}

double fun1(double x, double y, double z)
{
	double A = Grs(y, z, x, y, z);
	double B = Grs(x, z, x, y, z);
	double C = Grs(x, z, x, y, z);

	return x * x * A + y * y * B + 0.33 * x * y * C;
}

double fun(double x, double y, double z)
{
	try
	{
		return fun1(x, y, z); // Algorithm1
	}
	catch (ErrorRange &)
	{
		return fun2(x, y, z); // Algorithm2
	}
	catch (ErrorNoFile &)
	{
		return fun3(x, y, z); // Algorithm3
	}
	catch (...)
	{
		return fun3(x, y, z); // fallback
	}
}

int main()
{
	double x, y, z;
	cout << "Enter x y z: ";
	cin >> x >> y >> z;

	double f = fun(x, y, z);

	cout << "fun = " << f << endl;
}
