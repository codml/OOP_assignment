#pragma once

class Node
{
private:
    Node* m_pNext;
    int m_data;

public:
    Node();
    ~Node();

    void SetData(int n); // m_data�� ī��
    void SetNext(Node* pNext); // m_pNext�� ī��
    int GetData(); // m_data ��ȯ
    Node* GetNext(); // m_pNext ��ȯ
};