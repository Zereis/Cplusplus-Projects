#pragma once
#ifndef CONFIGSTMT
#define CONFIGSTMT
#include <iostream>
#include <vector>
#include <regex>
#include "Interpreter.h"
using namespace std; 
class Config 
{
private:

public:
	Config();
	void loadConfig();
	string config = "0";
	string dec;
	string hex;
	string bin;
};
#endif