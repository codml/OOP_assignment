#pragma once
#include <iostream>

class Score // ��� ������ ���� ���
{
private:
    Score* m_pNext; // ���� ��带 ����Ŵ
    Score* m_pPrev; // ���� ��带 ����Ŵ
    double m_Avg; // ������ ���

public:
    Score();
    ~Score();

    void SetAvg(double avg);
    void SetNext(Score* pNext);
    void SetPrev(Score* pPrev); // ��� ������ �� ī��
    double GetAvg();
    Score* GetNext();
    Score* GetPrev(); // ��� ���� ��ȯ
};

class StudentScoreList
{
private:
    Score* m_pHead; // ����Ʈ�� �� �� ���
    Score* m_pTail; // ����Ʈ�� �� �� ���

public:
    StudentScoreList();
    ~StudentScoreList();

    void Insert(Score* pScore); // ��带 ���� ���������� ������Ű�� ��ġ�� ����
    void PrintList(bool isAscending); // �������� �Ǵ� ������������ ���� ���
};