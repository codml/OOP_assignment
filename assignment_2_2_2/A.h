#pragma once

#include <iostream>
using namespace std;

class A
{
private:
	double num; // private ����: Ŭ���� ���ο�����(��: ��� �Լ�) ���� ����

public: // public: Ŭ���� �ܺο��� ��� ����
	A(double input); // ������: ��ü�� ������� �� ȣ��
	~A(); // �Ҹ���: ��ü�� �Ҹ�� �� ȣ��
};