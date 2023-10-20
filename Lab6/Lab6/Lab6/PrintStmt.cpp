#include "PrintStmt.h"
#include <bitset>
#include "MathExp.h"

Print::Print(string ch, vector<std::string> tokens)
{
	MathExp solve(ch, tokens);
	printResult = solve.expResult;
}


