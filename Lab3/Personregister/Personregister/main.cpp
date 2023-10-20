#include "Personregister.h"
#include "Person.h"
#include "PersonMedTel.h"
#include <iostream>
#include <string>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#if 1
#define PN(x) cout << x
#define DN(x) x
#define PD(x) cout << x
#else
#define PN(x)
#define DN(x)
#define PD(x) (x)
#endif
using namespace std;

void Init(PersonReg& tr) 
{ 
	tr.Töm();    
		PD(tr.LäggTillTest("olle", "0703955123"));
		PD(tr.LäggTillTest("olle", "123"));    
		PD(tr.LäggTillTest("kurt ke", "12345"));   
		PD(tr.LäggTillTest("olle", "456"));
		PD(tr.LäggTillTest("sven", "456"));     
		PD(tr.LäggTillTest("kurt", "95815"));     
		//PD(tr.LäggTillTest("olle", "789"));
		PN(endl);    
		PN(("fullt reg "));   
		PN((endl));    
		DN((tr.Print())); 
}
#include <fstream>
bool ReadReg(PersonReg& reg, string fileName)
{
	string line;
	ifstream myfile("PersonExempel.txt");
	if (myfile.is_open()) 
	{ 
		while (getline(myfile, line)) 
		{ 
			while (line.length() == 0 && getline(myfile, line));            
			string name(line);           
			string adress;           
			getline(myfile, adress);            
			reg.LäggTill(&Person(name, adress)); 
		}        
		myfile.close();       
		return true; 
	}
	else { 
		cout << "Unable to open file";        
		return false;
	}
}
void Test1() 
{ 
	PersonReg reg(10);    
	ReadReg(reg, "PersonExempel.txt");    
	reg.Print(); 
	cout << "\n\n";    
	reg.Töm();  
	reg.Print(); }
void Test2() {
	PersonReg reg(10);    
	Init(reg);    
	string namn, adress;    
	Person te, *tep;  

	tep = reg.SökNamn("sven");
	//tep = reg.SökNamn("olle");
	if (tep) 
	{ 

		cout << tep->name << " " << tep->adress << endl;        
		reg.TaBortEntry(tep); 
	}
	else
	{
		cout << "not found \n";
	}
	
	tep = reg.SökNamn("olle");     
	if (tep) 
	{ 
		cout << tep->name << " " << tep->adress << endl;
		reg.TaBortEntry(tep); 
	}
	
	else        
		cout << "not found \n";    
	
	tep = reg.SökNamn("olle"); 
	if (tep) 
	{ 
		cout << tep->name << " " << tep->adress << endl;
		reg.TaBortEntry(tep); 
	}
	else        
		cout << "not found \n";   
	
	tep = reg.SökNamn("olle");     
	if (tep) 
	{ 
		cout << tep->name << " " << tep->adress << endl;
		reg.TaBortEntry(tep); }
	else        
		cout << "not found \n";   

	tep = reg.SökNamn("olle");     
	if (tep) 
	{ 

		cout << tep->name << " " << tep->adress << endl;
		reg.TaBortEntry(tep);
	}
	else        
		cout << "not found \n";   
	
	reg.Print();    
	reg.Töm(); 
	cout << endl;
	reg.Print();
	
}
void Test3() {
	PersonReg reg(10);
	Init(reg);
	reg.Print();
	string namn, adress;
	Person te, *tep;

	tep = nullptr;
	while (tep = reg.SökFritt("olle", tep)) {
		tep->PrintPerson();
		//        cout << tep->adress << endl;
	}
	cout << "not found \n";

	cout << "blandade s kningar \n";
	Person* ptr1 = nullptr, *ptr2 = nullptr;
	bool first = true;
	
	while (first || ptr1 || ptr2) 
	{
		if (ptr1 || first) {
			ptr1 = reg.SökFritt("olle", ptr1);
			if (ptr1)
				ptr1->PrintPerson();
		}        if (ptr2 || first) {
			ptr2 = reg.SökFritt("581", ptr2);
			if (ptr2)
				ptr2->PrintPerson();
		}
		first = false;
	}
}
	
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);    
	locale::global(locale("swedish"));   
	
	//int storlek = 10;
	//PersonReg pr(10);    
	//Init(pr);    
	//Test1();    
	Test2();    
	//Test3();    
	/*cin.get();*/
	
	/*
	Person * myPerson = new PersonMedTel("David", "gata 15", "12345");
	myPerson->PrintPerson(); // Kallar på icke virtual som printar ut namn, adress och nummer
	
	Person * test = new Person("kek", "gata 10");
	test->PrintPerson(); // Kallar på virtual print funktion som printar bara ut namn och adress
	test->~Person();

	PersonReg * reg = new PersonReg(storlek);
	reg->LäggTill(myPerson);
	reg->Print(); // Lägger till person med telefon i registret och skrivs sedan ut
	*/
	// Eftersom personregister har ingen medlem som tar emot nummer som i PersonMedTel klassen har så
	// skrivs inte nummer ut utan bara namn och adress enlight funktion beskrivningen

	//PersonReg pr(10);    
	//Init(pr);    
	//Person* x1 = pr.SökFritt("olle", nullptr);
	//x1->PrintPerson();
	//Person* x2 = pr.SökFritt("olle", x1);
	//x2->PrintPerson();
	//Person* x3 = pr.SökFritt("olle", x2);
	//x3->PrintPerson();
	//Person* y2 = pr.SökFritt("olle", x1);
	//y2->PrintPerson();

	

	/*
	PersonReg* reg = new PersonReg(storlek);;
	Person* p = new Person("Olle", "gata14");

	reg->LäggTillTest("David", "gata13");
	reg->LäggTillTest("Olle", "gata14");
	//reg->LäggTill(p);



	reg->TaBortEntry(p);
	reg->Print();
	
	delete reg;
	delete p;
	*/

	//reg->Töm();
	//reg->SökNamn("David");
	
}

