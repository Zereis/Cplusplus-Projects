#pragma once
#ifndef PERSONREGISTER
#define PERSONREGISTER
#include "Person.h"
#include <iostream>
using namespace std;

class PersonReg
{
private:
	int maxStorlek;
	Person* person;

	int currentIndex = 0;
	int checknames = 0;
	string tempName;
	string tempAdress;
	string comparesök;
	
public:
	int test;
	PersonReg(const int maxStorlek);
	bool LäggTill(const Person* const);
	bool LäggTillTest(const string& namn, const string& adress);
	void TaBortEntry(Person* ptr);
	Person* SökNamn(const string& namn) const;
	void Print() const;
	void Töm();
	Person* SökFritt(const string& namn, Person* startOnNext)const;
	~PersonReg();
	

};
#endif