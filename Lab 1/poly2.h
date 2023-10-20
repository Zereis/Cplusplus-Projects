#pragma once
#ifndef POLY2_H
#define POLY2_H

class Poly2
{
	float a, b, c;

public:

	/*
	 * Constructor
	 */
	Poly2(float a, float b, float c);

	/*
	 * Evaluate y(x)
	 */
	float eval(float x);

	/*
	 * Find roots, i.e. x when y(x) = 0
	 */
	void findRoots(float &x1, float &x2);

	/*
	 * Destructor:
	 * not needed since no dynamic memory has been allocated,
	 */
};

#endif