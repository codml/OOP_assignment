#include <iostream>

using namespace std;

void bubble_sort(int arr[], int size);
void insertion_sort(int arr[], int size);
void merge(int arr[], int left, int right);
void merge_sort(int arr[], int size);
void quick(int arr[], int left, int right);
void quick_sort(int arr[], int size);

int cal_cnt = 0; // �� ���� Ƚ���� ���
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
	cin >> choice; // ���� ����� ����
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
			cal_cnt++; // ���� for���� ���� �񱳿��� �� ������ ���� Ƚ�� üũ
			if (arr[j] > arr[j + 1])
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
			// ������ ��Ҹ� ���ϸ� �����ĵ� �κ��� ���� ū ����
			// �����ĵ� �κ� �� ���� ���������� ������ �ȴ�.
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
		tmp = arr[i]; // ������ �� �̸� ����
		for (int j = i - 1; j >= 0; j--)
		{
			cal_cnt++;
			if (arr[j] > tmp) // ������ ������ ���� ���� ũ��
			{
				arr[j + 1] = arr[j]; // ���� �� ��ĭ �̷��
				if (!j)
				{
					arr[j] = tmp; // ���̻� ���� ���� ������ �� �տ� �� ����
					cal_cnt++;
				}
			}
			else
			{
				arr[j + 1] = tmp; // ������ ������ ���� ���� ������ ����
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

	if (left + 1 == right) // ���������� Ż������ 1: �������� ��Ұ� 2���� ��
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
	else if (left == right) // ���������� Ż������ 2: �������� ��Ұ� 1���� ��
	{
		cal_cnt++;
		return;
	}
	merge(arr, left, (left + right) / 2); // �ɰ��� ���� ����
	merge(arr, (left + right) / 2 + 1, right); // �ɰ��� ������ ����
	ptr = new int[right - left + 1]; // ���ĵ� �� �κ��� �����ϱ� ���� �迭 ����
	for (int i = left; i < right + 1; i++)
		ptr[i - left] = arr[i];
	l_idx = 0;
	r_idx = (right - left) / 2 + 1;
	for (int i = left; i < right + 1; i++)
	{
		// ���ĵ� ���� �κа� ������ �κ��� ���ϸ� �� ���� ���� ���� �迭�� ����
		cal_cnt++;
		if (ptr[l_idx] < ptr[r_idx])
		{
			if (l_idx == (right - left) / 2 + 1) // ���� �κ��� �� ��������
				arr[i] = ptr[r_idx++]; // ������ �� �۾Ƶ� ������ ����
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
	merge(arr, 0, size - 1); // ��ü �������� �������� ����
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
		return; // ����Ʈ�� ��������: left�� right�� ��ġ�ų� ������
	while (i <= j)
	{
		// i�� ���ʺ���, j�� �����ʺ��� ����
		// i�� pivot���� ���� �κ�, j�� ū �κ��̾�� �Ѵ�
		cal_cnt++;
		if (arr[i] > pivot && arr[j] < pivot) // �Ѵ� ��߳��� swap
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		if (arr[i] <= pivot) // i�� �����̸� ��ĭ �ű��
			i++;
		if (arr[j] >= pivot)
			j--;
	}
	tmp = arr[j];
	arr[j] = arr[left];
	arr[left] = tmp; // pivot�� j(���� �κ��� ���� ������)�� ��ȯ
	quick(arr, left, j - 1); // pivot �������� ����
	quick(arr, j + 1, right); // ������
}

void quick_sort(int arr[], int size)
{
	quick(arr, 0, size - 1); // ��ü �κп��� ����Ʈ ����
	cout << "Sorted order: ";
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl << "Median number: " << arr[size / 2] << endl;
}