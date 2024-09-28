#pragma once

class Node
{
private:
    Node* m_pNext;
    int m_data;

public:
    Node();
    ~Node();

    void SetData(int n); // ������ ī��
    void SetNext(Node* pNext); // ���� ��� �ּ� ī��
    int GetData(); // ������ ��ȯ
    Node* GetNext(); // ���� ����� �ּ� ��ȯ
};