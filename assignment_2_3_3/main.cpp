#include <string>
#include <iostream>
#include "string.h"

using namespace std;

int main()
{
	string a; // std::string
	oopstd::string b;
	size_t idx_a = 0;
	size_t idx_b = 0;

	a.assign("abcde");
	b.assign("abcde"); // 같은 문자열 할당
	cout << "assign func compare: " << a.c_str() << " vs " << b.c_str() << endl;
	cout << endl << "at func compare : " << a.at(3) << " vs " << b.at(3) << endl;
	a.clear();
	b.clear(); // 둘다 내용 삭제
	cout << endl << "clear func compare: " << a.c_str() << " vs " << b.c_str() << endl;
	a.assign("abcde");
	b.assign("abcde");
	a.push_back('f');
	b.push_back('f'); // 같은 문자열 할당 후 ,같은 문자 삽입
	cout << endl << "push_back func compare: " << a.c_str() << " vs " << b.c_str() << endl;
	oopstd::string c("abcgg"); // 비교용 string
	oopstd::string d(c); // copy constructor test
	cout << endl << "compare func compare: " << a.compare("abcgg") << " vs " << b.compare(&d) << endl;
	oopstd::string e("abcd"); // 비교용 string(2)
	cout << endl << "compare func compare(2): " << a.compare("abcd") << " vs " << b.compare(&e) << endl;
	a.replace(0, 2, "Alphabet"); // 0번째 위치부터 2자리를 빼고 새 문자열 삽입
	oopstd::string f("Alphabet");
	b.replace(0, 2, &f); // 같은 기능 수행
	cout << endl << "replace func compare: " << a.c_str() << " vs " << b.c_str() << endl;
	cout << endl << "substr func compare: " << a.substr(2, 3) << " vs " << (b.substr(2, 3)).c_str() << endl;
	cout << endl << "find func compare: " << a.find('p') << " vs " << b.find("pha") << endl;
	string g("2147483647asd");
	oopstd::string h("2147483647asd"); //stoi test용
	string i("36.4242asdf");
	oopstd::string j("36.4242asdf"); //stof test용
	cout << endl << "stoi func compare: " << stoi(g, &idx_a) << " " << idx_a << " vs " << oopstd::stoi(h, &idx_b) << " " << idx_b << endl;
	cout << endl << "stof func compare: " << stof(i, &idx_a) << " " << idx_a << " vs " << oopstd::stof(j, &idx_b) << " " << idx_b << endl;
	cout << endl << "to_string compare(int): " << to_string(-1234) << " vs " << (oopstd::to_string((int)(-1234))).c_str() << endl;
	cout << endl << "to_string compare(float): " << to_string((float)-41.2341) << " vs " << (oopstd::to_string((float)(-41.2341))).c_str() << endl;
	cout << endl << j.at(100) << endl; // pos 에러 확인용 test들
	cout << endl << j.replace(0, 100, (const oopstd::string*)&g).c_str() << endl;
	cout << endl << j.replace(100, 8, (const oopstd::string*)&g).c_str() << endl;
	cout << endl << j.replace(10, 8, (const oopstd::string*)&g).c_str() << endl;
	return (0);
}