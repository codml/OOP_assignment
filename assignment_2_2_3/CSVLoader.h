#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib> // atof를 위한 헤더

class CSVLoader
{
public:
    CSVLoader(); // 생성자
    CSVLoader(const char* path); // 생성자 오버로딩
    ~CSVLoader(); // 소멸자

    float** getData() const; // 생성된 2차원 배열 반환
    int getRows() const; // 행 반환
    int getCols() const; // 열 반환

    void parse(const char* path); // CSV파일 파싱
    void print(void); // 단순 출력

private:
    float** data; // 파싱된 2차원 배열의 주소값을 담을 변수
    int cols;
    int rows;
    int return_cols(std::string str); // 열의 개수를 반환하는 함수
};