#include "sslist.h"

Score::Score()
{
    m_pNext = 0;
    m_pPrev = 0;
    m_Avg = 0; // ��� ���� �ʱ�ȭ
}

Score::~Score()
{
    m_pNext = 0;
    m_pPrev = 0;
    m_Avg = 0;
}

void Score::SetAvg(double avg)
{
    m_Avg = avg;
}

void Score::SetNext(Score* pNext)
{
    m_pNext = pNext;
}

void Score::SetPrev(Score* pPrev)
{
    m_pPrev = pPrev; // ��� ������ �� ī��
}

double Score::GetAvg()
{
    return m_Avg;
}

Score* Score::GetNext()
{
    return m_pNext;
}

Score* Score::GetPrev()
{
    return m_pPrev; // ��� ���� ��ȯ
}

StudentScoreList::StudentScoreList()
{
    m_pHead = 0;
    m_pTail = 0; // ��� ���� �ʱ�ȭ
}

StudentScoreList::~StudentScoreList()
{
    Score* tmp;

    while (m_pHead)
    {
        tmp = m_pHead;
        m_pHead = m_pHead->GetNext();
        delete tmp; // m_pHead���� �ϳ��� ��� �޸� ����
    }
}

void StudentScoreList::Insert(Score* pScore)
{
    if (!m_pHead) // ����Ʈ�� �������
    {
        m_pHead = pScore;
        m_pTail = pScore; // �� ��尡 head���� tail
        return;
    }
    if (m_pHead->GetAvg() > pScore->GetAvg()) // �� ��尡 �� �տ� �߰��Ǿ�� �Ѵٸ�
    {
        pScore->SetNext(m_pHead); // �� ����� ������ head
        m_pHead->SetPrev(pScore); // head�� ������ �� ���
        m_pHead = pScore; // head�� �� ���� �ٲ�
        return;
    }
    for (Score* prev = m_pHead; prev->GetNext(); prev = prev->GetNext()) // head�� �������� ������
    {
        if (prev->GetNext()->GetAvg() > pScore->GetAvg())
        {
            // ���� ���(prev�� ���� ���)�� �տ� �� ��尡 �;� �Ѵٸ�
            pScore->SetNext(prev->GetNext()); // �� ����� ������ ���� ���
            pScore->SetPrev(prev); // �� ����� ������ prev
            prev->GetNext()->SetPrev(pScore); // ���� ����� ������ �� ���
            prev->SetNext(pScore); // prev�� ���� ���� �� ���
            return;
        }
    } // ���������� �񱳸� �ߴµ� �Լ��� �� ������ == �� �������� �߰��ؾ� �Ѵ�
    pScore->SetPrev(m_pTail); // �� ����� ���� ��尡 tail
    m_pTail->SetNext(pScore); // tail�� ������ �� ���
    m_pTail = pScore; // tail�� �� ���� �ٲ�
}

void StudentScoreList::PrintList(bool isAscending)
{
    if (isAscending) // ������������ ����ؾ� �ϸ�(�μ��� true)
    {
        for (Score* tmp = m_pHead; tmp; tmp = tmp->GetNext())
            std::cout << tmp->GetAvg() << " "; // head���� ���������� ���� ��带 ���
        std::cout << std::endl;
    }
    else // ������������ ����ؾ� �ϸ�(�μ��� false)
    {
        for (Score* tmp = m_pTail; tmp; tmp = tmp->GetPrev())
            std::cout << tmp->GetAvg() << " "; // tail���� ���������� ���� ��带 ���
        std::cout << std::endl;
    }
}