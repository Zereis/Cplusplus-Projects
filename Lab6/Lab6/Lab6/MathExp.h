#pragma once
#ifndef MATHEXP
#define MATHEXP
#include <iostream>
#include <vector>
#include <regex>
#include <stack>
using namespace std;
class MathExp
{
private:
	
public:
	MathExp(string &exp, vector<std::string> tokens);
	int countNegative = 0;
	int expResult;
	int solve(string &expression);
	string assignVariable;


};
#endif