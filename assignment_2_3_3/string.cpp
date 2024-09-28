#include "string.h"

oopstd::string::string()
{
	s = new char[1];
	s[0] = 0; // �⺻ �����ڴ� �� ���ڿ��� ����
	len = 0; // ���̴� 0
}

oopstd::string::string(const char* s)
{
	this->len = strlen(s); // �Ű����� ���ڿ��� ���̷� len �ʱ�ȭ
	this->s = new char[this->len + 1];
	strcpy(this->s, s);
	this->s[len] = 0; // �Ű����� ���ڿ��� ���� + 1��ŭ �Ҵ��� ���� �� NULL�� ������ ����
}

oopstd::string::string(const oopstd::string& str)
{
	this->len = str.len; // �Ű����� string�� ���̷� len �ʱ�ȭ
	this->s = new char[this->len + 1];
	strcpy(this->s, str.s);
	this->s[len] = 0; // ���ڿ� ���� �� NULL�� ������ ����
}

oopstd::string::~string()
{
	delete[] s; // s�� �Ҵ�� ���ڿ� �ʱ�ȭ
}

oopstd::string& oopstd::string::assign(const oopstd::string& str)
{
	this->len = str.len; // �Ű������� ���� string�� ���̷� len �ʱ�ȭ
	if (this->s)
		delete[] this->s; // �����Ѵٸ� ���� s �޸� ����
	this->s = new char[this->len + 1];
	strcpy(this->s, str.s);
	this->s[len] = 0;
	return *this;
}

char& oopstd::string::at(size_t pos)
{
	if (pos >= len) // ��ġ�� �����
	{
		std::cout << "incorrect pos" << std::endl;
		return s[len]; // s�� �� ���� �ִ� null���ڸ� ��ȯ
	}
	else
		return s[pos]; // s ���ڿ��� pos ��ġ�� �ִ� ���� ��ȯ
}

const char* oopstd::string::c_str() const
{
	return (const char*)s; // NULL�� ������ ���ڿ� s�� �ּҰ� ��ȯ
}

void oopstd::string::clear()
{
	delete[] s; // ���� �޸� ����
	s = new char[1];
	s[0] = 0; // �� ���ڿ� �Ҵ�
	len = 0; // ���̴� 0
}

void oopstd::string::push_back(char c)
{
	char* new_ptr;

	len++; // �̸� ���� �ø���
	new_ptr = new char[len + 1]; // �� ���ڿ�
	strcpy(new_ptr, s); // ���� ���ڿ� ����
	new_ptr[len - 1] = c; // �������� �Ű����� ���� ����
	new_ptr[len] = 0; // NULL�� ������
	delete[] s; // ���� ���ڿ� �޸� ����
	s = new_ptr; // ���ڿ� ����
}

int oopstd::string::compare(const oopstd::string* str) const
{
	size_t i;

	i = 0;
	while (i < this->len && i < str->len) // �� �� �ϳ��� �� ���� ������ �ݺ�
	{
		if (this->s[i] != str->s[i]) // ���� �ٸ���
			return (this->s[i] - str->s[i]); // �� ���̸� ��ȯ
		i++;
	}
	return (this->s[i] - str->s[i]); // �� �� �ϳ��� ������ ��������, �� ���� ��ȯ
	// �� �� �ϳ��� �����ٸ� ���� ���ڿ��� s[i]�� 0�� �� ��!
}

oopstd::string& oopstd::string::replace(size_t pose, size_t len, const oopstd::string* str)
{
	char* new_s;

	if (pose >= this->len || pose + len > this->len || pose >= len) // ������ �����
	{
		std::cout << "incorrect input" << std::endl;
		return *this; // replace �� �ϰ� ���� string ��ȯ
	}
	new_s = new char[this->len - (len - pose) + str->len + 1]; // ���ŵ� ���̸�ŭ �޸� �Ҵ�
	strncpy(new_s, this->s, pose); // pose �� ���ڿ� ����
	strcpy(new_s + pose, str->s); // str ����
	strncpy(new_s + pose + str->len, this->s + len, this->len - len); // len ������ ���ڿ� ����
	this->len = this->len - (len - pose) + str->len; // len ����
	new_s[this->len] = 0; // NULL ���ܹ��� ����
	delete[] this->s; // ���� �޸� ����
	this->s = new_s; // s ����
	return *this;
}

oopstd::string oopstd::string::substr(size_t pos, size_t len) const
{
	char* buf;

	if (pos >= this->len || pos + len > this->len || pos >= len)
	{
		std::cout << "incorrecn input" << std::endl;
		return *this;
	}
	buf = new char[len + 1]; // ��ȯ�� string�� ���ڿ�
	strncpy(buf, this->s + pos, len); // pos ��ġ���� len��ŭ ���ڿ� ����
	buf[len] = 0; // NULL ���ܹ��� �߰�
	oopstd::string ret(buf); // ������ ���ڿ��� string ����
	delete[] buf; // string�� �������� �޸� ����
	return ret;
}

size_t oopstd::string::find(const oopstd::string& str, size_t pos) const
{
	if (pos >= len)
	{
		std::cout << "incorrect pos" << std::endl;
		return -1;
	}
	for (size_t i = pos; this->s[i]; i++)
	{
		if (this->s[i] == str.s[0] && !strncmp(this->s + i, str.s, str.len))
				return i; // ù ��° ���ڰ� ����, str�� ���� ���� �κ��� �ش� string�� ������
		// �� �ε��� ��ȯ
	}
	return -1; // �����ϸ� string::npos(= size_t�� �ִ� ��) ��ȯ
}

int oopstd::stoi(const oopstd::string& str, size_t* idx, int base)
{
	int		minus;
	size_t	i;
	long	ret;
	const char* ptr;

	minus = 1;
	i = 0;
	ret = 0;
	ptr = str.c_str(); // �ܺο��� string�� ���ڿ��� ���� �Ұ��ϹǷ� c_str()�� ����� ptr�� ����
	while (ptr[i] == ' ' || (ptr[i] >= 9 && ptr[i] <= 13))
		i++; // whitespace�� �޴� ����
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			minus *= -1;
		i++;
	} // ��ȣ�� ó���ϴ� ����
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		ret *= base;
		ret += ptr[i] - '0';
		i++;
	} // ���� ���ڸ����� ������ long�� ���� ret�� ä������
	if (idx)
		*idx = i; // idx�� null�� �ƴϸ� str�� ���� index �ֱ�
	return ((int)(ret * minus)); // ���� ������ ���� ret�� minus�� ���� ��ȯ
}

float oopstd::stof(const oopstd::string& str, size_t* idx)
{
	int		minus;
	float	ret;
	float	dem;
	int		e_num;
	size_t	i;
	const char* ptr;

	minus = 1;
	ret = 0;
	dem = 1;
	e_num = 0;
	i = 0;
	ptr = str.c_str(); // Ŭ���� �ܺο��� string�� ���ڿ��� ���� �Ұ��ϹǷ� c_str() ���
	while (ptr[i] == ' ' || (ptr[i] >= 9 && ptr[i] <= 13))
		i++;
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			minus *= -1;
		i++;
	}
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		ret *= 10;
		ret += ptr[i] - '0';
		i++;
	}
	if (ptr[i] == '.') // �Ҽ��θ� �޴� ����
	{
		i++;
		while (ptr[i] >= '0' && ptr[i] <= '9')
		{
			dem *= 0.1;
			ret += dem * (float)(ptr[i] - '0');
			i++;
		} // �Ҽ��� ���� �ڸ��� �� �ڸ��� 0.1�� ��� ���� ret�� ����
		dem = 1;
		if (ptr[i] == 'e' || ptr[i] == 'E') // �ε��Ҽ��� �κ�
		{
			i++;
			if (ptr[i] == '-') // �ε��Ҽ��� 10^-n�κ�
			{
				i++;
				while (ptr[i] >= '0' && ptr[i] <= '9')
				{
					e_num *= 10;
					e_num += ptr[i] - '0';
					i++;
				}
				for (int i = 0; i < e_num; i++)
					dem *= 0.1;
			}
			else // �ε��Ҽ��� 10^n �κ�
			{
				if (ptr[i] == '+')
					i++;
				while (ptr[i] >= '0' && ptr[i] <= '9')
				{
					e_num *= 10;
					e_num += ptr[i] - '0';
					i++;
				}
				for (int i = 0; i < e_num; i++)
					dem *= 10;
			}
		}
	}
	if (idx)
		*idx = i;
	return ((float)minus * ret * dem);
}

oopstd::string oopstd::to_string(int val)
{
	char* s;
	size_t idx;
	char tmp;

	s = new char[15]; // int ������ �ִ� 11�ڸ�(10�ڸ�, '-' ��ȣ)�̹Ƿ� �˳��ϰ� ����
	idx = 0;
	if (val < 0) // �������
	{
		if (val == -2147483648)
		{
			strcpy(s, "-2147483648");
			idx += 11; // ���� �ּҰ��� -1�� ���ؼ� ������ �� �� �����Ƿ� ����ó��
		}
		else
		{
			s[idx++] = '-';
			val *= -1; // '-'��ȣ�� ���̰� val�� -1�� ���� ����� �ٲ�
			for (; val; val /= 10)
				s[idx++] = val % 10 + '0'; // ������ �ڸ����� �������� ���ڿ� ��ȯ
			for (int i = 1; i < idx / 2 + 1; i++)
			{
				tmp = s[i];
				s[i] = s[idx - i];
				s[idx - i] = tmp;
			} // '-' ��ȣ ���� ���ں��� ������ swap ����(������)
		}
	}
	else // ������
	{
		if (!val) // �Է� ���� 0�̸�
			s[idx++] = '0'; // '0'�� ��� ���ڿ�
		for (; val; val /= 10)
			s[idx++] = val % 10 + '0';
		for (int i = 0; i < idx / 2; i++)
		{
			tmp = s[i];
			s[i] = s[idx - 1 - i];
			s[idx - 1 - i] = tmp;
		} // ������ ���� ������ �˰���
	}
	s[idx] = 0; // NULL�� ������
	oopstd::string a(s); // s�� string ����
	return a;
}

oopstd::string oopstd::to_string(float val)
{
	char* s;
	size_t idx;
	char tmp;
	int tmp_num;
	float tmp_dem;

	s = new char[50]; // float�� int���� ������ ũ�Ƿ� �� �˳��ϰ� �޸� ���
	idx = 0;
	tmp_num = (int)val; // �Ű������� ���� �κ�
	if (val < 0)
		tmp_dem = val * -1 + tmp_num;
	else
		tmp_dem = val - tmp_num; // �Ű������� �Ҽ� �κ�
	if (tmp_num < 0) // �������
	{
		if (tmp_num == -2147483648)
		{
			strcpy(s, "-2147483648");
			idx += 11;
		}
		else
		{
			s[idx++] = '-';
			tmp_num *= -1;
			for (; tmp_num; tmp_num /= 10)
				s[idx++] = tmp_num % 10 + '0';
			for (int i = 1; i < idx / 2 + 1; i++)
			{
				tmp = s[i];
				s[i] = s[idx - i];
				s[idx - i] = tmp;
			}
		}
	} // to_string(int val)�� ����
	else // ������
	{
		if (!tmp_num)
			s[idx++] = '0';
		for (; tmp_num; tmp_num /= 10)
			s[idx++] = tmp_num % 10 + '0';
		for (int i = 0; i < idx / 2; i++)
		{
			tmp = s[i];
			s[i] = s[idx - 1 - i];
			s[idx - 1 - i] = tmp;
		}
	} // to_string(int val)�� ����
	if (tmp_dem) // �Ҽ��κ��� ������
		s[idx++] = '.'; // �ϴ� �Ҽ��� �ۼ�
	for (int i = 0; i < 6; tmp_dem -= tmp_num, i++)
	{ // float�� ��ȿ���ڴ� �Ҽ��� 6��° �ڸ�����!
		tmp_dem *= 10; // 10^-1��° �ڸ��� �Ҽ��� ���� �κ����� ������ 10 ����
		tmp_num = (int)tmp_dem; // ���� �κ� �ڸ���
		s[idx++] = tmp_num + '0'; // ���ڿ��� ����
	}
	s[idx] = 0; // NULL ���� ����
	oopstd::string a(s); // s�� string ����
	return a;
}
