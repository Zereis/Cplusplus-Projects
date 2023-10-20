#include "MathExp.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <regex>
using namespace std;
int precedence(char op) {
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

int applyOp(int a, int b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	}
}
int calcuate(string& tokens, int countNegative)
{
	int i;
	stack <int> values;
	stack <char> ops;

	for (i = 0; i < tokens.length(); i++) {


		if (tokens[i] == ' ')
			continue;

		else if (tokens[i] == '(') {
			ops.push(tokens[i]);
		}
		else if (isalpha(tokens[i]) || tokens[i] == '=' && i < 3)
		{
			continue;
		}
		else if (isdigit(tokens[i])) {
			int val = 0;

			while (i < tokens.length() &&
				isdigit(tokens[i]))
			{
				val = (val * 10) + (tokens[i] - '0');
				i++;
			}

			values.push(val);
			i--;
		}
		else if (tokens[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			if (!ops.empty())
				ops.pop();
		}
		else if (tokens[i] == '-' && isdigit(tokens[i + 1]))
		{
			countNegative++;
		}

		else
		{
			while (!ops.empty() && precedence(ops.top())
				>= precedence(tokens[i])) {
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			ops.push(tokens[i]);
		}
	}

	while (!ops.empty()) {
		if (countNegative == 0)
		{
			int val2 = values.top();
			values.pop();

			int val1 = values.top();
			values.pop();

			char op = ops.top();
			ops.pop();

			values.push(applyOp(val1, val2, op));
		}
		if (countNegative == 1)
		{
			int val2 = values.top();
			values.pop();

			int val1 = values.top();
			values.pop();

			char op = ops.top();
			ops.pop();

			values.push(applyOp(val1, -val2, op));
		}
		if (countNegative == 2)
		{
			int val2 = values.top();
			values.pop();

			int val1 = values.top();
			values.pop();

			char op = ops.top();
			ops.pop();

			values.push(applyOp(-val1, -val2, op));
		}
	}


	return values.top();
}
void parseExp(string& exp, string & assignVariable, vector<std::string> tokens, int countNegative)
{
	regex assign("([a-z] =)(.*)");
	regex variable("[A-Za-z]");
	regex equal("=");
	regex regAssignVariable("[a-z] = [a-z]");
	regex regPrintAssign("(print) [a-z]");
	regex regPrint("(print)(.*)");


	if (regex_match(exp, assign))
	{
		for (int i = 0; i < exp.size(); i++)
		{
			
			if (isalpha(exp[i]) && i > 0)
			{
				string test;
				test.push_back(exp[i]);
				regex remove(test);
				string replace;
				int x = 0;
			
	

				for (int j = 0; j < tokens.size(); j++)
				{
					string temp = tokens[j];

					if (isalpha(temp[x]) && temp[x] != test[0])
							continue;

						else if (temp[x] == ' ')
							continue;

						else if (temp[x] == '=')
							continue;

						else if (temp[x] == '*')
							continue;

						else if (temp[x] == '(')
							continue;

						else if (temp[x] == ')')
							continue;

						else if (temp[x] == '/')
							continue;

						else if (temp[x] == '-')
							continue;

						else if (isdigit(temp[x]))
							continue;

						else if (temp[x] == test[0])
						{
							if (regex_match(tokens[j].begin(), tokens[j].end(), regAssignVariable))
							{
								for (int k = 0; k < tokens.size(); k++)
								{
									if (tokens[k][0] == temp[4])
									{
										temp = tokens[k];

									}
								}
								

							}
							int result = calcuate(temp, countNegative);
							char c = '0' + result;
							replace.push_back(c);

	
							exp = regex_replace(exp, remove, replace);
							break;
						}
					x++;
	
				}
			}
		}
	}
	else if (regex_match(exp, regPrint))
	{
		regex remove("print");
		exp = regex_replace(exp, remove, "");
		
		for (int i = 0; i < exp.size(); i++)
		{
			if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
			{
				if (!isdigit(exp[i + 2]) && !isalpha(exp[i + 2]) && exp[i + 2] == '-' && !isdigit(exp[i + 3]))
				{
					// cout << exp[i + 2]; skriver ut felet
					cout << "Something is wrong with your expression";
					throw("Error");
					
				}
				break;
			}

		}
	}

}
MathExp::MathExp(string& exp, vector<std::string> tokens)
{
	parseExp(exp, assignVariable, tokens, countNegative);
	expResult = solve(exp);
}

int MathExp::solve(string& tokens)
{
	int i;
	stack <int> values;
	stack <char> ops;

	for (i = 0; i < tokens.length(); i++) {


		if (tokens[i] == ' ')
			continue;


		else if (tokens[i] == '(') {
			ops.push(tokens[i]);
		}
		else if (isalpha(tokens[i]) || tokens[i] == '=' && i < 3)
		{
			continue;
		}
		else if (isdigit(tokens[i])) {
			int val = 0;

			while (i < tokens.length() &&
				isdigit(tokens[i]))
			{
				val = (val * 10) + (tokens[i] - '0');
				i++;
			}

			values.push(val);
			i--;
		}
		else if (tokens[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			if (!ops.empty())
				ops.pop();

		}
		else if (tokens[i] == '-' && isdigit(tokens[i + 1]))
		{
			countNegative++;
		}

		else
		{
			while (!ops.empty() && precedence(ops.top())
				>= precedence(tokens[i])) {

				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			ops.push(tokens[i]);
		}
	}

	while (!ops.empty()) {
		if (countNegative == 0)
		{
			int val2 = values.top();
			values.pop();

			int val1 = values.top();
			values.pop();

			char op = ops.top();
			ops.pop();

			values.push(applyOp(val1, val2, op));
		}

		if (countNegative == 1)
		{
			int val2 = values.top();
			values.pop();

			int val1 = values.top();
			values.pop();

			char op = ops.top();
			ops.pop();

			values.push(applyOp(val1, -val2, op));
		}
		if (countNegative == 2)
		{
			int val2 = values.top();
			values.pop();

			int val1 = values.top();
			values.pop();

			char op = ops.top();
			ops.pop();

			values.push(applyOp(-val1, -val2, op));
		}
		else if (countNegative !=  0 && countNegative != 1 && countNegative != 2)
		{
			cout << "There is something wrong with your expression";
			break;
		}
	}

	return values.top();
}
