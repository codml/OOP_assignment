#include <iostream>
#include <cstring>
#include "person.h"

using namespace std;

int main()
{
    Professor park; // Professor class 인스턴스 생성
	Student kim; // Student class 인스턴스 생성
	char buf[1024]; // 정보를 받을 문자열
	char *ptr[5]; // ','단위로 쪼개진 문자열들의 첫 주소를 담을 포인터 배열

	cout << "Insert park's information(age, name, professor number, major):" << endl;
	cin.getline(buf, 1024); // 공백 포함 받기
	ptr[0] = strtok(buf, ",");
	for (int i = 1; i < 4; i++)
		ptr[i] = strtok(0, ","); // 포인터 배열에 ','를 기준으로 끊은 문자열에 주소값들을 저장
	for (int i = 0; i < 4; i++)
	{
		if (!(ptr[i])) // 하나라도 널(요소들 중 한 개 이상이 들어오지 않았다는 의미)이 있으면
		{
			cout << "input error" << endl;
			return 0;
		}
	}
	park.Setage(atoi(ptr[0])); 
	park.Setname(ptr[1]);
	park.SetprofNum(atoi(ptr[2]));
	park.Setmajor(ptr[3]); // 멤버 변수에 카피
	cout << "Insert kim's information(age, name, student number, major, school year):" << endl;
	cin.getline(buf, 1024); // 위와 같은 과정 반복
	ptr[0] = strtok(buf, ",");
	for (int i = 1; i < 5; i++)
		ptr[i] = strtok(0, ",");
	for (int i = 0; i < 5; i++)
	{
		if (!(ptr[i]))
		{
			cout << "input error" << endl;
			return 0;
		}
	}
	kim.Setage(atoi(ptr[0])); 
	kim.Setname(ptr[1]);
	kim.SetstuNum(atoi(ptr[2]));
	kim.Setmajor(ptr[3]);
	kim.SetschoolYear(atoi(ptr[4]));
	cout << "park's information: " << endl;
	park.Say(); // 오버라이딩한 Professor class의 Say()함수가 호출
	cout << "kim's information: " << endl;
	kim.Say(); // 오버라이딩한 Student class의 Say()함수가 호출
	return 0;
}