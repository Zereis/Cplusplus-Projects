#include "Person.h"
#include "Personregister.h"
#include <iostream>
using namespace std;
#include <stdio.h>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>

Person::Person(const string name, const string adress) 
{
	this->name = name;
	this->adress = adress;

}
void Person::PrintPerson()
{
	string printName = this->name;
	string printAdress = this->adress;
	cout << "Name: " + printName + ", " + "Address: " + printAdress << endl;

}

Person::~Person()
{

}
