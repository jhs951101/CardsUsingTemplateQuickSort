// QuickSort.cpp
//

#include <string>
#include <iostream>
#include <cassert>

#include "List.h"
#include "Card.h"
#include "FiveCards.h"

using namespace std;

const int  LINE_MAX = 13;

template<typename T>
void printList(List<T>& L)
{
	int i = 0;
	for (Iterator<T> cp = L.begin(); cp!=L.end(); cp.next()) {
		cout << cp.get() << " ";
		i++;
		if (i % LINE_MAX == 0) cout << endl;
	}
	cout << endl;
}

template<typename T>
void quickSort (List<T>& L)
{
	int n = L.size();
	if (n < 2) 
		return;

	List<T> L1;
	List<T> L2;
	List<T> Le;

	Iterator<T> last = L.end();
	last.previous();
	T pivot = last.get();

	Iterator<T> li = L.begin();
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

void compareAndPrint(FiveCards fc1, FiveCards fc2){  // 2개의 FiveCards를 비교한 다음 결과를 출력해주는 함수

	cout << "Left: " << fc1;
	cout << "Right: " << fc2;

	int diff = fc1.compareInPoker(fc2);

	if(diff > 0)
		cout << "Compare Result: 왼쪽의 카드 5장이 더 큽니다." << endl;
	else if(diff < 0)
		cout << "Compare Result: 오른쪽의 카드 5장이 더 큽니다." << endl;
	else
		cout << "Compare Result: 왼쪽과 오른쪽의 카드 5장 모두 동등합니다." << endl;

	cout << endl;
}

void fiveCardsTestInPoker(){  // 포커 순으로 비교하는 방식을 사용했을 때, 여러 가지 case에 대해서 FiveCards 2개를 비교하는 함수

	cout << "--- Test - 왼쪽과 오른쪽의 5장의 카드 서로 비교하기  (사전 순) ---" << endl;
	cout << endl;

	FiveCards fc1;
	FiveCards fc2;

	fc1[0] = Card(3,2);
	fc1[1] = Card(4,2);
	fc1[2] = Card(3,3);
	fc1[3] = Card(4,3);
	fc1[4] = Card(3,4);

	fc2[0] = Card(3,3);
	fc2[1] = Card(4,3);
	fc2[2] = Card(3,4);
	fc2[3] = Card(4,6);
	fc2[4] = Card(3,7);

	/*
	 * Left: ♥2 ♠2 ♥3 ♠3 ♥4
	 * Right: ♥3 ♠3 ♥4 ♠6 ♥7
	 */
	compareAndPrint(fc1, fc2);

	fc1[0] = Card(3,2);
	fc1[1] = Card(3,3);
	fc1[2] = Card(3,4);
	fc1[3] = Card(4,2);
	fc1[4] = Card(4,3);

	fc2[0] = Card(3,7);
	fc2[1] = Card(4,3);
	fc2[2] = Card(3,3);
	fc2[3] = Card(3,4);
	fc2[4] = Card(4,6);

	/*
	 * Left: ♥2 ♥3 ♥4 ♠2 ♠3
	 * Right: ♥7 ♠3 ♥3 ♥4 ♠6
	 */
	compareAndPrint(fc1, fc2);

	fc1[0] = Card(3,9);
	fc1[1] = Card(4,9);
	fc1[2] = Card(3,9);
	fc1[3] = Card(4,11);
	fc1[4] = Card(3,11);

	fc2[0] = Card(3,8);
	fc2[1] = Card(4,8);
	fc2[2] = Card(3,8);
	fc2[3] = Card(4,11);
	fc2[4] = Card(3,11);

	/*
	 * Left: ♥9 ♠9 ♥9 ♠J ♥J
	 * Right: ♥8 ♠8 ♥8 ♠J ♥J
	 */
	compareAndPrint(fc1, fc2);

	fc1[0] = Card(4,11);
	fc1[1] = Card(3,11);
	fc1[2] = Card(3,9);
	fc1[3] = Card(4,9);
	fc1[4] = Card(3,9);

	fc2[0] = Card(3,11);
	fc2[1] = Card(3,8);
	fc2[2] = Card(3,8);
	fc2[3] = Card(4,11);
	fc2[4] = Card(4,8);

	/*
	 * Left: ♠J ♥J ♥9 ♠9 ♥9
	 * Right: ♥J ♥8 ♥8 ♠J ♠8
	 */
	compareAndPrint(fc1, fc2);

	fc1[0] = Card(3,8);
	fc1[1] = Card(4,9);
	fc1[2] = Card(3,10);
	fc1[3] = Card(4,11);
	fc1[4] = Card(3,12);

	fc2[0] = Card(3,10);
	fc2[1] = Card(4,11);
	fc2[2] = Card(3,12);
	fc2[3] = Card(4,13);
	fc2[4] = Card(3,1);

	/*
	 * Left: ♥8 ♠9 ♥10 ♠J ♥Q
	 * Right: ♥10 ♠J ♥Q ♠K ♥A
	 */
	compareAndPrint(fc1, fc2);

	fc1[0] = Card(3,12);
	fc1[1] = Card(4,9);
	fc1[2] = Card(3,8);
	fc1[3] = Card(4,11);
	fc1[4] = Card(3,10);

	fc2[0] = Card(3,1);
	fc2[1] = Card(4,11);
	fc2[2] = Card(3,12);
	fc2[3] = Card(4,13);
	fc2[4] = Card(3,10);

	/*
	 * Left: ♥Q ♠9 ♥8 ♠J ♥10
	 * Right: ♥A ♠J ♥Q ♠K ♥10
	 */
	compareAndPrint(fc1, fc2);

	fc1[0] = Card(3,8);
	fc1[1] = Card(4,9);
	fc1[2] = Card(3,10);
	fc1[3] = Card(4,11);
	fc1[4] = Card(1,12);

	fc2[0] = Card(3,8);
	fc2[1] = Card(4,9);
	fc2[2] = Card(3,10);
	fc2[3] = Card(4,11);
	fc2[4] = Card(4,12);

	/*
	 * Left: ♥8 ♠9 ♥10 ♠J ♣Q
	 * Right: ♥8 ♠9 ♥10 ♠J ♠Q
	 */
	compareAndPrint(fc1, fc2);

	fc1[0] = Card(3,8);
	fc1[1] = Card(4,11);
	fc1[2] = Card(4,9);
	fc1[3] = Card(1,12);
	fc1[4] = Card(3,10);

	fc2[0] = Card(4,12);
	fc2[1] = Card(4,9);
	fc2[2] = Card(3,8);
	fc2[3] = Card(4,11);
	fc2[4] = Card(3,10);

	/*
	 * Left: ♥8 ♠J ♠9 ♣Q ♥10
	 * Right: ♠Q ♠9 ♥8 ♠J ♥10
	 */
	compareAndPrint(fc1, fc2);
}

int main()
{
	fiveCardsTestInPoker();

	return 0;
}

