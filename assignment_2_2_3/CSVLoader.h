#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib> // atof�� ���� ���

class CSVLoader
{
public:
    CSVLoader(); // ������
    CSVLoader(const char* path); // ������ �����ε�
    ~CSVLoader(); // �Ҹ���

    float** getData() const; // ������ 2���� �迭 ��ȯ
    int getRows() const; // �� ��ȯ
    int getCols() const; // �� ��ȯ

    void parse(const char* path); // CSV���� �Ľ�
    void print(void); // �ܼ� ���

private:
    float** data; // �Ľ̵� 2���� �迭�� �ּҰ��� ���� ����
    int cols;
    int rows;
    int return_cols(std::string str); // ���� ������ ��ȯ�ϴ� �Լ�
};