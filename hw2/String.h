/*
 * String.h
 *
 *  Created on: Apr 25, 2012
 *      Author: cskim
 */

#ifndef MY_STRING_H_
#define MY_STRING_H_

#include <iostream>
using namespace std;

class String {
public:
	String(); // Default constructor
	String(const char p[]); // Simple constructor
	String(const String& right); // Copy constructor
	~String(); // Destructor
	String& operator=(const String& right); // Assignment operator

	String& operator+=(const String& right);
	int length() const;
	int size() const;
	char& operator[](int index);
	char operator[](int index) const;

	int compare(const String& right) const;

	string tostring() const;
	ostream& outstr(ostream& sout) const;
	String substr(int pos, int nlen) const;

	static String getHighValue(); // New
private:
	char* buffer;
	int len;
};

String operator+(const String& left, const String& right);
String operator+(char left, const String& right);
ostream& operator<<(ostream& out, const String& str);

bool operator<(const String& left, const String& right);
bool operator<=(const String& left, const String& right);
bool operator==(const String& left, const String& right);
bool operator!=(const String& left, const String& right);
bool operator>=(const String& left, const String& right);
bool operator>(const String& left, const String& right);

#endif /* MY_STRING_H_ */
