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
}pos; // 이미지를 자르기 위한 좌표

unsigned char** make_memory(unsigned int height, unsigned int width); // 이미지 메모리 할당
void free_memory(unsigned char** pp_mem); // 메모리 해제
char* insert_str(const char* str, const char* tmp); // 사진 제목을 생성
int	return_digit(unsigned int width);
char* insert_size(unsigned int width, unsigned int height); // cropped image의 제목 생성
void swap_plus(pos* ptr);
int is_possible(int x1, int y1, int x2, int y2); // 좌표값 2개가 범위를 만족하면서 직사각형을 만드는지
int	make_cropped(unsigned char** input_buf, unsigned char** output_buf,
	unsigned int height, unsigned int width, char *input_name); // cropped image 생성
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
	input_buf = make_memory(IMG_HEIGHT, IMG_WIDTH); // image를 읽을 메모리 할당
	if (!input_buf)
	{
		fclose(fp_input);
		return (0);
	}
	for (unsigned int i = 0; i < IMG_HEIGHT; i++)
		fread(input_buf[i], sizeof(unsigned char), IMG_WIDTH, fp_input); // 메모리 공간에 image 읽기
	fclose(fp_input);
	if (!make_cropped(input_buf, output_buf, IMG_HEIGHT, IMG_WIDTH, input_name))
	{
		// make_cropped 함수는 성공하면 1 반환, 실패하면 내부에서 할당한 메모리를
		// 전부 해제하고 0 반환
		free_memory(input_buf);
		return (0);
	}
	output_buf = make_memory(IMG_HEIGHT, IMG_WIDTH);
	if (!output_buf)
	{
		// horizontal flip, vertical flip은 둘다 IMG_HEIGHT X IMG_WIDTH의 사이즈
		// 같은 메모리 공간을 써도 무방
		free_memory(input_buf);
		return (0);
	}
	if (!make_horizon(input_buf, output_buf, IMG_HEIGHT, IMG_WIDTH, input_name))
	{
		// make_horizon도 make_cropped처럼 성공하면 1 반환, 실패하면 메모리 해제 후 0 반환
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
	// 원본 파일의 이름에 '.'의 위치를 찾아 그 위치에 추가 문자열을 삽입함
	// '.'의 위치를 찾은 이유는 확장자명(.raw)만 제거하기 위함
	// 파일 이름에 확장자명 이외의 자리에 '.'이 있을 수 있지만,
	// 애초에 파일 및 폴더명을 만들 때 '.'이 포함되는 것을 지양함
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
	} // 여기까지 하면 width = 256일때, ptr = "_cropped_256"
	ptr[9 + w_digit] = 'x';
	for (int i = h_digit + w_digit + 9; i >= w_digit + 10; i--)
	{
		ptr[i] = height % 10 + '0';
		height /= 10;
	} // 여기까지 하면 width = 256, height = 192일때, ptr = "_cropped_256x192"
	ptr[w_digit + h_digit + 10] = '.';
	ptr[w_digit + h_digit + 11] = 'r';
	ptr[w_digit + h_digit + 12] = 'a';
	ptr[w_digit + h_digit + 13] = 'w';
	ptr[w_digit + h_digit + 14] = 0; // 뒤에 ".raw"확장자명 붙임
	return ptr;
}

void swap_plus(pos* ptr)
{
	int	tmp; // 이전 문제에서도 썼던 swap 사용

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
		return (0); // 직사각형을 만들 수 없거나, index가 사진의 길이를 넘어가는지 검사
	else
		return (1);
}

int	make_cropped(unsigned char** input_buf, unsigned char** output_buf,
	unsigned int height, unsigned int width, char* input_name)
{
	FILE* fp_output;
	char str_pos[2][10]; // crop할 2개의 좌표를 문자열로 받음
	pos	cut_pos[2]; // crop할 2개의 좌표
	char* size_name; // crop할 사이즈를 문자열로 바꿔 이를 포함한 이름 첨자 만들기
	char* output_name;
	unsigned int len_x;
	unsigned int len_y;

	cout << "1st coordinate : ";
	cin >> str_pos[0] >> str_pos[1]; // 좌표값을 입력받을 때, 콤마와 공백이 있어야 한다!
	cut_pos[0].x = atoi(str_pos[0]); // x뒤에 콤마가 와도, atoi는 숫자 뒤에 문자를 버림
	cut_pos[0].y = atoi(str_pos[1]);
	cout << "2nd coordinate : ";
	cin >> str_pos[0] >> str_pos[1];
	cut_pos[1].x = atoi(str_pos[0]);
	cut_pos[1].y = atoi(str_pos[1]);
	if (!is_possible(cut_pos[0].x, cut_pos[0].y, cut_pos[1].x, cut_pos[1].y)) // 좌표의 유효성 검사
		return (0);
	swap_plus(cut_pos); // cut_pos[0].x < cut_pos[1].y를 만들기 위함(y도 마찬가지)
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
	} // 원본 이미지의 부분을 output_buf에 저장
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

	output_name = insert_str(input_name, "_horizontalflip.raw"); // 새로운 파일 이름 생성
	fp_output = fopen(output_name, "wb"); // 결과 파일 스트림 생성
	if (!fp_output)
	{
		delete[] output_name;
		return (0);
	}
	for (unsigned int i = 0; i < height; i++)
	{
		for (unsigned int j = 0; j < width; j++)
			output_buf[i][j] = input_buf[i][width - j - 1]; // 좌우 반전해 저장
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
			output_buf[i][j] = input_buf[height - i - 1][j]; // 위아래 반전
	}
	for (unsigned int i = 0; i < IMG_HEIGHT; i++)
		fwrite(output_buf[i], sizeof(unsigned char), IMG_WIDTH, fp_output);
	fclose(fp_output);
	delete[] output_name;
	return (1);
}