#pragma once
#ifndef PRINTSTMT
#define PRINTSTMT
#include <iostream>
#include <vector>
#include <regex>
#include "ConfigStmt.h"
#include <stack>
using namespace std;
class Print : public Config
{
private:

public:
	
	Print(string ch, vector<std::string> tokens);
	int printResult;
};
#endif