#pragma once

class Node
{
private:
    Node* m_pNext;
    int m_data;

public:
    Node();
    ~Node();

    void SetData(int n); // 데이터 카피
    void SetNext(Node* pNext); // 다음 노드 주소 카피
    int GetData(); // 데이터 반환
    Node* GetNext(); // 다음 노드의 주소 반환
};