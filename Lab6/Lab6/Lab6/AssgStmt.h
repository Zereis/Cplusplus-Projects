#pragma once
#ifndef ASSGSTMT
#define ASSSGTMT
#include <iostream>
#include <vector>
#include <regex>
using namespace std;
class Assign
{
private:

public:
	string variable;
	string equal;
	Assign(string ch, vector<std::string> tokens);
	string temp;
	int result;
};
#endif