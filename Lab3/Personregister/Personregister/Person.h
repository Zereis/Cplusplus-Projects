#pragma once
#include <iostream>
using namespace std;

class Person
{ 
private:
	
public:
	string name;
	string adress;
	Person(const string name = "?", const string adress = "?");
	virtual void PrintPerson();
	~Person();
	
};
