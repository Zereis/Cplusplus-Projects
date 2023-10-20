#include "poly2.h"
#include <cmath>
#include <iostream>
using namespace std;

Poly2::Poly2(float a, float b, float c)
{
	this->a = a;
	this->b = b;
	this->c = c;

}

float Poly2::eval(float x)
{
	float yx = x;
	
	cout << "y(" << yx << ") = " << a << "*" << x << "^2" << " + " << b << "*" << x << " + " << c << endl;
	return yx;
}

void Poly2::findRoots(float &x1, float &x2)
{
	float root1;
	float root2;

	root1 = b - sqrt(pow(b, 2) - 4 * a * c) / 2 * a;
	root2 = b + sqrt(pow(b, 2) - 4 * a * c) / 2 * a;

	x1 = root1;
	x2 = root2;
}
