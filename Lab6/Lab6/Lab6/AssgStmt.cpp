#include "AssgStmt.h"
#include <bitset>
#include "MathExp.h"

Assign::Assign(string ch, vector<std::string> tokens)
{
	MathExp solve(ch, tokens);
	result = solve.expResult;
	temp = solve.assignVariable;

}
