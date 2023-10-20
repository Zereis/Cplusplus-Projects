#include "Interpreter.h"
#include "PrintStmt.h"
#include "ConfigStmt.h"
#include "MathExp.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <regex>
using namespace std;


int main()
{
	fstream myfile("example.txt");	
	myfile.is_open();
	Interpreter test(myfile);
	myfile.close();


}

