#include <iostream>
#include <cstring>
#include "person.h"

using namespace std;

int main()
{
    Professor park; // Professor class �ν��Ͻ� ����
	Student kim; // Student class �ν��Ͻ� ����
	char buf[1024]; // ������ ���� ���ڿ�
	char *ptr[5]; // ','������ �ɰ��� ���ڿ����� ù �ּҸ� ���� ������ �迭

	cout << "Insert park's information(age, name, professor number, major):" << endl;
	cin.getline(buf, 1024); // ���� ���� �ޱ�
	ptr[0] = strtok(buf, ",");
	for (int i = 1; i < 4; i++)
		ptr[i] = strtok(0, ","); // ������ �迭�� ','�� �������� ���� ���ڿ��� �ּҰ����� ����
	for (int i = 0; i < 4; i++)
	{
		if (!(ptr[i])) // �ϳ��� ��(��ҵ� �� �� �� �̻��� ������ �ʾҴٴ� �ǹ�)�� ������
		{
			cout << "input error" << endl;
			return 0;
		}
	}
	park.Setage(atoi(ptr[0])); 
	park.Setname(ptr[1]);
	park.SetprofNum(atoi(ptr[2]));
	park.Setmajor(ptr[3]); // ��� ������ ī��
	cout << "Insert kim's information(age, name, student number, major, school year):" << endl;
	cin.getline(buf, 1024); // ���� ���� ���� �ݺ�
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
	park.Say(); // �������̵��� Professor class�� Say()�Լ��� ȣ��
	cout << "kim's information: " << endl;
	kim.Say(); // �������̵��� Student class�� Say()�Լ��� ȣ��
	return 0;
}