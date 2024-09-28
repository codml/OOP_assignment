#pragma once

#include <iostream>

class Clock
{
public:
    Clock(); // 생성자
    ~Clock(); // 소멸자

    void increaseHour(); // 1시간 증가
    void increaseMinute(); // 1분 증가
    void increaseSecond(); // 1초 증가

    void setTime(int second); // private 멤버 함수로 멤버 변수들 설정
    void printTime(); // 시, 분, 초 출력

private:
    void setHour(int hour); // 멤버 변수 hour에 값 삽입
    void setMinute(int minute); // 멤버 변수 minute에 값 삽입
    void setSecond(int second); // 멤버 변수 second에 값 삽입

    int hour;
    int minute;
    int second;
};