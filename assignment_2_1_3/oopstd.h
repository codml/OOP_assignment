namespace oopstd {
	// stdó�� namespace�� ������
	void* memset(void* ptr, int value, size_t num)
	{
		size_t	i;

		i = 0;
		while (i < num)
		{
			((unsigned char*)ptr)[i] = (unsigned char)value;
			// �Է¹��� ���ڸ� unsigned char�� ĳ������ �޸� ������ ����
			// ����Ʈ ������ ����!
			i++;
		}
		return (ptr);
	}

	void* memcpy(void* destination, const void* source, size_t num)
	{
		size_t	i;

		if (destination == source)
			return (0); // ���� �ּҰ� ������ �� ��ȯ
		i = 0;
		while (i < num)
		{
			((unsigned char*)destination)[i] = ((const unsigned char*)source)[i];
			// ����Ʈ ������ ����
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
			// ���� ������ ���� �ٸ��� �� ���̸� ��ȯ
			// �� ���ڿ� �� �ϳ��� ���� ������ ��
			// �� ���ڸ� unsigned char�� ĳ������ �� ���̸� ��ȯ�ؾ� ��
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
		// �� ���ڿ� �� �ϳ��� �����ų� num �ڸ����� ��
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
		destination[i] = 0; // ���� �� �ٿ� ���ڿ� �ϼ�
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
		} // source�� ���̰� num���� ������
		// ���� ������ null�� ä��� -> �Ŵ��� �ִ� ����
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
			str++; // whitespace�� �޴� ����
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				minus *= -1;
			str++;
		} // ��ȣ�� ó���ϴ� ����
		while (*str && (*str >= '0' && *str <= '9'))
		{
			ret *= 10;
			ret += *str - '0';
			str++;
		} // ���� ���ڸ����� ������ long�� ���� ret�� ä������
		return ((int)(ret * minus)); // ���� ������ ���� ret�� minus�� ���� ��ȯ
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
		if (*str == '.') // �Ҽ��θ� �޴� ����
		{
			str++;
			while (*str >= '0' && *str <= '9')
			{
				dem *= 0.1;
				ret += dem * (float)(*str - '0');
				str++;
			} // �Ҽ��� ���� �ڸ��� �� �ڸ��� 0.1�� ��� ���� ret�� ����
			dem = 1;
			if ((*str == 'e' || *str == 'E')) // �ε��Ҽ��� �κ�
			{
				str++;
				if (*str == '-') // �ε��Ҽ��� 10^-n�κ�
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
				else // �ε��Ҽ��� 10^n �κ�
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