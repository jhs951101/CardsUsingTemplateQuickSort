//
// Programmed by cskim HUFS.ac.kr 2008/5/6
//
#ifndef MY_CARD_H
#define MY_CARD_H

#include <iostream>
#include <string>
#include "String.h"
using namespace std;

enum PIP { ACE=1, JACK=11, QUEEN, KING };
enum SUIT { CLUB=1, DIAMOND, HEART, SPADE };

class Card {
private:
	SUIT	suit;
	PIP		rank;

public:
	Card ();
	Card (int s, int r);
	string	tostring() const;
	String	toString() const;
	//ostream& outstr(ostream& sout) const;
	int compare (const Card& c) const;
	static Card getHighValue(); // New

	PIP getRank();
	SUIT getSuit();
};

bool operator<(const Card& left, const Card& right);
bool operator<=(const Card& left, const Card& right);
bool operator==(const Card& left, const Card& right);
bool operator!=(const Card& left, const Card& right);
bool operator>=(const Card& left, const Card& right);
bool operator>(const Card& left, const Card& right);

ostream& operator<<(ostream& out, const Card& value);

#endif
