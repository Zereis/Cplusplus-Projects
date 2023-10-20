#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  


#include "String.h"
#include <iostream>
#include <stdio.h>
#include <crtdbg.h>
#include <string>
#include <iostream>
#include <cassert>
#include <utility>
String::~String()
{
	delete[] charArray;
}

String::String()
{
	charSize = 0;
	charCap = 1;
	charArray = new char[charSize + 2];
	charArray[0] = '\0';
	Invariant();
}

String::String(const String & rhs)
{
	charArray = new char[strlen(rhs.charArray) + 1];
	strcpy_s(charArray, strlen(rhs.charArray) + 1, rhs.charArray);

	Invariant();
}

String::String(const char * cstr)
{

	if (cstr != nullptr)
	{
		charSize = strlen(cstr);
		if (charSize == 0)
		{
			strcpy_s(charArray, charSize , cstr);
		}
		else
		{
			charCap = charSize;
			charArray = new char[charSize + 1];
			strcpy_s(charArray, charSize + 1, cstr);
		}
	}
	
	Invariant();
}
void String::Invariant()
{
	assert(charSize <= charCap);//Obs! Ändra och lägg till så det passar er klass
}
String & String::operator=(const String & rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	else if (this != &rhs)
	{
	
		if (charSize == rhs.charSize)
		{
			strcpy_s(charArray, strlen(rhs.charArray) + 1, rhs.charArray);
			return *this;
		}
		else
		{
			delete[]charArray;
			charSize = rhs.size();
			charCap = charSize;
			charArray = new char[strlen(rhs.charArray) + 2];
			strcpy_s(charArray, rhs.charSize + 1, rhs.charArray);
			return *this;
		}
	}

}

char & String::operator[](size_t i)
{
	return charArray[i];
}

const char & String::operator[](size_t i) const
{
	return charArray[i];
}

size_t String::size() const
{
	return charSize;
}

size_t String::capacity() const
{
	return charCap;
}

void String::push_back(char c)
{
	if (strlen(charArray) + 1 > charCap)
	{
		increaseCap(charArray);
	}

	int newLength = strlen(charArray);

	if (c == 0 && charSize == 0)
	{
		charArray[charSize] = ' ';
		charArray[charSize + 1] = '\0';
		charSize = strlen(charArray);
	}
	else if (c != 0 && charSize == 0)
	{
		charArray[charSize] = c;
		charArray[charSize + 1] = '\0';
		charSize = strlen(charArray);
	}
	else if (c == 0 && charSize > 0)
	{
		char* newArray = new char[newLength + 2];

		for (int i = 0; i < charSize; i++)
		{
			newArray[i] = charArray[i];
		}
		
		delete[] charArray;
		newArray[newLength] = ' ';
		newArray[newLength + 1] = '\0';
		charArray = newArray;
		charSize = strlen(charArray);
	}
	else 
	{
		if (strlen(charArray) + 1 < charCap)
		{
			charArray[newLength] = c;
			charArray[newLength + 1] = '\0';
			charSize = strlen(charArray);
		}
		else
		{
			char* newArray = new char[newLength + 2];

			for (int i = 0; i < charSize; i++)
			{
				newArray[i] = charArray[i];
			}

			delete[] charArray;
			newArray[newLength] = c;
			newArray[newLength + 1] = '\0';

			charArray = newArray;
			charSize = strlen(charArray) + 1;
		}

	}

}	

void String::increaseCap(char * cstr)
{
	if (charSize < charCap)
		return;

	string cap = cstr;
	int newCharCap =  charCap *2;
	char * newArray = new char[newCharCap];

	for (int i = 0; i < charSize; i++)
	{
		newArray[i] = cstr[i];
	}
	newArray[strlen(cstr)] = '\0';

	charCap = newCharCap;

	delete[] charArray;
	charArray = newArray;
}

void String::print()
{
	cout << charArray;
}


const char * String::data() const
{
	return charArray;
}

bool operator==(const String & lhs, const String & rhs)
{
	return strcmp(lhs.charArray, rhs.charArray)==0;
}

bool operator!=(const String & lhs, const String & rhs)
{
	return strcmp(lhs.charArray, rhs.charArray)!= 0;
}
std::ostream& operator<< (std::ostream& out, const String& rhs) 
{ 
	for (size_t i = 0; i < rhs.size(); ++i)
		out << rhs[i]; 
	return out;
}