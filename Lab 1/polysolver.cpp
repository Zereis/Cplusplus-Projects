#include <iostream>
#include "poly2.h"
using namespace std;

int main(int argc, char** argv)
{
	std::cout << "Root-finding started..." << std::endl;
	
	
	float z;
	float v;
	float c;

	float x;
	cin >> z >> v >> c;

	cin >> x;
	Poly2 findRoots(z,v,c);
	float x1;
	float x2;
	findRoots.eval(x);
	findRoots.findRoots(x1, x2);
	cout << x1 << endl; 
	cout << x2 << endl;

	return 0;
}