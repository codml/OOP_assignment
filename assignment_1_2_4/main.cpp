#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

#define IMG_HEIGHT 512
#define IMG_WIDTH 512

typedef struct
{
	int	x;
	int	y;
}pos; // �̹����� �ڸ��� ���� ��ǥ

unsigned char** make_memory(unsigned int height, unsigned int width); // �̹��� �޸� �Ҵ�
void free_memory(unsigned char** pp_mem); // �޸� ����
char* insert_str(const char* str, const char* tmp); // ���� ������ ����
int	return_digit(unsigned int width);
char* insert_size(unsigned int width, unsigned int height); // cropped image�� ���� ����
void swap_plus(pos* ptr);
int is_possible(int x1, int y1, int x2, int y2); // ��ǥ�� 2���� ������ �����ϸ鼭 ���簢���� �������
int	make_cropped(unsigned char** input_buf, unsigned char** output_buf,
	unsigned int height, unsigned int width, char *input_name); // cropped image ����
int	make_horizon(unsigned char** input_buf, unsigned char** output_buf,
	unsigned int height, unsigned int width, char* input_name); // horizontal flip
int	make_vertical(unsigned char** input_buf, unsigned char** output_buf,
	unsigned int height, unsigned int width, char* input_name); // vertical flip

int main()
{
	FILE* fp_input = 0;
	unsigned char** input_buf = 0;
	unsigned char** output_buf = 0;
	char	input_name[100];

	cout << "Input file name: ";
	cin >> input_name;
	fp_input = fopen(input_name, "rb");
	if (!fp_input)
		return (0);
	input_buf = make_memory(IMG_HEIGHT, IMG_WIDTH); // image�� ���� �޸� �Ҵ�
	if (!input_buf)
	{
		fclose(fp_input);
		return (0);
	}
	for (unsigned int i = 0; i < IMG_HEIGHT; i++)
		fread(input_buf[i], sizeof(unsigned char), IMG_WIDTH, fp_input); // �޸� ������ image �б�
	fclose(fp_input);
	if (!make_cropped(input_buf, output_buf, IMG_HEIGHT, IMG_WIDTH, input_name))
	{
		// make_cropped �Լ��� �����ϸ� 1 ��ȯ, �����ϸ� ���ο��� �Ҵ��� �޸𸮸�
		// ���� �����ϰ� 0 ��ȯ
		free_memory(input_buf);
		return (0);
	}
	output_buf = make_memory(IMG_HEIGHT, IMG_WIDTH);
	if (!output_buf)
	{
		// horizontal flip, vertical flip�� �Ѵ� IMG_HEIGHT X IMG_WIDTH�� ������
		// ���� �޸� ������ �ᵵ ����
		free_memory(input_buf);
		return (0);
	}
	if (!make_horizon(input_buf, output_buf, IMG_HEIGHT, IMG_WIDTH, input_name))
	{
		// make_horizon�� make_croppedó�� �����ϸ� 1 ��ȯ, �����ϸ� �޸� ���� �� 0 ��ȯ
		free_memory(input_buf);
		free_memory(output_buf);
		return (0);
	}
	if (!make_vertical(input_buf, output_buf, IMG_HEIGHT, IMG_WIDTH, input_name))
	{
		free_memory(input_buf);
		free_memory(output_buf);
		return (0);
	}
	free_memory(input_buf);
	free_memory(output_buf);
	cout << "Output images are stored!" << endl;
	return (0);
}

unsigned char** make_memory(unsigned int height, unsigned int width)
{
	unsigned char** pp_mem = new unsigned char* [height];
	if (!pp_mem)
		return (0);
	pp_mem[0] = new unsigned char[height * width];
	if (!pp_mem[0])
	{
		delete[] pp_mem;
		return (0);
	}
	for (unsigned int i = 1; i < height; i++)
		pp_mem[i] = pp_mem[i - 1] + width;
	return pp_mem;
}

void free_memory(unsigned char **pp_mem)
{
	if (pp_mem)
	{
		delete[] pp_mem[0];
		delete[] pp_mem;
	}
}

char* insert_str(const char* str, const char* tmp)
{
	int	i, j;
	char* ptr = new char [strlen(str) + strlen(tmp)];

	for (i = 0; str[i] != '.'; i++)
		ptr[i] = str[i];
	// ���� ������ �̸��� '.'�� ��ġ�� ã�� �� ��ġ�� �߰� ���ڿ��� ������
	// '.'�� ��ġ�� ã�� ������ Ȯ���ڸ�(.raw)�� �����ϱ� ����
	// ���� �̸��� Ȯ���ڸ� �̿��� �ڸ��� '.'�� ���� �� ������,
	// ���ʿ� ���� �� �������� ���� �� '.'�� ���ԵǴ� ���� ������
	for (j = 0; tmp[j]; j++)
		ptr[j + i] = tmp[j];
	ptr[j + i] = 0;
	return (ptr);
}

int	return_digit(unsigned int width)
{
	int	i;

	for (i = 0; width; i++)
		width /= 10;
	return (i);
}

char* insert_size(unsigned int width, unsigned int height)
{
	char* ptr = new char[100];
	int	w_digit;
	int	h_digit;

	w_digit = return_digit(width);
	h_digit = return_digit(height);
	strcpy(ptr, "_cropped_");
	for (int i = w_digit + 8; i >= 9; i--)
	{
		ptr[i] = width % 10 + '0';
		width /= 10;
	} // ������� �ϸ� width = 256�϶�, ptr = "_cropped_256"
	ptr[9 + w_digit] = 'x';
	for (int i = h_digit + w_digit + 9; i >= w_digit + 10; i--)
	{
		ptr[i] = height % 10 + '0';
		height /= 10;
	} // ������� �ϸ� width = 256, height = 192�϶�, ptr = "_cropped_256x192"
	ptr[w_digit + h_digit + 10] = '.';
	ptr[w_digit + h_digit + 11] = 'r';
	ptr[w_digit + h_digit + 12] = 'a';
	ptr[w_digit + h_digit + 13] = 'w';
	ptr[w_digit + h_digit + 14] = 0; // �ڿ� ".raw"Ȯ���ڸ� ����
	return ptr;
}

void swap_plus(pos* ptr)
{
	int	tmp; // ���� ���������� ��� swap ���

	if (ptr->x > (ptr + 1)->x)
	{
		tmp = ptr->x;
		ptr->x = (ptr + 1)->x;
		(ptr + 1)->x = tmp;
	}
	if (ptr->y > (ptr + 1)->y)
	{
		tmp = ptr->y;
		ptr->y = (ptr + 1)->y;
		(ptr + 1)->y = tmp;
	}
}

int is_possible(int x1, int y1, int x2, int y2)
{
	if (x1 == x2 || y1 == y2 || x1 < 0 || x1 > IMG_WIDTH - 1
		|| x2 < 0 || x2 > IMG_WIDTH - 1 || y1 < 0 || y1 > IMG_HEIGHT - 1
		|| y2 < 0 || y2 > IMG_HEIGHT - 1)
		return (0); // ���簢���� ���� �� ���ų�, index�� ������ ���̸� �Ѿ���� �˻�
	else
		return (1);
}

int	make_cropped(unsigned char** input_buf, unsigned char** output_buf,
	unsigned int height, unsigned int width, char* input_name)
{
	FILE* fp_output;
	char str_pos[2][10]; // crop�� 2���� ��ǥ�� ���ڿ��� ����
	pos	cut_pos[2]; // crop�� 2���� ��ǥ
	char* size_name; // crop�� ����� ���ڿ��� �ٲ� �̸� ������ �̸� ÷�� �����
	char* output_name;
	unsigned int len_x;
	unsigned int len_y;

	cout << "1st coordinate : ";
	cin >> str_pos[0] >> str_pos[1]; // ��ǥ���� �Է¹��� ��, �޸��� ������ �־�� �Ѵ�!
	cut_pos[0].x = atoi(str_pos[0]); // x�ڿ� �޸��� �͵�, atoi�� ���� �ڿ� ���ڸ� ����
	cut_pos[0].y = atoi(str_pos[1]);
	cout << "2nd coordinate : ";
	cin >> str_pos[0] >> str_pos[1];
	cut_pos[1].x = atoi(str_pos[0]);
	cut_pos[1].y = atoi(str_pos[1]);
	if (!is_possible(cut_pos[0].x, cut_pos[0].y, cut_pos[1].x, cut_pos[1].y)) // ��ǥ�� ��ȿ�� �˻�
		return (0);
	swap_plus(cut_pos); // cut_pos[0].x < cut_pos[1].y�� ����� ����(y�� ��������)
	len_x = cut_pos[1].x - cut_pos[0].x + 1;
	len_y = cut_pos[1].y - cut_pos[0].y + 1;
	size_name = insert_size(len_x, len_y);
	output_name = insert_str(input_name, size_name);
	fp_output = fopen(output_name, "wb");
	if (!fp_output)
	{
		delete[] size_name;
		delete[] output_name;
		return (0);
	}
	output_buf = make_memory(len_y, len_x);
	if (!output_buf)
	{
		fclose(fp_output);
		delete[] size_name;
		delete[] output_name;
		return 0;
	}
	for (unsigned int i = 0; i < len_y; i++)
	{
		for (unsigned int j = 0; j < len_x; j++)
			output_buf[i][j] = input_buf[i + cut_pos[0].y][j + cut_pos[0].x];
	} // ���� �̹����� �κ��� output_buf�� ����
	for (unsigned int i = 0; i < len_y; i++)
		fwrite(output_buf[i], sizeof(unsigned char), len_x, fp_output);
	fclose(fp_output);
	free_memory(output_buf);
	delete[] size_name;
	delete[] output_name;
	return (1);
}

int	make_horizon(unsigned char** input_buf, unsigned char** output_buf,
	unsigned int height, unsigned int width, char* input_name)
{
	FILE* fp_output;
	char* output_name;

	output_name = insert_str(input_name, "_horizontalflip.raw"); // ���ο� ���� �̸� ����
	fp_output = fopen(output_name, "wb"); // ��� ���� ��Ʈ�� ����
	if (!fp_output)
	{
		delete[] output_name;
		return (0);
	}
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
			output_buf[i][j] = input_buf[i][width - j - 1]; // �¿� ������ ����
	}
	for (unsigned int i = 0; i < IMG_HEIGHT; i++)
		fwrite(output_buf[i], sizeof(unsigned char), IMG_WIDTH, fp_output);
	fclose(fp_output);
	delete[] output_name;
	return (1);
}

int	make_vertical(unsigned char** input_buf, unsigned char** output_buf,
	unsigned int height, unsigned int width, char* input_name)
{
	FILE* fp_output;
	char* output_name;

	output_name = insert_str(input_name, "_verticalflip.raw");
	fp_output = fopen(output_name, "wb");
	if (!fp_output)
	{
		delete[] output_name;
		return (0);
	}
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
			output_buf[i][j] = input_buf[height - i - 1][j]; // ���Ʒ� ����
	}
	for (unsigned int i = 0; i < IMG_HEIGHT; i++)
		fwrite(output_buf[i], sizeof(unsigned char), IMG_WIDTH, fp_output);
	fclose(fp_output);
	delete[] output_name;
	return (1);
}