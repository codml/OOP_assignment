#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "oopstd.h"

using namespace std;

int main()
{
    char mem1[5];
    char mem2[5];
    char mem3[5];
    char mem4[5]; // memset, memcpy�� ���� �迭
    char arr1[50];
    char arr2[] = "I love OOP class";
    char arr3[50];
    char arr4[] = "I love OOP class";
    char arr5[] = "I love A+ grade";
    char arr_int[] = "8732468764921837324";
    char arr_double[] = "123.23423e-10";

    cout << "*****memory : filled with a*****" << endl;
    memset(mem1, 'a', 5);
    oopstd::memset(mem2, 'a', 5); // �� �Լ� ��� �޸� ������ 'a'�� ä��
    for (int i = 0; i < 5; i++)
        cout << "memset: " << mem1[i] << " oopstd::memset: " << mem2[i] << endl;
    cout << "*****memory copy*****" << endl;
    memcpy(mem3, mem1, 5);
    oopstd::memcpy(mem4, mem2, 5);
    for (int i = 0; i < 5; i++)
        cout << "memcpy: " << mem3[i] << " oopstd::memcpy: " << mem4[i] << endl;
    // �޸� ������ ������ ���
    cout << "*****str compare*****" << endl;
    cout << arr2 << " " << arr5 << endl;
    if (strcmp(arr2, arr5) > 0 && oopstd::strcmp(arr2, arr5) > 0)
        // �� ���ڿ��� O�� A���� ���̰� ���µ�, 'O' > 'A'�̹Ƿ� arr2�� �� Ŀ����
        cout << "***compare success!***" << endl;
    else
        cout << "***compare failed...***" << endl;
    cout << "*****only 5 bytes compare(strings will be same)*****" << endl;
    if (!strncmp(arr2, arr5, 5) && !oopstd::strncmp(arr2, arr5, 5))
        // �� ���ڿ��� ���̴� 7��° �ε������� ���Ƿ� 5����Ʈ�� ���ϸ� ���̰� ����
        cout << "***compare success!***" << endl;
    else
        cout << "***compare failed...***" << endl;
    cout << "*****strings will be copied to other memories*****" << endl;
    // ���ڿ� ī��
    cout << "strcpy: " << strcpy(arr1, arr2) << " oopstd::strcpy: " << oopstd::strcpy(arr3, arr4) << endl;
    memset(arr1, 0, 50);
    oopstd::memset(arr3, 0, 50); // �η� �迭 �ʱ�ȭ
    cout << "*****only 10 bytes will be copied(strings will be same)*****" << endl;
    // 10����Ʈ�� ����
    cout << "strncpy: " << strncpy(arr1, arr2, 10) << " oopstd::strncpy: " << oopstd::strncpy(arr3, arr4, 10) << endl;
    cout << "*****I love OOP class" << " strlen test*****" << endl;
    cout << "strlen: " << strlen(arr2) << " oopstd::strlen: " << oopstd::strlen(arr2) << endl;
    cout << "atoi: " << atoi(arr_int) << " oopstd::atoi: " << oopstd::atoi(arr_int) << endl;
    cout << "atof: " << atof(arr_double) << " oopstd::atof: " << oopstd::atof(arr_double) << endl;
    return 0;
}