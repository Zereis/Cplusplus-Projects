#include <iostream>
using namespace std;
int main()
{
	int eratoshenes[29] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};

	for (int i = 0; i < 29; i++)
	{
		if (eratoshenes[i] % 2 != 1 && eratoshenes[i] != 2)
		{
			eratoshenes[i] = 0;
		}
		if (eratoshenes[i] != 0)
		{
			cout << eratoshenes[i] << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < 29; i++)
	{
		if (eratoshenes[i] % 3 != 2 && eratoshenes[i] != 3 && eratoshenes[i] % 3 != 1)
		{
			eratoshenes[i] = 0;
		}
		if (eratoshenes[i] != 0)
		{
			cout << eratoshenes[i] << " ";
		}
	}
	cout << endl;
	for (int i = 0; i < 29; i++)
	{
		if (eratoshenes[i] % 5 != 2 && eratoshenes[i] != 5 && eratoshenes[i] % 5 != 1 && eratoshenes[i] % 5 != 3 && eratoshenes[i] % 5 != 4)
		{
			eratoshenes[i] = 0;
		}
		if (eratoshenes[i] != 0)
		{
			cout << eratoshenes[i] << " ";
		}
	}
}


