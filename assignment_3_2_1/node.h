#pragma once
#include <iostream>
#include <cstdlib>
#include <cmath>

class Node
{
private:
    int data;
    Node* next;

public:
    Node();

    void setNext(Node* ptr);
    void setData(int data);
    Node* getNext();
    int getData(); // ��� ������ �� �Ҵ� �� ��ȯ
};

Node* make_rand_list(); // 16���� ������ ���� ������ ����Ʈ ����
void insertion_sort(Node** head); // ���� ���ķ� descending order�� ������ ����
void print_list(Node* head); // ����Ʈ ���
Node* Binary_Search(Node* p, int n); // ���� Ž��
void memory_free(Node* head); // �޸� ����