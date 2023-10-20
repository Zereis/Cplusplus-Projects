#pragma once
#ifndef STRING
#define STRING
#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
using namespace std;
class String
{
private:
	

public:
	char * charArray;
	int charSize;
	int charCap;

	~String();
	String();
	String(const String& rhs);
	void Invariant();
	String(const char* cstr);
	String& operator=(const String& rhs);
	char& operator[](size_t i);
	const char& operator[](size_t i) const;
	size_t size() const;
	size_t capacity() const;
	void push_back(char c);
	void increaseCap(char* cstr);
	void print();
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator != (const String& lhs, const String& rhs);
	const char* data() const;
	friend std::ostream& operator<< (std::ostream& out, const String& rhs);
};
#endif
