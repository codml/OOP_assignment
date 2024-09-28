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
    int getData(); // 멤버 변수에 값 할당 및 반환
};

Node* make_rand_list(); // 16개의 랜덤한 값을 가지는 리스트 생성
void insertion_sort(Node** head); // 삽입 정렬로 descending order를 가지게 만듦
void print_list(Node* head); // 리스트 출력
Node* Binary_Search(Node* p, int n); // 이진 탐색
void memory_free(Node* head); // 메모리 해제