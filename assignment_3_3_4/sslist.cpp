#include "sslist.h"

Score::Score()
{
    m_pNext = 0;
    m_pPrev = 0;
    m_Avg = 0; // 멤버 변수 초기화
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
    m_pPrev = pPrev; // 멤버 변수에 값 카피
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
    return m_pPrev; // 멤버 변수 반환
}

StudentScoreList::StudentScoreList()
{
    m_pHead = 0;
    m_pTail = 0; // 멤버 변수 초기화
}

StudentScoreList::~StudentScoreList()
{
    Score* tmp;

    while (m_pHead)
    {
        tmp = m_pHead;
        m_pHead = m_pHead->GetNext();
        delete tmp; // m_pHead부터 하나씩 노드 메모리 해제
    }
}

void StudentScoreList::Insert(Score* pScore)
{
    if (!m_pHead) // 리스트가 비었으면
    {
        m_pHead = pScore;
        m_pTail = pScore; // 새 노드가 head이자 tail
        return;
    }
    if (m_pHead->GetAvg() > pScore->GetAvg()) // 새 노드가 맨 앞에 추가되어야 한다면
    {
        pScore->SetNext(m_pHead); // 새 노드의 다음은 head
        m_pHead->SetPrev(pScore); // head의 이전은 새 노드
        m_pHead = pScore; // head를 새 노드로 바꿈
        return;
    }
    for (Score* prev = m_pHead; prev->GetNext(); prev = prev->GetNext()) // head의 다음부터 끝까지
    {
        if (prev->GetNext()->GetAvg() > pScore->GetAvg())
        {
            // 현재 노드(prev의 다음 노드)의 앞에 새 노드가 와야 한다면
            pScore->SetNext(prev->GetNext()); // 새 노드의 다음은 현재 노드
            pScore->SetPrev(prev); // 새 노드이 이전은 prev
            prev->GetNext()->SetPrev(pScore); // 현재 노드의 이전은 새 노드
            prev->SetNext(pScore); // prev의 다음 노드는 새 노드
            return;
        }
    } // 마지막까지 비교를 했는데 함수가 안 끝났다 == 맨 마지막에 추가해야 한다
    pScore->SetPrev(m_pTail); // 새 노드의 이전 노드가 tail
    m_pTail->SetNext(pScore); // tail의 다음이 새 노드
    m_pTail = pScore; // tail을 새 노드로 바꿈
}

void StudentScoreList::PrintList(bool isAscending)
{
    if (isAscending) // 오름차순으로 출력해야 하면(인수가 true)
    {
        for (Score* tmp = m_pHead; tmp; tmp = tmp->GetNext())
            std::cout << tmp->GetAvg() << " "; // head부터 연속적으로 다음 노드를 출력
        std::cout << std::endl;
    }
    else // 내림차순으로 출력해야 하면(인수가 false)
    {
        for (Score* tmp = m_pTail; tmp; tmp = tmp->GetPrev())
            std::cout << tmp->GetAvg() << " "; // tail부터 연속적으로 이전 노드를 출력
        std::cout << std::endl;
    }
}