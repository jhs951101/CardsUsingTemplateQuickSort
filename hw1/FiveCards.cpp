//
// Programmed by cskim HUFS.ac.kr 2008/5/6
//

#include "List.h"
#include "FiveCards.h"

Card FIVEHIGHCARD[] = { Card(1,15), Card(1,15), Card(1,15), Card(1,15), Card(1,15) };
FiveCards& FiveCards::getHighValue(){
	FiveCards* p5Cards = new FiveCards();
	p5Cards->pelem = FIVEHIGHCARD;
	return *p5Cards;
}
FiveCards::FiveCards() {
	pelem = new Card[FIVE];
	for(int i=0; i<FIVE; ++i)
		pelem[i] = Card(1,15);
}
FiveCards::FiveCards(const FiveCards& right) {
	pelem = new Card[FIVE];
	 for(int i=0; i<FIVE; ++i) 
		 pelem[i] = right.pelem[i];
}

FiveCards& FiveCards::operator=(const FiveCards& right) {
	if(this != &right) {
		delete[] pelem;
		pelem = new Card[FIVE];
		for(int i=0; i<FIVE; ++i) 
			pelem[i]=right.pelem[i];
	}
	return *this;
}
FiveCards::~FiveCards() {
	delete[] pelem;
}
Card& FiveCards::operator[](int index) {
	assert((index >= 0) && (index < FIVE));
	return pelem[index];
}

Card FiveCards::operator[](int index) const {
	assert((index >= 0) && (index < FIVE));
	return pelem[index];
}

void quickSort (List<Card>& L)
{
	int n = L.size();
	if (n < 2)
		return;

	List<Card> L1;
	List<Card> L2;
	List<Card> Le;

	Iterator<Card> last = L.end();
	last.previous();
	Card pivot = last.get();

	Iterator<Card> li = L.begin();
	while (!L.empty()) {
		if (li.get() < pivot) {
			L1.push_back(li.get());
		}
		else if (li.get() == pivot) {
			Le.push_back(li.get());
		}
		else {
			L2.push_back(li.get());
		}
		li = L.erase(li);
	}
	quickSort(L1);
	quickSort(L2);

	li = L1.begin();
	while (!L1.empty()) {
		L.push_back(li.get());
		li = L1.erase(li);
	}
	li = Le.begin();
	while (!Le.empty()) {
		L.push_back(li.get());
		li = Le.erase(li);
	}
	li = L2.begin();
	while (!L2.empty()) {
		L.push_back(li.get());
		li = L2.erase(li);
	}

}

int FiveCards::compareInOrder(const FiveCards& right) const {  // 2개의 FiveCards에 대해 사전 순으로 카드 5장을 비교하는 함수

	List<Card> l1;
	List<Card> l2;

	for(int i=0; i<5; i++){
		l1.push_back(this->pelem[i]);
		l2.push_back(right.pelem[i]);
	}

	quickSort(l1);
	quickSort(l2);  // 카드 5장을 정렬부터 해야 사전 순으로 비교하는 것이 쉬워짐

	Iterator<Card> i1 = l1.begin();
	Iterator<Card> i2 = l2.begin();

	for(int i=0; i<5; i++){
		Card a = i1.get();
		Card b = i2.get();

		if(a.compare(b) != 0)  // 앞에서 부터 비교를 해나가다가 서로 다른 카드이면 더 큰 카드를 가진 FiveCards가 더 큰 것임
			return a.compare(b);

		i1++;
		i2++;
	}

	return 0;  // 계속 비교를 해나갔지만 모두 같은 카드라면 서로 같은 FiveCards임
}

string FiveCards::tostring() const {

	string result = "[";
	for(int i=0; i<FIVE; ++i) {
		 if ( i != 0 ) result+=", ";
		 result += pelem[i].tostring();
	}
	result += "]\n";
	return result;
}

bool operator<(const FiveCards& left, const FiveCards& right)  {
   return (left.compareInOrder(right) < 0);
}

bool operator<=(const FiveCards& left, const FiveCards& right)  {
   return ((left.compareInOrder(right) < 0) || (left.compareInOrder(right) == 0));
}

bool operator>(const FiveCards& left, const FiveCards& right)  {
   return (left.compareInOrder(right) > 0);
}

bool operator>=(const FiveCards& left, const FiveCards& right)  {
   return ((left.compareInOrder(right) > 0) || (left.compareInOrder(right) == 0));
}

bool operator==(const FiveCards& left, const FiveCards& right){
	return (left.compareInOrder(right) == 0);
}

bool operator!=(const FiveCards& left, const FiveCards& right){
	return (left.compareInOrder(right) != 0);
}

ostream& operator<<(ostream& out, const FiveCards& cards) {
	out << cards.tostring();

	return out;
}
