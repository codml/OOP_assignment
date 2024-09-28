#pragma once
#include <iostream>

class Score // 평균 성적을 담은 노드
{
private:
    Score* m_pNext; // 이후 노드를 가리킴
    Score* m_pPrev; // 이전 노드를 가리킴
    double m_Avg; // 성적의 평균

public:
    Score();
    ~Score();

    void SetAvg(double avg);
    void SetNext(Score* pNext);
    void SetPrev(Score* pPrev); // 멤버 변수에 값 카피
    double GetAvg();
    Score* GetNext();
    Score* GetPrev(); // 멤버 변수 반환
};

class StudentScoreList
{
private:
    Score* m_pHead; // 리스트의 맨 앞 노드
    Score* m_pTail; // 리스트의 맨 뒤 노드

public:
    StudentScoreList();
    ~StudentScoreList();

    void Insert(Score* pScore); // 노드를 성적 오름차순을 유지시키는 위치에 삽입
    void PrintList(bool isAscending); // 오름차순 또는 내림차순으로 성적 출력
};