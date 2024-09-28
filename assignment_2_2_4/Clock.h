#pragma once

#include <iostream>

class Clock
{
public:
    Clock(); // ������
    ~Clock(); // �Ҹ���

    void increaseHour(); // 1�ð� ����
    void increaseMinute(); // 1�� ����
    void increaseSecond(); // 1�� ����

    void setTime(int second); // private ��� �Լ��� ��� ������ ����
    void printTime(); // ��, ��, �� ���

private:
    void setHour(int hour); // ��� ���� hour�� �� ����
    void setMinute(int minute); // ��� ���� minute�� �� ����
    void setSecond(int second); // ��� ���� second�� �� ����

    int hour;
    int minute;
    int second;
};