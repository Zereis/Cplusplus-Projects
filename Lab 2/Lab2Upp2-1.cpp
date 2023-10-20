#include <iostream>
using namespace std;
#include <string>

void substitute_str(std::string& iostring, const std::string& before, const std::string& after)
{
	int startPos = 0;
	int count = 0;
	

	if (before.compare(after) != 0)
	{
		while ((startPos = iostring.find(before, startPos)) != string::npos)
		{
			iostring.replace(startPos, before.length(), after);
		}
		cout << iostring << endl;
	}

	cout << iostring << endl;
}
int main()
{
	//string input = "Hej på dej";
	//substitute_str(input, "ej", "ig");

	string input = "Hejjj";
	substitute_str(input, "ej", "asd");
}
