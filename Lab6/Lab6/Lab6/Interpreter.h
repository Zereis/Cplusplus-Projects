#pragma once
#ifndef INTERPRETER
#define INTERPRETER
#include <iostream>
#include <vector>
#include <regex>
#include "ConfigStmt.h"
using namespace std;
class Interpreter
{
private:
	
public:
	Interpreter(std::ostream& out_stream);
	void evaluate(const std::vector<std::string>& tokens, ostream& out_stream);
	vector<string> tokens;
	vector <int> result;

};
#endif

