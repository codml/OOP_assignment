#include <iostream>
#include <cstring>

using namespace std;

int path_cnt = 0; // ��θ� �̵��ϸ� �ִ� ��θ� ī�����ϴ� ����
int flag = 0; // �������� ���������� �˷��ִ� ����

char** set_map(int row, int col)
{
	char* ptr;
	char** pptr;

	ptr = new char[row * (col + 1)]; // ���� �� ���� ���� ���ڿ�;
	if (!ptr)
		return (0);
	pptr = new char* [row + 1]; // ���� ����Ű�� ���� ������
	if (!pptr)
	{
		delete[]ptr;
		return (0);
	}
	pptr[0] = ptr;
	for (int i = 1; i < row; i++)
		pptr[i] = pptr[i - 1] + col + 1; // ������ ��� ���� �ѹ��� �Ҵ�������
											// �� ���� ���� �����Ϳ� ���� �־���
	pptr[row] = 0;
	for (int i = 0; i < row; i++)
		cin >> pptr[i];
	return (pptr);
}

int* make_dfs_tree(int row, int col)
{
	int* dfs_tree;

	dfs_tree = new int[row * col];
	if (!dfs_tree)
		return (0);
	memset(dfs_tree, 0, sizeof(int) * row * col);
	// dfs�� ���� tree�� �迭�� ����!
	// map[i][j]�� �湮�ߴ� ���� dfs_tree[i * col + j]���� Ȯ��!
	return (dfs_tree);
}


int	check_movable(char** pptr, size_t x, size_t y, int* dfs_tree)
{
	// x�� y�� ���� ��迡 �ְų�(x == 0 or row - 1, y == 0 or col - 1)
	// �����̰��� �ϴ� ��ġ�� ��(1)�̰ų�
	// �����̰��� �ϴ� ��ġ�� �湮�ߴٸ�
	// ������ �� ���� ����!
	if ((x == 0 || pptr[x - 1][y] == '1'
		|| dfs_tree[(x - 1) * strlen(pptr[0]) + y] == 1)
		&& (y == 0 || pptr[x][y - 1] == '1'
			|| dfs_tree[x * strlen(pptr[0]) + y - 1] == 1)
		&& (pptr[x + 1] == 0 || pptr[x + 1][y] == '1'
			|| dfs_tree[(x + 1) * strlen(pptr[0]) + y] == 1)
		&& (pptr[x][y + 1] == 0 || pptr[x][y + 1] == '1'
			|| dfs_tree[x * strlen(pptr[0]) + y + 1] == 1))
		return (0);
	else
		return (1);
}

void	dfs_map(char** pptr, size_t x, size_t y, int dest[], int* dfs_tree)
{
	dfs_tree[x * strlen(pptr[0]) + y] = 1; // �ش� ��ġ�� �湮��
	path_cnt++; // ��ĭ ���������Ƿ� ī��Ʈ
	if (x == dest[0] - 1 && y == dest[1] - 1) // �������� �����ߴٸ� ����!
	{
		flag = 1;
		return;
	}
	if (check_movable(pptr, x, y, dfs_tree))
	{
		// ���� �������� �������� �ʾҰ�(flag == 0)
		// �� �� �������ζ� �̵��� �� ������
		// �̵�!
		if (!flag && x && pptr[x - 1][y] != '1'
			&& dfs_tree[(x - 1) * strlen(pptr[0]) + y] != 1)
			dfs_map(pptr, x - 1, y, dest, dfs_tree);
		if (!flag && y && pptr[x][y - 1] != '1'
			&& dfs_tree[x * strlen(pptr[0]) + y - 1] != 1)
			dfs_map(pptr, x, y - 1, dest, dfs_tree);
		if (!flag && pptr[x + 1] && pptr[x + 1][y] != '1'
			&& dfs_tree[(x + 1) * strlen(pptr[0]) + y] != 1)
			dfs_map(pptr, x + 1, y, dest, dfs_tree);
		if (!flag && pptr[x][y + 1] && pptr[x][y + 1] != '1'
			&& dfs_tree[x * strlen(pptr[0]) + y + 1] != 1)
			dfs_map(pptr, x, y + 1, dest, dfs_tree);
	}
	// �������� �ʾҴٸ� ����� �� ���� ī��Ʈ���� �����ϱ� ������
	if (!flag)
	{
		dfs_tree[x * strlen(pptr[0]) + y] = 0;
		path_cnt--;
	}
}

int main()
{
	int row, col;
	char** pptr;
	int* dfs_tree;
	int start[2];
	int dest[2];

	cin >> row >> col;
	pptr = set_map(row, col);
	if (!pptr)
	{
		cout << "map allocation failed" << endl;
		return (0);
	}
	cin >> start[1] >> start[0] >> dest[1] >> dest[0]; // ������, ���� �Է�(��, �� �ݴ� ����!)
	dfs_tree = make_dfs_tree(row, col);
	if (!dfs_tree)
	{
		delete[] pptr[0];
		delete[] pptr;
		cout << "map allocation failed" << endl;
		return (0);
	}
	dfs_map(pptr, start[0] - 1, start[1] - 1, dest, dfs_tree);
	cout << path_cnt << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			cout << dfs_tree[i * row + j];
		cout << endl;
	}
	delete[] pptr[0];
	delete[] pptr;
	delete[] dfs_tree;
	return (0);
}