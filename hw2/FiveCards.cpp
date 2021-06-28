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

int decideFiveCards(string lr, FiveCards fc){  /* 카드 5장을 가지고 짝패를 판단하는 함수
						  return 되는 번호가 클 수록 짝패의 순위가 높은 것임*/
	/*
	 * return 0: No Pair
	 * return 1: 1 Pair
	 * return 2: 2 Pair
	 * return 3: Triple
	 * return 4: Straight
	 * return 5: Flush
	 * return 6: Full House
	 * return 7: 4 Card
	 */

	if( (fc[0] == fc[1] && fc[0] == fc[2] && fc[0] == fc[3])
		|| (fc[1] == fc[2] && fc[1] == fc[3] && fc[1] == fc[4]) ){  // 4 Card 인지 판단
			cout << lr << " Result: 4 Card" << endl;
			return 7;
	}

	if( (fc[0] == fc[1] && fc[0] == fc[2] && fc[3] == fc[4])
		|| (fc[2] == fc[3] && fc[2] == fc[4] && fc[0] == fc[1]) ){  // Full House 인지 판단
			cout << lr << " Result: Full House" << endl;
			return 6;
	}

	if( fc[0].getSuit() == fc[1].getSuit() && fc[0].getSuit() == fc[2].getSuit()
		&& fc[0].getSuit() == fc[3].getSuit() && fc[0].getSuit() == fc[4].getSuit() ){  // Flush 인지 판단
			cout << lr << " Result: Flush" << endl;
			return 5;
	}

	bool isStraight = true;

	for(int i=0; i<4; i++){

		int rank1 = fc[i].getRank();
		int rank2 = fc[i+1].getRank();

		if(rank1 == ACE)
			rank1 = KING + 1;

		if(rank2 == ACE)
			rank2 = KING + 1;

		if(rank1+1 != rank2){
			isStraight = false;
			break;
		}
	}

	if(isStraight){  // Straight 인지 판단
		cout << lr << " Result: Straight" << endl;
		return 4;
	}

	if( (fc[0] == fc[1] && fc[0] == fc[2])
		|| (fc[1] == fc[2] && fc[1] == fc[3])
		|| (fc[2] == fc[3] && fc[2] == fc[4]) ){  // Triple 인지 판단
		cout << lr << " Result: Triple" << endl;
		return 3;
	}

	int i=0;
	int isTwoPair = 0;

	while(isTwoPair != 2 && i<4){
		if(fc[i] == fc[i+1]){
			isTwoPair++;
			i = i+2;
		}
		else{
			i++;
		}
	}

	if(isTwoPair == 2){  // 2 Pair 인지 판단
		cout << lr << " Result: 2 Pair" << endl;
		return 2;
	}

	for(int i=0; i<4; i++){
		if(fc[i] == fc[i+1]){  // 1 Pair 인지 판단
			cout << lr << " Result: 1 Pair" << endl;
			return 1;
		}
	}

	cout << lr << " Result: No Pair" << endl;
	return 0;  // No Pair 라고 판단됨
}

int FiveCards::compareInPoker(const FiveCards& right) const {

	List<Card> l1;
	List<Card> l2;

	for(int i=0; i<5; i++){
		l1.push_back(this->pelem[i]);
		l2.push_back(right.pelem[i]);
	}

	quickSort(l1);
	quickSort(l2);  // 카드 5장을 정렬부터 해야 포커 순으로 비교하는 것이 쉬워짐

	Iterator<Card> i1 = l1.begin();
	Iterator<Card> i2 = l2.begin();

	FiveCards fc1;
	FiveCards fc2;

	for(int i=0; i<5; i++){  // FiveCards를 새로 만든 다음 정렬된 카드 5장을 순서대로 넣음
		fc1[i] = i1.get();
		fc2[i] = i2.get();

		i1++;
		i2++;
	}

	int a, b;

	for(int i=1; i<=3; i++){
		if(i == 1){  // 두 FiveCards의 짝패를 비교함
			a = decideFiveCards("Left", fc1);
			b = decideFiveCards("Right", fc2);
		}
		else if(i == 2){  // 서로 짝패가 같다면 가장 큰 카드 숫자를 가지고 비교함
			a = fc1[4].getRank();

			if(a == ACE)
				a = KING + 1;

			b = fc2[4].getRank();

			if(b == ACE)
				b = KING + 1;
		}
		else if(i == 3){  // 서로 숫자가 같다면 무늬를 가지고 비교함
			int rank = fc1[4].getRank();

			int max1 = fc1[4].getSuit();

			for(int j=3; j>=0; j--){  /* 가장 큰 카드가 2장 이상 있을 수도 있으므로 여러 장의 가장 큰 카드로부터 가장 큰 무늬를 찾아냄
						     ex) ◆5 ◆6 ◆7 ◆7 ♥7 : 가장 큰 카드는 '7'이고, 카드가 3장임 */
				if(fc1[j].getRank() != rank)
					break;

				if(max1 < fc1[j].getSuit())
					max1 = fc1[j].getSuit();
			}

			int max2 = fc2[4].getSuit();

			for(int j=3; j>=0; j--){
				if(fc2[j].getRank() != rank)
					break;

				if(max2 < fc2[j].getSuit())
					max2 = fc2[j].getSuit();
			}

			a = max1;
			b = max2;
		}

		if(a-b != 0)
			return (a-b);
	}

	return 0;  // 무늬마저도 같다면 서로 동일하다고 판단함
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
   return (left.compareInPoker(right) < 0);
}

bool operator<=(const FiveCards& left, const FiveCards& right)  {
   return ((left.compareInPoker(right) < 0) || (left.compareInPoker(right) == 0));
}

bool operator>(const FiveCards& left, const FiveCards& right)  {
   return (left.compareInPoker(right) > 0);
}

bool operator>=(const FiveCards& left, const FiveCards& right)  {
   return ((left.compareInPoker(right) > 0) || (left.compareInPoker(right) == 0));
}

bool operator==(const FiveCards& left, const FiveCards& right){
	return (left.compareInPoker(right) == 0);
}

bool operator!=(const FiveCards& left, const FiveCards& right){
	return (left.compareInPoker(right) != 0);
}

ostream& operator<<(ostream& out, const FiveCards& cards) {
	out << cards.tostring();

	return out;
}
