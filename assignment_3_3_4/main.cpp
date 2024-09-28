#include <iostream>
#include <cstring>
#include "sslist.h"

using namespace std;

int main()
{
    StudentScoreList sslist; // �ν��Ͻ� ����
	char buf[10];
    int math, english, science;
    Score* tmp;

    for (int i = 0; true; i++)
    {
		cout << "Insert student " << i + 1 << "(exit: no): ";
		cin >> buf;
		if (!strcmp(buf, "no")) // no�� �Է¹����� �л� �Է��� �ߴ�
			break;
		cout << "Math score: ";
		cin >> math;
		cout << "English score: ";
		cin >> english;
		cout << "Science score: ";
		cin >> science;
		tmp = new Score; // �� ���(���� ��� ����)
		tmp->SetAvg((math + english + science) / (double)3); // ���� ����� ����� ��忡 ī��
		sslist.Insert(tmp); // ����Ʈ�� ��带 ����
    }
	cout << "Ascending order: " << endl;
	sslist.PrintList(true); // PrintList()�� �μ��� true�̹Ƿ� ��������(head����)���� ���
	cout << "Descending order: " << endl;
	sslist.PrintList(false); // PrintList()�� �μ��� false�̹Ƿ� ��������(tail����)���� ���
    return 0;
}