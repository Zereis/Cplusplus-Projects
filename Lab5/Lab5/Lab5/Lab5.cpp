#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
//#include <stdlib.h>
#include <crtdbg.h>

//#define VG

#include "String.h"

#include <string>
#include <iostream>
#include <cassert>
#include <utility>


using namespace std;

void AssertStrEqual(const String& lhs, const char* rhs) {
	for (size_t i = 0; i < lhs.size() && *rhs != '\0'; ++i) {
		assert(lhs[i] == rhs[i]);
		assert(rhs[i] != 0);
	}
	assert(rhs[lhs.size()] == 0);
}

void TestPushBackReallocation() {
	String str("hej");
	assert(str.size() <= str.capacity());
	assert(str.size() == 3);
	auto hej = "hej";
	//AssertStrEqual(str, hej);
	AssertStrEqual(str, "hej");
//#ifdef VG
//	//If VG we try to take 20 empty places: (size+1 < capacity)
//	while (str.size() + 20 >= str.capacity() && str.size() < 1000)
//		str.push_back('A' + rand() % 32);
//	assert(str.size() < 1000);	//If this fail it prbably the case that capacity is increased with a constant.
//#endif //VG

	auto internalBuf = &str[0];
	auto cap = str.capacity();
	auto siz = str.size();
	size_t i;
	for (i = siz + 1; i <= cap; ++i) {
		str.push_back(char(i) + 'a');
		assert(internalBuf == &str[0]);
		assert(cap == str.capacity());
		assert(i == str.size());
	}
	str.push_back(char(i));
	assert(internalBuf != &str[0]);
	assert(cap < str.capacity());
	assert(i == str.size());
}

#pragma region DeleteCheckFel
//#pragma push_macro("new")
//#undef new
//
//void* memoryPtr;
//void* operator new(size_t size) {
//    memoryPtr = ::malloc(size);
//    return memoryPtr;
//}
//
//void operator delete(void* ptr) {
//    if (ptr != memoryPtr) {
//        cout << "You are deleting the wrong string!?\n";
//    }
//    ::free(ptr);
//}
//
//void TestDelete() {
//    void* sSave = malloc(sizeof(String));
//    void* sPtr;
//    {
//        String s("huj");
//        sPtr = &s;
//        memcpy(sSave, &s, sizeof(String));
//        s.~String();
//#pragma pop_macro("new")
//    }
//    if (memcmp(sSave, sPtr, sizeof(String)))
//        cout << "You are doing uneccessary things in you deconstructor ~String()\n";
//}
#pragma endregion DeleteCheckFel

void TestDelete() {
	//V舁Godk舅t (g蚌 att ka p・Godk舅t men jag kr舸er inte detta!)
	void* sSave = malloc(sizeof(String));
	void* sPtr;
	{
		String s("hejsan");
		sPtr = &s;
		memcpy(sSave, &s, sizeof(String));
	}
	if (memcmp(sSave, sPtr, sizeof(String)))
		cout << "You are doing uneccessary things in you deconstructor ~String()\n";
	else { //F att f蚣ga "null" version, tveksamt om den hittar n虍ot!
		{
			String s;
			sPtr = &s;
			memcpy(sSave, &s, sizeof(String));
		}
		if (memcmp(sSave, sPtr, sizeof(String)))
			cout << "You are doing uneccessary things in you deconstructor ~String()\n";
	}
	delete sSave;
}

void TestCapacitySetting() {
	//F godk舅t
	{
		String s, r;
		int size = s.size();
		for (int i = 0; i < size * 2 + 16; ++i)
			r.push_back('a' + i % 26);
		s = r;
		assert(s.size() <= s.capacity());
	}
	{ //Will probably fail to catch any error :-(
		String r;
		for (int i = 0; i < 65; ++i)
			r.push_back('a' + i % 26);
		String s(r);
		assert(s.size() <= s.capacity());
	}
}

void TestPushBack() {
	//F Godk舅t
	{
		String str = "bar";
		str.push_back('a');
		assert(str == "bara");
	}
	{
		String r;
		int size = 65;
		for (int i = 0; i < size; ++i)
			r.push_back('a' + i % 26);
		assert(r.size() <= r.capacity());
		assert(r.size() == size);
	}

	//Test No Extra Alloc    
	{       
		String r;       
		int size = 65;        
		for (size = 0; size < 65; ++size)            
			r.push_back('a' + size % 26);       
		while (r.size() >= r.capacity()) {            
			r.push_back('a' + size % 26);            
			++size;        
		}
		const char* ptr = r.data();       
		int cap = r.capacity();       

		while (ptr == r.data())       
		{        
			r.push_back('x');        
		}        
		assert(r.size() == cap + 1);   
 
	}
}


String* MakeString(size_t size) {
	String* str = new String();
	int i;
	for (i = 0; i < size; ++i)
		str->push_back('a' + i % 26);
	return str;
}

#ifdef VG
void TestNoExtraAlloc() {
	//Bara f VG (anv舅der reserve)
	String r;
	int size;
	for (size = 0; size < 33; ++size)
		r.push_back('a' + size % 26);
	while (r.size() >= r.capacity()) {
		r.push_back('a' + size % 26);
		++size;
	}

	String* sPtr;
	sPtr = MakeString(r.size() - 1);
	sPtr->reserve(sPtr->size() + 1);
	const char* dPtr;
	dPtr = sPtr->data();
	*sPtr = r;//ska inte ge omallokering;
	assert(dPtr == sPtr->data()); //Du allokerar nytt minne i onan.
	delete sPtr;

	sPtr = MakeString(r.size() - 1);
	dPtr = sPtr->data();
	*sPtr = r;//ska ge omallokering;
	//assert(dPtr != sPtr->data());
	if (dPtr == sPtr->data())
		cout << "********Det 舐 mligt att du inte allokerar mer minne i operator= fast det behs!******";
	delete sPtr;
}
#endif
void TestFörGodkäntString() {
	//-	String()
	String str0;	AssertStrEqual(str0, "");

	//-	String(Str舅g str舅g)
	String s1("foo"); assert(s1 == "foo");
	String str(s1); assert(str == "foo");
	String s3("bar");  assert(s3 == "bar");

	//-	~String() Kom ih虍 destruktorn!
	delete new String("hej");
	TestDelete();

	//	-	operator =(Str舅g str舅g)
	str = "hej";
	assert((str = s3) == s3);
	assert((str = str) == s3);	//self assignment

								//Ej samma buffert
	str = "heja"; s3 = str;
	str[0] = 'x'; assert(s3[0] == 'h');
	s3[1] = 'y'; assert(str[1] == 'e');


	String str1("foo"), str2("bar"), str3("hej");
	str3 = str = str1;
	assert(str3 == str);
	assert(str1 == str);

	TestCapacitySetting();

	//No extra realloc
	AssertStrEqual(str1, "foo");
	auto xxx = str1.data();
	str1 = String("huj");
	assert(xxx == str1.data());

	//-	operator==
	//testas erallt!
	{
		String s, r;
		s.push_back(0);
		s.push_back(0);
		s.push_back(0);
		r.push_back(0);
		assert(s != r && !(r == s));
	}

	//- operator!=
	assert(str1 != str);
	assert(!(str1 != str1));
	//-	operator[](size_t i) som indexerar utan range check.
	str = "bar";
	str[-1]; str[1000];	//No error
	assert(str[1] == 'a');
	str[1] = 'y';
	assert(str[1] == 'y');

	const String sc(str);
	assert(sc[1] == 'y');
	assert(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value); //Kolla att det blir en const resultat av indexering

																				 //-	push_back(char c)
	TestPushBack();

	// data
	const char* temp = str.data();
	assert(temp == &str[0]);

	//-	size(), capacity() and reloccation test;
	TestPushBackReallocation();

	cout << String("hej\n");
	cout << "Om det st蚌 hej p・feg蘰nde rad s・舐 TestFGodk舅t klar\n";

}

/*
void TestFV舁Godk舅tString() {
#ifdef VG
	TestDelete();
	TestNoExtraAlloc();

	String str("bar");

	//-	at(size_t i) som indexerar med range check
	try {
		str.at(-1);
		assert(false);
	}
	catch (std::out_of_range&) {};
	try {
		str.at(3);
		assert(false);
	}
	catch (std::out_of_range&) {};

	//- at indexerar

	//-	at(size_t i) 
	str = "bar";
	assert(str.at(1) == 'a');
	str.at(1) = 'y';
	assert(str.at(1) == 'y');

	const String strC(str);
	assert(strC.at(1) == 'y');
	assert(std::is_const<std::remove_reference< decltype(strC.at(1))>::type>::value); //Kolla att det blir en const resultat av indexering


	//	reserve()
	auto internalBuf = &str[0];
	auto cap = str.capacity();
	auto siz = str.size();

	str.reserve(cap);
	assert(internalBuf == &str[0]);
	assert(cap == str.capacity());
	assert(siz == str.size());

	str.reserve(cap + 1);
	assert(internalBuf != &str[0]);
	assert(cap < str.capacity());
	assert(siz == str.size());

	// shrink_to_fit
	str = "hej";
	str.reserve(10);
	internalBuf = &str[0];
	cap = str.capacity();
	siz = str.size();

	str.shrink_to_fit();
	assert(internalBuf != &str[0]);
	assert(str.capacity() == str.size());
	AssertStrEqual(str, "hej");

	/////////////////
	//-	operator+=(Str舅g str舅g) som tolkas som konkatenering.
	//foo, bar, hej
	String str1("foo"), str2("bar"), str3("hej");
	((str = "xyz") += str1) += (str3 += str1);
	assert(str3 == "hejfoo" && str == "xyzfoohejfoo" && str1 == "foo");

	//+= som f蚌 plats;
	str = "bar"; str.reserve(10);
	str += "foo";
	assert(str == "barfoo");

	//+= som inte f蚌 plats;
	str.reserve(10);
	str = "";
	size_t i;
	for (i = 0; str.size() < str.capacity(); ++i)
		str.push_back(char('0' + i));
	str1 = "bar";
	str += str1;
	for (size_t k = 0; k < i; ++k)
		assert(str[k] == '0' + k);
	assert(str[i] == 'b');
	//+= Sj舁v assignment	//Borde testa med att capacity tar slut!
	str = "foo";
	str += str;
	assert(str == "foofoo");

	//-	operator+
	str = "bar";
	assert(str + "foo" == "barfoo");
	AssertStrEqual(str, "bar");

	cout << "\nTestFV舁Godk舅t klar\n";
#endif //VG
}
*/

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	locale::global(locale("swedish"));

	/*TestCapacitySetting();*/
	/*TestPushBackReallocation();*/
	/*TestPushBack();*/
	TestFörGodkäntString();
#ifdef VG
	TestFV舁Godk舅tString();
	cout << "VG test klart\n";
#endif
	/*
	new int;
	cout << "det finns en minnesl臘ka i main, avsiktligt!\n s・ni kan se att er minnesl臘kstest fungerar\n";
	cin.get();*/
}
