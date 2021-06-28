/*
 * String.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: cskim
 */
#include <cstring>
#include "String.h"

using namespace std;

String String::getHighValue(){
	return String("zzzz");
}

String::String() {
	//cout << "Default Constructor Called\n";
	len = 0;
	buffer = new char[0]; // No need to allocate array to hold zero characters
}

String::String(const char p[]) {
	// Determine number of characters in string (strlen(p))
	//cout << "Char Array Constructor Called str=";
	len = 0;
	while (p[len] != '\0')
		len++;
	// Allocate buffer array, remember to make space for NULL character
	buffer = new char[len + 1];
	// Copy new characters (strcpy( buffer, p ))
	for (int i = 0; i < len; i++)
		buffer[i] = p[i];
	buffer[len] = '\0';
	//cout << *this << endl;
}

String::String(const String& right) {
	//cout << "Copy Constructor Called str=";
	int n = right.length();
	len = n;
	buffer = new char[n + 1];
	for (int i = 0; i < n; i++)
		buffer[i] = right[i];
	buffer[n] = '\0';
	//cout << *this << endl;
}

String& String::operator=(const String& right) {
	//cout << "Assignment Oper. Called str=";
	if (this != &right) {
		delete[] buffer; // Get rid of old buffer
		len = right.length();
		buffer = new char[len + 1];
		for (int i = 0; i < len; i++)
			buffer[i] = right[i];
		buffer[len] = '\0';
	}
	else {
		//cout << "assign op--same var assign \n";
	}
	//cout << *this << endl;
	return *this;
}

String::~String() {
	//cout << "Destructor Called str=";
	//cout << *this << endl;

	delete[] buffer;
}
String& String::operator+=(const String& right) {
	char* newbuf = new char[len+right.length()+1];
	for (int i = 0; i < len; i++)
		newbuf[i] = buffer[i];
	for (int i = 0; i < right.length(); i++)
		newbuf[len+i] = right[i];

	delete[] buffer; // Get rid of old buffer

	len += right.length();
	buffer = newbuf;
	buffer[len] = '\0';
	return *this;
}

String String::substr(int pos, int nlen) const {
	char* subbuf = new char[nlen+1];
	for (int i=0; i<nlen; ++i){
		subbuf[i] = buffer[pos+i];
	}
	subbuf[nlen] = '\0';
	return String(subbuf);
}
int String::compare(const String& right) const {
	return std::strcmp(buffer, right.buffer);
}
string String::tostring() const {
	return string(buffer);
}
int String::length() const {
	return len;
}
int String::size() const{
	return len;
}
char String::operator [](int i) const {
	return buffer[i];
}
char& String::operator [](int i) {
	return buffer[i];
}
ostream& String::outstr(ostream& sout) const {
	for (int i = 0; i < len; ++i)
		sout << buffer[i];
	return sout;
}
ostream& operator<<(ostream& sout, const String& s) {
	return s.outstr(sout);
}
String operator+(const String& left, const String& right) {
	String res = left;
	res+=right;
	return res;
}
String operator+(char left, const String& right) {
	char* subbuf = new char[2];
	subbuf[0] = left;
	subbuf[1] = '\0';
	String res = String(subbuf);
	res+=right;
	return res;
}

bool operator>(const String& left, const String& right) {
	return (left.compare(right) > 0);
}

bool operator>=(const String& left, const String& right) {
	return ((left.compare(right) > 0) || (left.compare(right) == 0));
}

bool operator<(const String& left, const String& right) {
	return (left.compare(right) < 0);
}

bool operator<=(const String& left, const String& right) {
	return ((left.compare(right) < 0) || (left.compare(right) == 0));
}

bool operator==(const String& left, const String& right) {
	return (left.compare(right) == 0);
}

bool operator!=(const String& left, const String& right) {
	return (left.compare(right) != 0);
}
