#include "Personregister.h"
#include "Person.h"
#include "PersonMedTel.h"
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

PersonReg::PersonReg(const int maxStorlek)
{
	this->maxStorlek = maxStorlek;
	person = new Person[maxStorlek];
}

bool PersonReg::LäggTill(const Person* p)
{

	if (currentIndex < maxStorlek)
	{
		person[currentIndex] = *p;
		currentIndex++;
	}

	return true;
}
bool PersonReg::LäggTillTest(const string& namn, const string& adress)
{
	if (currentIndex < maxStorlek)
	{
		person[currentIndex] = Person(namn, adress);
		currentIndex++;
	}

	return true;
}

void PersonReg::TaBortEntry(Person * ptrs)
{
	

	for (Person* ptr = person; ptr != person + maxStorlek; ++ptr)
	{
		if (ptr->name == ptrs->name && ptr->adress == ptrs->adress)
		{
			ptr->name = "?";
			ptr->adress = "?";
			for (Person* ptrSort = person; ptrSort != person + maxStorlek; ++ptrSort)
			{
				while (ptr->name == "?" && ptr < ptrSort && ptrSort->name != "?")
				{
					ptr->name = ptrSort->name;
					ptr->adress = ptrSort->adress;

					ptrSort->name = "?";
					ptrSort->adress = "?";
					ptr++;
				}
				
			}
		}
	}
	currentIndex--;
}
Person * PersonReg::SökNamn(const string & namn) const
{
	for (Person* ptr = person; ptr != person + maxStorlek; ++ptr)
	{
		if (ptr->name == namn)
		{
			return ptr;
		}

	}
	return nullptr;
}
void PersonReg::Print() const
{
	for (Person* ptr = person; ptr != person + maxStorlek; ++ptr) 
	{
		ptr->PrintPerson(); 
	}
}
void PersonReg::Töm() 
{
	for (Person* ptr = person; ptr != person + maxStorlek; ++ptr)
	{
		ptr->name = "?";
		ptr->adress = "?";
	}
	currentIndex = 0;
}

PersonReg::~PersonReg()
{
	delete[] person;
}
Person * PersonReg::SökFritt(const string & sökEfter, Person * startOnNext) const
{
	for (Person* ptr = person; ptr != person + maxStorlek; ++ptr)
	{
		if (startOnNext == nullptr)
		{
			if (sökEfter == ptr->name || ptr->adress.find(sökEfter) == true)
			{
				return ptr;
			}

		}
		else if (startOnNext != nullptr)
		{
			if (ptr > startOnNext && sökEfter == ptr->name)
				return ptr;
		}	
	}
	return nullptr;
}
