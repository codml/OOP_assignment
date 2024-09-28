#include <iostream>
#include <cstring>

using namespace std;

int path_cnt = 0; // 경로를 이동하며 최단 경로를 카운팅하는 변수
int flag = 0; // 목적지에 도착했음을 알려주는 변수

char** set_map(int row, int col)
{
	char* ptr;
	char** pptr;

	ptr = new char[row * (col + 1)]; // 맵의 각 행을 이은 문자열;
	if (!ptr)
		return (0);
	pptr = new char* [row + 1]; // 맵을 가리키는 이중 포인터
	if (!pptr)
	{
		delete[]ptr;
		return (0);
	}
	pptr[0] = ptr;
	for (int i = 1; i < row; i++)
		pptr[i] = pptr[i - 1] + col + 1; // 위에서 모든 행을 한번에 할당했으니
											// 각 행을 이중 포인터에 각각 넣어줌
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
	// dfs를 위한 tree를 배열로 생성!
	// map[i][j]를 방문했는 지를 dfs_tree[i * col + j]에서 확인!
	return (dfs_tree);
}


int	check_movable(char** pptr, size_t x, size_t y, int* dfs_tree)
{
	// x나 y가 맵의 경계에 있거나(x == 0 or row - 1, y == 0 or col - 1)
	// 움직이고자 하는 위치가 벽(1)이거나
	// 움직이고자 하는 위치를 방문했다면
	// 움직일 수 없는 상태!
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
	dfs_tree[x * strlen(pptr[0]) + y] = 1; // 해당 위치를 방문함
	path_cnt++; // 한칸 움직였으므로 카운트
	if (x == dest[0] - 1 && y == dest[1] - 1) // 목적지에 도착했다면 종료!
	{
		flag = 1;
		return;
	}
	if (check_movable(pptr, x, y, dfs_tree))
	{
		// 아직 목적지에 도착하지 않았고(flag == 0)
		// 한 쪽 방향으로라도 이동할 수 있으면
		// 이동!
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
	// 도착하지 않았다면 샛길로 샌 경우는 카운트에서 빼야하기 때문에
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
	cin >> start[1] >> start[0] >> dest[1] >> dest[0]; // 시작점, 종점 입력(행, 열 반대 주의!)
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