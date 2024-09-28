namespace oopstd {
	// std처럼 namespace를 생성함
	void* memset(void* ptr, int value, size_t num)
	{
		size_t	i;

		i = 0;
		while (i < num)
		{
			((unsigned char*)ptr)[i] = (unsigned char)value;
			// 입력받은 문자를 unsigned char로 캐스팅해 메모리 공간에 복사
			// 바이트 단위로 복사!
			i++;
		}
		return (ptr);
	}

	void* memcpy(void* destination, const void* source, size_t num)
	{
		size_t	i;

		if (destination == source)
			return (0); // 둘이 주소가 같으면 널 반환
		i = 0;
		while (i < num)
		{
			((unsigned char*)destination)[i] = ((const unsigned char*)source)[i];
			// 바이트 단위로 복사
			i++;
		}
		return (destination);
	}

	int	    strcmp(const char* str1, const char* str2)
	{
		size_t	i;

		i = 0;
		while ((unsigned char)str1[i] && (unsigned char)str2[i])
		{
			// 문자 단위로 비교해 다르면 그 차이를 반환
			// 두 문자열 중 하나가 끝날 때까지 비교
			// 각 문자를 unsigned char로 캐스팅해 그 차이를 반환해야 함
			if ((unsigned char)str1[i] != (unsigned char)str2[i])
				return ((unsigned char)str1[i] - (unsigned char)str2[i]);
			i++;
		}
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}

	int     strncmp(const char* str1, const char* str2, size_t num)
	{
		size_t	i;
	
		i = 0;
		while ((unsigned char)str1[i] && (unsigned char)str2[i] && i < num)
		{
			if ((unsigned char)str1[i] != (unsigned char)str2[i])
				return ((unsigned char)str1[i] - (unsigned char)str2[i]);
			i++;
		}
		// 두 문자열 중 하나가 끝나거나 num 자리까지 비교
		if (i < num)
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		return (0);
	}

	char* strcpy(char* destination, const char* source)
	{
		size_t	i;

		i = 0;
		while (source[i])
		{
			destination[i] = source[i];
			i++;
		}
		destination[i] = 0; // 끝에 널 붙여 문자열 완성
		return (destination);
	}

	char* strncpy(char* destination, const char* source, size_t num)
	{
		size_t	i;

		i = 0;
		while (i < num && source[i])
		{
			destination[i] = source[i];
			i++;
		}
		while (i < num)
		{
			destination[i] = 0;
			i++;
		} // source의 길이가 num보다 작으면
		// 남는 공간을 null로 채운다 -> 매뉴얼에 있는 내용
		return (destination);
	}

	size_t	strlen(const char* str)
	{
		size_t	i;

		i = 0;
		while (str[i])
			i++;
		return (i);
	}

	int     atoi(const char* str)
	{
		int		minus;
		long long ret;

		minus = 1;
		ret = 0;
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++; // whitespace를 받는 구간
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				minus *= -1;
			str++;
		} // 부호를 처리하는 구간
		while (*str && (*str >= '0' && *str <= '9'))
		{
			ret *= 10;
			ret += *str - '0';
			str++;
		} // 수를 앞자리부터 읽으며 long형 변수 ret에 채워나감
		return ((int)(ret * minus)); // 수의 정보를 담은 ret과 minus를 곱해 반환
	}

	float   atof(const char* str)
	{
		int		minus;
		float	ret;
		float	dem;
		int		e_num;

		minus = 1;
		ret = 0;
		dem = 1;
		e_num = 0;
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				minus *= -1;
			str++;
		}
		while (*str >= '0' && *str <= '9')
		{
			ret *= 10;
			ret += *str - '0';
			str++;
		}
		if (*str == '.') // 소수부를 받는 구간
		{
			str++;
			while (*str >= '0' && *str <= '9')
			{
				dem *= 0.1;
				ret += dem * (float)(*str - '0');
				str++;
			} // 소수점 뒤의 자리는 각 자리에 0.1을 계속 곱해 ret에 더함
			dem = 1;
			if ((*str == 'e' || *str == 'E')) // 부동소수점 부분
			{
				str++;
				if (*str == '-') // 부동소수점 10^-n부분
				{
					str++;
					while (*str >= '0' && *str <= '9')
					{
						e_num *= 10;
						e_num += *str - '0';
						str++;
					}
					for (int i = 0; i < e_num; i++)
						dem *= 0.1;
				}
				else // 부동소수점 10^n 부분
				{
					if (*str == '+')
						str++;
					while (*str >= '0' && *str <= '9')
					{
						e_num *= 10;
						e_num += *str - '0';
						str++;
					}
					for (int i = 0; i < e_num; i++)
						dem *= 10;
				}
			}
		}
		return ((float)minus * ret * dem);
	}
}