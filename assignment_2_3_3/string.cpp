#include "string.h"

oopstd::string::string()
{
	s = new char[1];
	s[0] = 0; // 기본 생성자는 빈 문자열을 가짐
	len = 0; // 길이는 0
}

oopstd::string::string(const char* s)
{
	this->len = strlen(s); // 매개변수 문자열의 길이로 len 초기화
	this->s = new char[this->len + 1];
	strcpy(this->s, s);
	this->s[len] = 0; // 매개변수 문자열의 길이 + 1만큼 할당해 복사 후 NULL로 끝나게 보장
}

oopstd::string::string(const oopstd::string& str)
{
	this->len = str.len; // 매개변수 string의 길이로 len 초기화
	this->s = new char[this->len + 1];
	strcpy(this->s, str.s);
	this->s[len] = 0; // 문자열 복사 후 NULL로 끝나게 보장
}

oopstd::string::~string()
{
	delete[] s; // s에 할당된 문자열 초기화
}

oopstd::string& oopstd::string::assign(const oopstd::string& str)
{
	this->len = str.len; // 매개변수로 받은 string의 길이로 len 초기화
	if (this->s)
		delete[] this->s; // 존재한다면 기존 s 메모리 해제
	this->s = new char[this->len + 1];
	strcpy(this->s, str.s);
	this->s[len] = 0;
	return *this;
}

char& oopstd::string::at(size_t pos)
{
	if (pos >= len) // 위치를 벗어나면
	{
		std::cout << "incorrect pos" << std::endl;
		return s[len]; // s의 맨 끝에 있는 null문자를 반환
	}
	else
		return s[pos]; // s 문자열의 pos 위치에 있는 문자 반환
}

const char* oopstd::string::c_str() const
{
	return (const char*)s; // NULL로 끝나는 문자열 s의 주소값 반환
}

void oopstd::string::clear()
{
	delete[] s; // 기존 메모리 삭제
	s = new char[1];
	s[0] = 0; // 빈 문자열 할당
	len = 0; // 길이는 0
}

void oopstd::string::push_back(char c)
{
	char* new_ptr;

	len++; // 미리 길이 늘리기
	new_ptr = new char[len + 1]; // 새 문자열
	strcpy(new_ptr, s); // 기존 문자열 복사
	new_ptr[len - 1] = c; // 마지막에 매개변수 문자 삽입
	new_ptr[len] = 0; // NULL로 끝내기
	delete[] s; // 기존 문자열 메모리 해제
	s = new_ptr; // 문자열 갱신
}

int oopstd::string::compare(const oopstd::string* str) const
{
	size_t i;

	i = 0;
	while (i < this->len && i < str->len) // 둘 중 하나를 다 읽을 때까지 반복
	{
		if (this->s[i] != str->s[i]) // 둘이 다르면
			return (this->s[i] - str->s[i]); // 그 차이를 반환
		i++;
	}
	return (this->s[i] - str->s[i]); // 둘 중 하나라도 끝까지 비교했으면, 그 차를 반환
	// 둘 중 하나만 끝났다면 끝난 문자열은 s[i]가 0이 될 것!
}

oopstd::string& oopstd::string::replace(size_t pose, size_t len, const oopstd::string* str)
{
	char* new_s;

	if (pose >= this->len || pose + len > this->len || pose >= len) // 범위가 벗어나면
	{
		std::cout << "incorrect input" << std::endl;
		return *this; // replace 안 하고 기존 string 반환
	}
	new_s = new char[this->len - (len - pose) + str->len + 1]; // 갱신된 길이만큼 메모리 할당
	strncpy(new_s, this->s, pose); // pose 전 문자열 복사
	strcpy(new_s + pose, str->s); // str 복사
	strncpy(new_s + pose + str->len, this->s + len, this->len - len); // len 이후의 문자열 복사
	this->len = this->len - (len - pose) + str->len; // len 갱신
	new_s[this->len] = 0; // NULL 종단문자 보장
	delete[] this->s; // 기존 메모리 삭제
	this->s = new_s; // s 갱신
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
	buf = new char[len + 1]; // 반환할 string의 문자열
	strncpy(buf, this->s + pos, len); // pos 위치부터 len만큼 문자열 복사
	buf[len] = 0; // NULL 종단문자 추가
	oopstd::string ret(buf); // 추출한 문자열로 string 생성
	delete[] buf; // string이 생겼으니 메모리 해제
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
				return i; // 첫 번째 문자가 같고, str과 전부 같은 부분이 해당 string에 있으면
		// 그 인덱스 반환
	}
	return -1; // 실패하면 string::npos(= size_t의 최대 값) 반환
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
	ptr = str.c_str(); // 외부에서 string의 문자열에 접근 불가하므로 c_str()을 사용해 ptr로 받음
	while (ptr[i] == ' ' || (ptr[i] >= 9 && ptr[i] <= 13))
		i++; // whitespace를 받는 구간
	if (ptr[i] == '-' || ptr[i] == '+')
	{
		if (ptr[i] == '-')
			minus *= -1;
		i++;
	} // 부호를 처리하는 구간
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		ret *= base;
		ret += ptr[i] - '0';
		i++;
	} // 수를 앞자리부터 읽으며 long형 변수 ret에 채워나감
	if (idx)
		*idx = i; // idx가 null이 아니면 str의 시작 index 넣기
	return ((int)(ret * minus)); // 수의 정보를 담은 ret과 minus를 곱해 반환
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
	ptr = str.c_str(); // 클래스 외부에서 string의 문자열에 접근 불가하므로 c_str() 사용
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
	if (ptr[i] == '.') // 소수부를 받는 구간
	{
		i++;
		while (ptr[i] >= '0' && ptr[i] <= '9')
		{
			dem *= 0.1;
			ret += dem * (float)(ptr[i] - '0');
			i++;
		} // 소수점 뒤의 자리는 각 자리에 0.1을 계속 곱해 ret에 더함
		dem = 1;
		if (ptr[i] == 'e' || ptr[i] == 'E') // 부동소수점 부분
		{
			i++;
			if (ptr[i] == '-') // 부동소수점 10^-n부분
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
			else // 부동소수점 10^n 부분
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

	s = new char[15]; // int 정수는 최대 11자리(10자리, '-' 부호)이므로 넉넉하게 잡음
	idx = 0;
	if (val < 0) // 음수라면
	{
		if (val == -2147483648)
		{
			strcpy(s, "-2147483648");
			idx += 11; // 음수 최소값은 -1을 곱해서 연산을 할 수 없으므로 예외처리
		}
		else
		{
			s[idx++] = '-';
			val *= -1; // '-'부호를 붙이고 val에 -1을 곱해 양수로 바꿈
			for (; val; val /= 10)
				s[idx++] = val % 10 + '0'; // 마지막 자리부터 역순으로 문자열 변환
			for (int i = 1; i < idx / 2 + 1; i++)
			{
				tmp = s[i];
				s[i] = s[idx - i];
				s[idx - i] = tmp;
			} // '-' 부호 다음 문자부터 끝까지 swap 연산(뒤집기)
		}
	}
	else // 양수라면
	{
		if (!val) // 입력 값이 0이면
			s[idx++] = '0'; // '0'만 담긴 문자열
		for (; val; val /= 10)
			s[idx++] = val % 10 + '0';
		for (int i = 0; i < idx / 2; i++)
		{
			tmp = s[i];
			s[i] = s[idx - 1 - i];
			s[idx - 1 - i] = tmp;
		} // 음수일 때와 동일한 알고리즘
	}
	s[idx] = 0; // NULL로 끝내기
	oopstd::string a(s); // s로 string 생성
	return a;
}

oopstd::string oopstd::to_string(float val)
{
	char* s;
	size_t idx;
	char tmp;
	int tmp_num;
	float tmp_dem;

	s = new char[50]; // float은 int보다 범위가 크므로 더 넉넉하게 메모리 잡기
	idx = 0;
	tmp_num = (int)val; // 매개변수의 정수 부분
	if (val < 0)
		tmp_dem = val * -1 + tmp_num;
	else
		tmp_dem = val - tmp_num; // 매개변수의 소수 부분
	if (tmp_num < 0) // 음수라면
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
	} // to_string(int val)과 동일
	else // 양수라면
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
	} // to_string(int val)과 동일
	if (tmp_dem) // 소수부분이 있으면
		s[idx++] = '.'; // 일단 소수점 작성
	for (int i = 0; i < 6; tmp_dem -= tmp_num, i++)
	{ // float의 유효숫자는 소수점 6번째 자리까지!
		tmp_dem *= 10; // 10^-1번째 자리의 소수가 정수 부분으로 오도록 10 곱함
		tmp_num = (int)tmp_dem; // 정수 부분 자르기
		s[idx++] = tmp_num + '0'; // 문자열에 삽입
	}
	s[idx] = 0; // NULL 종단 문자
	oopstd::string a(s); // s로 string 생성
	return a;
}
