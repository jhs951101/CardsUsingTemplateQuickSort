//
// Programmed by cskim HUFS.ac.kr 2008/5/6
//
#include "String.h"
#include "Card.h"

Card Card::getHighValue(){
	return Card(1,15);
}

Card::Card () {
	suit = SPADE;
	rank = ACE;
}
Card::Card (int s, int r) { 
	suit = (SUIT) s;
	rank = (PIP) r;
}

String Card::toString () const {
	String image;
	switch (suit) {
	case CLUB:		image = "CL "; break;
	case DIAMOND:	image = "DI "; break;
	case HEART:		image = "HE "; break;
	case SPADE:		image = "SP "; break;
	}
	switch ((int)rank) {
	case ACE:	image += "A "; break;
	case JACK:	image += "J "; break;
	case QUEEN:	image += "Q "; break;
	case KING:	image += "K "; break;
	case 10:	image += "10"; break;
	default:	image = image + ((char)('0'+(int)rank) + String(" "));
	}
	return image;
}

string Card::tostring () const {
	string image;
	switch (suit) {
	case CLUB:		image = "CL "; break;
	case DIAMOND:	image = "DI "; break;
	case HEART:		image = "HE "; break;
	case SPADE:		image = "SP "; break;
	}
	switch ((int)rank) {
	case ACE:	image += "A "; break;
	case JACK:	image += "J "; break;
	case QUEEN:	image += "Q "; break;
	case KING:	image += "K "; break;
	case 10:	image += "10"; break;
	default:	image = image + (char)('0'+rank) + " ";
	}
	return image;
}
/*
ostream& Card::outstr(ostream& sout) const {

	sout << tostring();
	return sout;
}
 */
ostream& operator<<(ostream& out, const Card& card)
{
	out << card.tostring();

	return out;
}

int Card::compare(const Card& right) const {
	int lrank, rrank; 
	if (rank == ACE ) 
		lrank = KING + 1;
	else
		lrank = rank;

	if (right.rank == ACE ) 
		rrank = KING + 1;
	else
		rrank = right.rank;

	int diff = lrank - rrank;

	return diff;
}

PIP Card::getRank(){
	return this->rank;
}

SUIT Card::getSuit(){
	return this->suit;
}

bool operator<(const Card& left, const Card& right)
{
	return left.compare(right) < 0;
}

bool operator<=(const Card& left, const Card& right)
		{
	return left.compare(right) <= 0;
		}

bool operator==(const Card& left, const Card& right)
		{
	return left.compare(right) == 0;
		}

bool operator!=(const Card& left, const Card& right)
		{
	return left.compare(right) != 0;
		}

bool operator>=(const Card& left, const Card& right)
		{
	return left.compare(right) >= 0;
		}

bool operator>(const Card& left, const Card& right)
{
	return left.compare(right) > 0;
}
