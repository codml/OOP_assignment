#include <iostream>

using namespace std;

void bubble_sort(int arr[], int size);
void insertion_sort(int arr[], int size);
void merge(int arr[], int left, int right);
void merge_sort(int arr[], int size);
void quick(int arr[], int left, int right);
void quick_sort(int arr[], int size);

int cal_cnt = 0; // 비교 연산 횟수를 기록
int main()
{
	int size, choice;
	int* arr;

	cout << "Input size: ";
	cin >> size;
	arr = new int[size];
	if (!arr)
		return (0);
	for (int i = 0; i < size; i++)
		cin >> arr[i];
	cout << "Select sort(1: bubble sort, 2: insertion sort, 3: merge sort, 4: quick sort): ";
	cin >> choice; // 정렬 방법을 선택
	switch (choice)
	{
	case 1:
		bubble_sort(arr, size);
		break;
	case 2:
		insertion_sort(arr, size);
		break;
	case 3:
		merge_sort(arr, size);
		break;
	case 4:
		quick_sort(arr, size);
		break;
	default:
		break;
	}
	cout << "Calculation count: " << cal_cnt << endl;
	delete[]arr;
	return (0);
}

void bubble_sort(int arr[], int size)
{
	int tmp;

	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			cal_cnt++; // 이중 for문을 돌며 비교연산 할 때마다 연산 횟수 체크
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			// 인접한 요소를 비교하며 비정렬된 부분중 가장 큰 값을
			// 비정렬된 부분 중 가장 오른쪽으로 보내게 된다.
		}
	}
	cout << "Sorted order: ";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl << "Median number: " << arr[size / 2] << endl;
}

void insertion_sort(int arr[], int size)
{
	int tmp;

	for (int i = 1; i < size; i++)
	{
		tmp = arr[i]; // 삽입할 값 미리 저장
		for (int j = i - 1; j >= 0; j--)
		{
			cal_cnt++;
			if (arr[j] > tmp) // 삽입할 값보다 현재 값이 크면
			{
				arr[j + 1] = arr[j]; // 현재 값 한칸 미루기
				if (!j)
				{
					arr[j] = tmp; // 더이상 비교할 값이 없으면 맨 앞에 값 삽입
					cal_cnt++;
				}
			}
			else
			{
				arr[j + 1] = tmp; // 삽입할 값보다 현재 값이 작으면 삽입
				break;
			}
		}
	}
	cout << "Sorted order: ";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl << "Median number: " << arr[size / 2] << endl;
}

void merge(int arr[], int left, int right)
{
	int tmp, l_idx, r_idx;
	int* ptr;

	if (left + 1 == right) // 병합정렬의 탈출조건 1: 나눠지는 요소가 2개일 때
	{
		cal_cnt++;
		if (arr[left] > arr[right])
		{
			tmp = arr[left];
			arr[left] = arr[right];
			arr[right] = tmp;
		}
		return;
	}
	else if (left == right) // 병합정렬의 탈출조건 2: 나눠지는 요소가 1개일 때
	{
		cal_cnt++;
		return;
	}
	merge(arr, left, (left + right) / 2); // 쪼개진 왼쪽 절반
	merge(arr, (left + right) / 2 + 1, right); // 쪼개진 오른쪽 절반
	ptr = new int[right - left + 1]; // 정렬된 두 부분을 정렬하기 위한 배열 생성
	for (int i = left; i < right + 1; i++)
		ptr[i - left] = arr[i];
	l_idx = 0;
	r_idx = (right - left) / 2 + 1;
	for (int i = left; i < right + 1; i++)
	{
		// 정렬된 왼쪽 부분과 오른쪽 부분을 비교하며 더 작은 수를 기존 배열에 삽입
		cal_cnt++;
		if (ptr[l_idx] < ptr[r_idx])
		{
			if (l_idx == (right - left) / 2 + 1) // 왼쪽 부분이 다 끝났으면
				arr[i] = ptr[r_idx++]; // 왼쪽이 더 작아도 오른쪽 삽입
			else
				arr[i] = ptr[l_idx++];
		}
		else
		{
			if (r_idx == right - left + 1)
				arr[i] = ptr[l_idx++];
			else
				arr[i] = ptr[r_idx++];
		}
	}
	delete[]ptr;
}

void merge_sort(int arr[], int size)
{
	merge(arr, 0, size - 1); // 전체 범위에서 병합정렬 시작
	cout << "Sorted order: ";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl << "Median number: " << arr[size / 2] << endl;
}

void quick(int arr[], int left, int right)
{
	int i = left + 1;
	int j = right;
	int tmp;
	int pivot = arr[left];

	if (left >= right)
		return; // 퀵소트의 종료조건: left와 right가 겹치거나 엇갈림
	while (i <= j)
	{
		// i는 왼쪽부터, j는 오른쪽부터 시작
		// i는 pivot보다 작은 부분, j는 큰 부분이어야 한다
		cal_cnt++;
		if (arr[i] > pivot && arr[j] < pivot) // 둘다 어긋나면 swap
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		if (arr[i] <= pivot) // i가 정상이면 한칸 옮기기
			i++;
		if (arr[j] >= pivot)
			j--;
	}
	tmp = arr[j];
	arr[j] = arr[left];
	arr[left] = tmp; // pivot과 j(작은 부분의 가장 오른쪽)을 교환
	quick(arr, left, j - 1); // pivot 기준으로 왼쪽
	quick(arr, j + 1, right); // 오른쪽
}

void quick_sort(int arr[], int size)
{
	quick(arr, 0, size - 1); // 전체 부분에서 퀵소트 시작
	cout << "Sorted order: ";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl << "Median number: " << arr[size / 2] << endl;
}