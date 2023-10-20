#include "Interpreter.h"
#include "PrintStmt.h"
#include "ConfigStmt.h"
#include "AssgStmt.h"
#include "MathExp.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream>
#include <regex>

using namespace std;

void parse_Exp​(const string tokens, Config& config)
{
	regex regConfigDec("(config dec)");
	regex regConfigHex("(config hex)");
	regex regConfigBin("(config bin)");
	if (regex_match(tokens.begin(), tokens.end(), regConfigDec))
	{
		config.config = "1";
		config.loadConfig();
	}
	else if (regex_match(tokens.begin(), tokens.end(), regConfigHex))
	{
		config.config = "2";
		config.loadConfig();
	}
	else if (regex_match(tokens.begin(), tokens.end(), regConfigBin))
	{
		config.config = "3";
		config.loadConfig();
	}

}
void parse_Stmt​(const std::vector<std::string>& tokens, Config& configs, vector <int> &result, ostream& out_stream)
{

	regex regConfig("(config)(.*)");
	regex regAssign("([a-z] =)(.*)");
	regex regAssignVariable("[a-z] = [a-z]");
	regex regPrint("(print)(.*)");
	regex regPrintAssign("(print) [a-z]");
	for (int i = 0; i < tokens.size(); i++)
	{
		if (regex_match(tokens[i].begin(), tokens[i].end(), regConfig))
		{
		
			string changeConfig = tokens[i];
			parse_Exp​(changeConfig, configs);
		}
		else if (regex_match(tokens[i].begin(), tokens[i].end(), regAssignVariable))
		{
			string compare = tokens[i];


		}
		else if (regex_match(tokens[i].begin(), tokens[i].end(), regAssign))
		{
			//string assignToken = tokens[i];
			//Assign assign(assignToken, tokens);

			//if (configs.config == "1")
			//{
			//	out_stream << assign.result << endl;
			//}
			//else if (configs.config == "2")
			//{

			//	out_stream << std::hex << assign.result << endl;
			//}
			//else if (configs.config == "3")
			//{
			//	out_stream << std::bitset<32>(assign.result).to_string() << endl;
			//}
		}
		else if (regex_match(tokens[i].begin(), tokens[i].end(), regPrintAssign))
		{
			string compare = tokens[i];
			regex remove("print");
			regex blankSpace("\\s");
			compare = regex_replace(compare, remove, "");
			compare = regex_replace(compare, blankSpace, "");

			for (int j = 0; j < tokens.size(); j++)
			{
				string temp = tokens[j];
				if (compare[0] == temp[0])
				{
					MathExp math(temp, tokens);
					if (configs.config == "1")
					{
						out_stream << math.expResult << endl;
					}
					else if (configs.config == "2")
					{

						out_stream << std::hex << math.expResult << endl;
					}
					else if (configs.config == "3")
					{
						out_stream << std::bitset<32>(math.expResult).to_string() << endl;
					}
					
				}
			}

		}
		else if (regex_match(tokens[i].begin(), tokens[i].end(), regPrint))
		{

			string printAns = tokens[i];
			Print print(printAns, tokens);
			if (configs.config == "1")
			{
				out_stream << print.printResult << endl;
			}
			else if (configs.config == "2")
			{
				
				out_stream << std::hex << print.printResult << endl;
			}
			else if (configs.config == "3")
			{
				out_stream << std::bitset<32>(print.printResult).to_string() << endl;
			}
		}
	}

}
Interpreter::Interpreter(std::ostream & out_stream)
{

	fstream myfile("example.txt");
	string line;
	if (myfile.is_open())
	{

		while (getline(myfile, line))
		{
			stringstream ss(line);
			while (getline(ss, line, ','))
			{
				tokens.push_back(line);
		
			}
		}
		ofstream test("example.txt");
		test.is_open();
		test.close();
	}
	myfile.close();
	evaluate(tokens, out_stream);


	//for (auto a : result)
	//{
	//	out_stream << a << endl;
	//	//out_stream << std::hex << a << endl;
	//	//out_stream << std::bitset<32>(a).to_string() << endl;
	//}


}

void Interpreter::evaluate(const std::vector<std::string>& tokens, ostream & out_stream)
{
	Config config;
	parse_Stmt​(tokens, config, result, out_stream);
}




