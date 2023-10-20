#pragma once
#include "Person.h"
#include <iostream>
using namespace std;

class PersonMedTel : public Person
{
private:

public:
	string nummer;
	void PrintPerson();
	PersonMedTel(const string name = "?", const string adress = "?", const string nummer = "?");
	virtual ~PersonMedTel();
};