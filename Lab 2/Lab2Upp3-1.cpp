#include <iostream>
using namespace std;
#include <string>

char* substitute_cstr(const char* input, const char before, const char* after)
{
	string str = input;
	for(int i=0; i < before; i++)
	{
		if (str[i] == 'e')
		{
			str[i] = after[0];
		}
		if (str[i] == 'j')
		{
			str[i] = after[1];
		}
	}

	input = str.c_str();
	cout << input;
	return 0;
}
int main()
{
	const char* input = "Hej på dej";
	char size = strlen(input);
	substitute_cstr(input, size, "ig");


}
