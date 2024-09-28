#pragma once

class Node
{
private:
    Node* m_pNext;
    int m_data;

public:
    Node();
    ~Node();

    void SetData(int n); // m_data에 카피
    void SetNext(Node* pNext); // m_pNext에 카피
    int GetData(); // m_data 반환
    Node* GetNext(); // m_pNext 반환
};