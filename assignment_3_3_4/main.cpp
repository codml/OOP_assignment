#include <iostream>
#include <cstring>
#include "sslist.h"

using namespace std;

int main()
{
    StudentScoreList sslist; // 인스턴스 생성
	char buf[10];
    int math, english, science;
    Score* tmp;

    for (int i = 0; true; i++)
    {
		cout << "Insert student " << i + 1 << "(exit: no): ";
		cin >> buf;
		if (!strcmp(buf, "no")) // no를 입력받으면 학생 입력을 중단
			break;
		cout << "Math score: ";
		cin >> math;
		cout << "English score: ";
		cin >> english;
		cout << "Science score: ";
		cin >> science;
		tmp = new Score; // 새 노드(성적 평균 생성)
		tmp->SetAvg((math + english + science) / (double)3); // 성적 평균을 계산해 노드에 카피
		sslist.Insert(tmp); // 리스트에 노드를 삽입
    }
	cout << "Ascending order: " << endl;
	sslist.PrintList(true); // PrintList()에 인수가 true이므로 오름차순(head부터)으로 출력
	cout << "Descending order: " << endl;
	sslist.PrintList(false); // PrintList()에 인수가 false이므로 내림차순(tail부터)으로 출력
    return 0;
}