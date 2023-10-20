#include "PersonMedTel.h"
#include <stdio.h>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>
void PersonMedTel::PrintPerson()
{
	cout << "Name: " + name + " " + "Address: " + adress + " " + "Number: " + nummer << endl;
}

PersonMedTel::PersonMedTel(const string name, const string adress, const string nummer)
{
	this->name = name;
	this->adress = adress;
	this->nummer = nummer;
}


PersonMedTel::~PersonMedTel()
{
	
}
