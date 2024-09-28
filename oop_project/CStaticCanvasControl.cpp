// CStaticCanvasControl.cpp: 구현 파일
//

#include "pch.h"
#include "oop_project.h"
#include "CStaticCanvasControl.h"

Data::Data()
{
	Isvisit = false;
	side = 15;
	row = 0;
	col = 0;
	par = 0; // 멤버 변수 초기화
}

bool Data::Isvisited()
{
	return Isvisit;
}

void Data::setVisit(bool n)
{
	Isvisit = n;
}

void Data::setRow(int n)
{
	row = n;
}

int Data::getRow()
{
	return row;
}

void Data::setCol(int n)
{
	col = n;
}

int Data::getCol()
{
	return col;
}

void Data::setPar(Data* data)
{
	par = data;
}

Data* Data::getPar()
{
	return par;
}

void Data::setSide()
{
	side = 15; // 1번째 비트를 왼쪽 벽, 2번째 비트를 오른쪽 벽, 3번째 비트를 위쪽 벽, 4번째 비트를 아래 벽이라 생각
	// 2^0 + 2^1 + 2^2 + 2^3 = 15, 즉 모든 방향으로 벽이 막혀있으면 side = 15
}

char Data::getSide()
{
	return side;
}

void Data::deleteLeft()
{
	if ((side & 1) == 1) // 왼쪽 벽이 있다면 1번째 비트에 1이 있고, 이를 1과 & 연산 하면 1만 남게 됨 
		side--; // 왼쪽 벽 제거 == 1 빼기
}

void Data::deleteRight()
{
	if ((side & 2) == 2) // 오른쪽 벽이 있다면 2번째 비트에 1이 있고, 이를 2과 & 연산 하면 2만 남게 됨 
		side -= 2; // 오른쪽 벽 제거 == 2 빼기
}

void Data::deleteUp()
{
	if ((side & 4) == 4) // 위와 같은 방식
		side -= 4;
}

void Data::deleteDown()
{
	if ((side & 8) == 8) // 위와 같은 방식
		side -= 8;
}

MyStack::MyStack()
{
	memset(arr, 0, sizeof(Data*) * LEN); // 스택 초기화
	idx = -1;
}

void MyStack::Push(Data* data)
{
	if (idx == LEN - 1) // 그럴 일은 없지만, 스택이 꽉 찼다면 그냥 종료
		return;
	arr[++idx] = data; // 인덱스를 늘리고 그 위치에 데이터 삽입
}

Data* MyStack::Pop()
{
	if (Isempty()) // 스택이 비어있으면 그냥 종료
		return 0;
	return arr[idx--]; // 가장 위 데이터를 반환하고 인덱스 감소
}

bool MyStack::Isempty()
{
	if (idx == -1)
		return true;
	return false;
}

MyQueue::MyQueue()
{
	memset(arr, 0, sizeof(Data*) * (LEN + 1));
	front = 0;
	rear = 0;
}

void MyQueue::Push(Data* data)
{
	if ((rear + 1) % (LEN + 1) == front) // rear의 다음 칸이 front -> 큐가 꽉 참
		return;
	rear = (rear + 1) % (LEN + 1); // rear를 한 칸 옮기고
	arr[rear] = data; // 그 위치에 데이터 추가
}

Data* MyQueue::Pop()
{
	if (Isempty())
		return 0;
	front = (front + 1) % (LEN + 1); // front를 한 칸 옮기고
	return arr[front]; // 그 위치의 데이터 반환
}

bool MyQueue::Isempty()
{
	if (front == rear)
		return true;
	else
		return false;
}

Map::Map()
{
	rows = 0;
	cols = 0;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			(map[i] + j)->setRow(i);
			(map[i] + j)->setCol(j); // 미로의 각 방에 해당 위치 데이터 정보 삽입
		}
	}
}

void Map::setSize(int row, int col)
{
	rows = row;
	cols = col; // 미로는 크기가 달라질 수 있으므로 그때마다 크기 정보를 받음
}

void* Map::getMap()
{
	return map;
}

int Map::getRows()
{
	return rows;
}

int Map::getCols()
{
	return cols;
}

bool Map::findNeighbor(Data* ptr)
{
	if (ptr->getCol() != 0 && map[ptr->getRow()][ptr->getCol() - 1].Isvisited() == false)
		return true; // 왼쪽 방으로 갈 수 있는지
	if (ptr->getCol() != cols - 1 && map[ptr->getRow()][ptr->getCol() + 1].Isvisited() == false)
		return true; // 오른쪽으로 갈 수 있는지
	if (ptr->getRow() != 0 && map[ptr->getRow() - 1][ptr->getCol()].Isvisited() == false)
		return true; // 위쪽으로 갈 수 있는지
	if (ptr->getRow() != rows - 1 && map[ptr->getRow() + 1][ptr->getCol()].Isvisited() == false)
		return true; // 아래로 갈 수 있는지
	return false;
}

bool Map::findRoot(Data* ptr)
{
	if ((ptr->getSide() & 1) == 0 && map[ptr->getRow()][ptr->getCol() - 1].Isvisited() == false)
		return true; // 왼쪽 벽이 뚫려있으면서 왼쪽을 방문하지 않았다면
	if ((ptr->getSide() & 2) == 0 && map[ptr->getRow()][ptr->getCol() + 1].Isvisited() == false)
		return true; // 오른쪽 벽이 뚫려있으면서 오른쪽을 방문하지 않았다면
	if ((ptr->getSide() & 4) == 0 && map[ptr->getRow() - 1][ptr->getCol()].Isvisited() == false)
		return true; // 위쪽 벽이 뚫려있으면서 위쪽을 방문하지 않았다면
	if ((ptr->getSide() & 8) == 0 && map[ptr->getRow() + 1][ptr->getCol()].Isvisited() == false)
		return true; // 아래쪽 벽이 뚫려있으면서 아래쪽을 방문하지 않았다면
	return false;
}

void Map::setVisitFalse()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			map[i][j].setVisit(false);
	}
}

void Map::setSide()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			map[i][j].setSide();
	}
}

void Map::setPar()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			map[i][j].setPar(0);
	}
}

// CStaticCanvasControl

IMPLEMENT_DYNAMIC(CStaticCanvasControl, CStatic)

CStaticCanvasControl::CStaticCanvasControl()
	: m_black_pen(PS_SOLID, 2, RGB(0, 0, 0))
	, m_white_brush(RGB(255, 255, 255))
	, startX(0)
	, startY(0)
	, maze_height(0)
	, maze_width(0)
	, rect_size(0)
	, current_mouse_point(-1, -1)
	, red_y(-1)
	, red_x(-1)
	, blue_y(-1)
	, blue_x(-1)
	, prev_y(-1)
	, prev_x(-1)
	// 멤버 변수 초기화
{
}

CStaticCanvasControl::~CStaticCanvasControl()
{
}


BEGIN_MESSAGE_MAP(CStaticCanvasControl, CStatic)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CStaticCanvasControl 메시지 처리기

void CStaticCanvasControl::BuildMapByDfs(BOOL animate)
{
	Invalidate(FALSE); // 화면의 바뀐 부분만 갱신
	int row, col, ranNum;
	MyStack stack;
	Data* cur, * cho;
	Data(*map)[30];
	CPaintDC dc(this);
	CPen path_pen(PS_SOLID, 4, RGB(155, 155, 255));
	CBrush visit(RGB(155, 155, 255));
	CRect r(0, 0, rect_size - 2, rect_size - 2);

	dc.SelectObject(&path_pen);
	srand((unsigned int)time(NULL));
	row = rand() % miro.getRows();
	col = rand() % miro.getCols(); // 시작 위치 랜덤
	map = (Data(*)[30])miro.getMap();
	stack.Push(&map[row][col]); // 스택에 시작 위치 넣음
	map[row][col].setVisit(true); // 방문 표시
	if (animate) // 애니메이션
	{
		r.MoveToXY(startX + col * rect_size + 1, startY + row * rect_size + 1);
		dc.FillRect(&r, &visit);
	}
	while (!stack.Isempty())
	{
		cur = stack.Pop(); // 스택에서 방 하나 뽑아 현재 노드로 본다
		if (miro.findNeighbor(cur)) // 방문할 근처 방이 있다면
		{
			stack.Push(cur); // 다시 스택에 넣는다
			while (1)
			{
				ranNum = rand() % 4; // 갈 방향 랜덤하게 정하기
				if (ranNum == 0)
				{
					if (cur->getCol() == 0
						|| map[cur->getRow()][cur->getCol() - 1].Isvisited() == true)
						continue; // 갈 수 없다면 다시 랜덤한 방향 고르기
					cho = &map[cur->getRow()][cur->getCol() - 1]; // 다음 방을 choice 방으로 지정
					cho->setVisit(true); // 방문
					cur->deleteLeft(); // 벽 허물기
					cho->deleteRight();
					if (animate) // 애니메이션
					{
						r.MoveToXY(startX + cho->getCol() * rect_size + 1, startY + cho->getRow() * rect_size + 1);
						dc.FillRect(&r, &visit); // 방문한 choice 방 칠하기
						dc.MoveTo(this->startX + cur->getCol() * rect_size,
							this->startY + cur->getRow() * rect_size);
						dc.LineTo(this->startX + cur->getCol() * rect_size,
							this->startY + (cur->getRow() + 1) * rect_size); // 방 사이 벽을 선 덧칠로 없애기
					}
					break;
				}
				if (ranNum == 1) // 방향만 다를 뿐, 방식은 똑같음
				{
					if (cur->getCol() == miro.getCols() - 1
						|| map[cur->getRow()][cur->getCol() + 1].Isvisited() == true)
						continue;
					cho = &map[cur->getRow()][cur->getCol() + 1];
					cho->setVisit(true);
					cur->deleteRight();
					cho->deleteLeft();
					if (animate)
					{
						r.MoveToXY(startX + cho->getCol() * rect_size + 1, startY + cho->getRow() * rect_size + 1);
						dc.FillRect(&r, &visit);
						dc.MoveTo(this->startX + (cur->getCol() + 1) * rect_size,
							this->startY + cur->getRow() * rect_size);
						dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
							this->startY + (cur->getRow() + 1) * rect_size);
					}
					break;
				}
				if (ranNum == 2)
				{
					if (cur->getRow() == 0
						|| map[cur->getRow() - 1][cur->getCol()].Isvisited() == true)
						continue;
					cho = &map[cur->getRow() - 1][cur->getCol()];
					cho->setVisit(true);
					cur->deleteUp();
					cho->deleteDown();
					if (animate)
					{
						r.MoveToXY(startX + cho->getCol() * rect_size + 1, startY + cho->getRow() * rect_size + 1);
						dc.FillRect(&r, &visit);
						dc.MoveTo(this->startX + cur->getCol() * rect_size,
							this->startY + cur->getRow() * rect_size);
						dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
							this->startY + cur->getRow() * rect_size);
					}
					break;
				}
				if (ranNum == 3)
				{
					if (cur->getRow() == miro.getRows() - 1
						|| map[cur->getRow() + 1][cur->getCol()].Isvisited() == true)
						continue;
					cho = &map[cur->getRow() + 1][cur->getCol()];
					cho->setVisit(true);
					cur->deleteDown();
					cho->deleteUp();
					if (animate)
					{
						r.MoveToXY(startX + cho->getCol() * rect_size + 1, startY + cho->getRow() * rect_size + 1);
						dc.FillRect(&r, &visit);
						dc.MoveTo(this->startX + cur->getCol() * rect_size,
							this->startY + (cur->getRow() + 1) * rect_size);
						dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
							this->startY + (cur->getRow() + 1) * rect_size);
					}
					break;
				}
			}
			if (animate)
				Sleep(10); // 애니메이션 효과를 위한 멈춤
			stack.Push(cho); // choice 방을 스택에 넣음
		}
	}
}

void CStaticCanvasControl::findPathByDfs(BOOL animate)
{
	Invalidate(FALSE);
	Data* cur, * des, * next, * end;
	MyStack stack;
	Data(*map)[30];
	CPaintDC dc(this);
	CPen red_pen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen path_pen(PS_SOLID, 4, RGB(155, 155, 255));
	CPen* old_pen;
	CRect r(0, 0, rect_size - 2, rect_size - 2);
	CBrush visit(RGB(155, 155, 255));
	CBrush red(RGB(255, 0, 0));
	CBrush blue(RGB(0, 0, 255));

	map = (Data(*)[30])miro.getMap();
	cur = &map[red_y][red_x]; // 출발지 방
	next = cur;
	des = &map[blue_y][blue_x]; // 도착지 방
	r.MoveToXY(startX + cur->getCol() * rect_size + 1, startY + cur->getRow() * rect_size + 1);
	dc.FillRect(&r, &visit); // 출발지 색칠
	dc.SelectObject(&red);
	dc.Ellipse(startX + cur->getCol() * rect_size, startY + cur->getRow() * rect_size,
		startX + (cur->getCol() + 1) * rect_size, startY + (cur->getRow() + 1) * rect_size); // 출발지 원 다시 그리기
	cur->setVisit(true);
	stack.Push(cur); // 스택에 현재 방 넣기
	old_pen = dc.SelectObject(&path_pen); // path_pen으로 갱신 후 old_pen에 기존 펜 정보 저장
	while (1)
	{
		cur = stack.Pop(); // 스택에서 방 뽑기
		if (cur == des)
			break; // 목적지에 도착했다면 종료
		if (miro.findRoot(cur)) // 갈 방이 있다면
		{
			stack.Push(cur); // 다시 스택에 넣기
			if ((cur->getSide() & 1) == 0 && map[cur->getRow()][cur->getCol() - 1].Isvisited() == false)
			{ // 왼쪽으로 갈 수 있다면
				next = &map[cur->getRow()][cur->getCol() - 1]; // next 노드 지정
				r.MoveToXY(startX + next->getCol() * rect_size + 1, startY + next->getRow() * rect_size + 1);
				dc.FillRect(&r, &visit); // 다음 칸 색칠
				dc.MoveTo(this->startX + cur->getCol() * rect_size,
					this->startY + cur->getRow() * rect_size);
				dc.LineTo(this->startX + cur->getCol() * rect_size,
					this->startY + (cur->getRow() + 1) * rect_size); // 벽 뚫기
			}
			else if ((cur->getSide() & 2) == 0 && map[cur->getRow()][cur->getCol() + 1].Isvisited() == false)
			{ // 방향만 다를 뿐, 방식은 같음
				next = &map[cur->getRow()][cur->getCol() + 1];
				r.MoveToXY(startX + next->getCol() * rect_size + 1, startY + next->getRow() * rect_size + 1);
				dc.FillRect(&r, &visit);
				dc.MoveTo(this->startX + (cur->getCol() + 1) * rect_size,
					this->startY + cur->getRow() * rect_size);
				dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
					this->startY + (cur->getRow() + 1) * rect_size);
			}
			else if ((cur->getSide() & 4) == 0 && map[cur->getRow() - 1][cur->getCol()].Isvisited() == false)
			{
				next = &map[cur->getRow() - 1][cur->getCol()];
				r.MoveToXY(startX + next->getCol() * rect_size + 1, startY + next->getRow() * rect_size + 1);
				dc.FillRect(&r, &visit);
				dc.MoveTo(this->startX + cur->getCol() * rect_size,
					this->startY + cur->getRow() * rect_size);
				dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
					this->startY + cur->getRow() * rect_size);
			}
			else
			{
				next = &map[cur->getRow() + 1][cur->getCol()];
				r.MoveToXY(startX + next->getCol() * rect_size + 1, startY + next->getRow() * rect_size + 1);
				dc.FillRect(&r, &visit);
				dc.MoveTo(this->startX + cur->getCol() * rect_size,
					this->startY + (cur->getRow() + 1) * rect_size);
				dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
					this->startY + (cur->getRow() + 1) * rect_size);
			}
			if (animate)
				Sleep(10); // 애니메이션 효과를 위한 멈춤
			next->setVisit(true); // next 방 방문 표시
			next->setPar(cur); // next 방이 cur에서 왔다는 정보 저장
			stack.Push(next); // next를 스택에 넣기
		}
	}
	end = cur; // 도착 방의 주소를 저장
	dc.SelectObject(old_pen);
	old_pen = dc.SelectObject(&red_pen);
	dc.MoveTo(startX + cur->getCol() * rect_size + rect_size / 2,
		startY + cur->getRow() * rect_size + rect_size / 2); // 도착 방에서 경로 그리기 시작
	cur = cur->getPar();
	while (cur)
	{
		dc.LineTo(startX + cur->getCol() * rect_size + rect_size / 2,
			startY + cur->getRow() * rect_size + rect_size / 2); // 경로 이어가기
		cur = cur->getPar(); // 이전 경로로 이동
	}
	dc.SelectObject(old_pen);
	dc.SelectObject(&blue);
	dc.Ellipse(startX + end->getCol() * rect_size, startY + end->getRow() * rect_size,
		startX + (end->getCol() + 1) * rect_size, startY + (end->getRow() + 1) * rect_size); // 도착 지점 원 그리기
	UpdateWindow();
}

void CStaticCanvasControl::findPathByBfs(BOOL animate)
{
	Invalidate(FALSE);
	Data* cur, * des, * next, * end;
	MyQueue queue;
	Data(*map)[30];
	CPaintDC dc(this);
	CPen red_pen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen path_pen(PS_SOLID, 4, RGB(155, 155, 255));
	CPen* old_pen;
	CRect r(0, 0, rect_size - 2, rect_size - 2);
	CBrush visit(RGB(155, 155, 255));
	CBrush red(RGB(255, 0, 0));
	CBrush blue(RGB(0, 0, 255));

	map = (Data(*)[30])miro.getMap();
	cur = &map[red_y][red_x];
	next = cur;
	des = &map[blue_y][blue_x];
	r.MoveToXY(startX + cur->getCol() * rect_size + 1, startY + cur->getRow() * rect_size + 1);
	dc.FillRect(&r, &visit);
	dc.SelectObject(&red);
	dc.Ellipse(startX + cur->getCol() * rect_size, startY + cur->getRow() * rect_size,
		startX + (cur->getCol() + 1) * rect_size, startY + (cur->getRow() + 1) * rect_size);
	cur->setVisit(true);
	queue.Push(cur); // 큐에 현재 방 넣기
	old_pen = dc.SelectObject(&path_pen);
	while (1)
	{
		cur = queue.Pop(); // 큐에서 방 하나 뽑기
		if (cur == des) // 목적지라면 종료
			break;
		if (miro.findRoot(cur)) // 갈 루트가 있다면
		{
			if ((cur->getSide() & 1) == 0 && map[cur->getRow()][cur->getCol() - 1].Isvisited() == false)
			{ // 왼쪽으로 갈 수 있다면
				next = &map[cur->getRow()][cur->getCol() - 1];
				r.MoveToXY(startX + next->getCol() * rect_size + 1, startY + next->getRow() * rect_size + 1);
				dc.FillRect(&r, &visit); // 다음 방 칠하기
				dc.MoveTo(this->startX + cur->getCol() * rect_size,
					this->startY + cur->getRow() * rect_size);
				dc.LineTo(this->startX + cur->getCol() * rect_size,
					this->startY + (cur->getRow() + 1) * rect_size); // 벽 뚫기
				if (animate)
					Sleep(10);
				next->setVisit(true); // 다음 방 방문 표시 후 큐에 넣기
				next->setPar(cur);
				queue.Push(next);
			}
			if ((cur->getSide() & 2) == 0 && map[cur->getRow()][cur->getCol() + 1].Isvisited() == false)
			{ // 방향만 다를 뿐, 방식은 같음
				next = &map[cur->getRow()][cur->getCol() + 1];
				r.MoveToXY(startX + next->getCol() * rect_size + 1, startY + next->getRow() * rect_size + 1);
				dc.FillRect(&r, &visit);
				dc.MoveTo(this->startX + (cur->getCol() + 1) * rect_size,
					this->startY + cur->getRow() * rect_size);
				dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
					this->startY + (cur->getRow() + 1) * rect_size);
				if (animate)
					Sleep(10);
				next->setVisit(true);
				next->setPar(cur);
				queue.Push(next);
			}
			if ((cur->getSide() & 4) == 0 && map[cur->getRow() - 1][cur->getCol()].Isvisited() == false)
			{
				next = &map[cur->getRow() - 1][cur->getCol()];
				r.MoveToXY(startX + next->getCol() * rect_size + 1, startY + next->getRow() * rect_size + 1);
				dc.FillRect(&r, &visit);
				dc.MoveTo(this->startX + cur->getCol() * rect_size,
					this->startY + cur->getRow() * rect_size);
				dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
					this->startY + cur->getRow() * rect_size);
				if (animate)
					Sleep(10);
				next->setVisit(true);
				next->setPar(cur);
				queue.Push(next);
			}
			if ((cur->getSide() & 8) == 0 && map[cur->getRow() + 1][cur->getCol()].Isvisited() == false)
			{
				next = &map[cur->getRow() + 1][cur->getCol()];
				r.MoveToXY(startX + next->getCol() * rect_size + 1, startY + next->getRow() * rect_size + 1);
				dc.FillRect(&r, &visit);
				dc.MoveTo(this->startX + cur->getCol() * rect_size,
					this->startY + (cur->getRow() + 1) * rect_size);
				dc.LineTo(this->startX + (cur->getCol() + 1) * rect_size,
					this->startY + (cur->getRow() + 1) * rect_size);
				if (animate)
					Sleep(10);
				next->setVisit(true);
				next->setPar(cur);
				queue.Push(next);
			} // BFS는 너비 우선 탐색으로, 한 노드에서 갈 수 있는 루트가 여러 개 있으면 모두 방문하고
		} // 또 그 노드들에서 가지치는 형식으로 탐색하므로 각각 방문할 때마다 next를 큐에 넣어야 함
	}
	end = cur; // 경로 표시
	dc.SelectObject(old_pen);
	old_pen = dc.SelectObject(&red_pen);
	dc.MoveTo(startX + cur->getCol() * rect_size + rect_size / 2,
		startY + cur->getRow() * rect_size + rect_size / 2);
	cur = cur->getPar();
	while (cur)
	{
		dc.LineTo(startX + cur->getCol() * rect_size + rect_size / 2,
			startY + cur->getRow() * rect_size + rect_size / 2);
		cur = cur->getPar();
	}
	dc.SelectObject(old_pen);
	dc.SelectObject(&blue);
	dc.Ellipse(startX + end->getCol() * rect_size, startY + end->getRow() * rect_size,
		startX + (end->getCol() + 1) * rect_size, startY + (end->getRow() + 1) * rect_size);
	UpdateWindow();
}

void CStaticCanvasControl::DrawMap()
{
	Invalidate();
	CPaintDC dc(this);
	Data(*map)[30];
	Data* cur;
	CPen white_pen(PS_SOLID, 4, RGB(255, 255, 255));
	CPen red_pen(PS_SOLID, 5, RGB(255, 0, 0));
	CPen path_pen(PS_SOLID, 4, RGB(155, 155, 255));
	CPen* old_pen;
	CBrush visit(RGB(155, 155, 255));
	CBrush red(RGB(255, 0, 0));
	CBrush blue(RGB(0, 0, 255));
	CBrush yellow(RGB(255, 255, 0));
	CBrush white(RGB(255, 255, 255));
	CRect r(0, 0, rect_size - 2, rect_size - 2);

	// 더블 버퍼링 코드
	// 더블 버퍼링이란, 가상의 DC에 그림을 그린 후 다 그려지면 이를 실제 화면으로 옮기는 것
	// 이 함수에선 dc 대신 memDC에 그린 후 이를 dc에 옮김
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, m_rect_window.Width(), m_rect_window.Height());
	memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, m_rect_window.Width(), m_rect_window.Height(), WHITENESS);

	map = (Data(*)[30])miro.getMap();
	for (int y = startY; y < startY + maze_height; y += rect_size)
	{
		for (int x = startX; x < startX + maze_width; x += rect_size)
		{
			memDC.Rectangle(x, y, x + rect_size, y + rect_size);
			if (x <= current_mouse_point.x && current_mouse_point.x < x + rect_size
				&& y <= current_mouse_point.y && current_mouse_point.y < y + rect_size)
			{ // 마우스의 위치가 방 위에 있으면 그 방을 노란색으로 칠함
				r.MoveToXY(x + 1, y + 1);
				memDC.FillRect(&r, &yellow);
			}
			else if (map[(y - startY) / rect_size][(x - startX) / rect_size].Isvisited())
			{
				r.MoveToXY(x + 1, y + 1);
				memDC.FillRect(&r, &visit);
			}
			if (startX + red_x * rect_size <= x && x < startX + (red_x + 1) * rect_size
				&& startY + red_y * rect_size <= y && y < startY + (red_y + 1) * rect_size)
			{
				memDC.SelectObject(&red);
				memDC.Ellipse(x, y, x + rect_size, y + rect_size);
				memDC.SelectObject(&white); // 출발지 원 그리기
			}
			else if (startX + blue_x * rect_size <= x && x < startX + (blue_x + 1) * rect_size
				&& startY + blue_y * rect_size <= y && y < startY + (blue_y + 1) * rect_size)
			{
				memDC.SelectObject(&blue);
				memDC.Ellipse(x, y, x + rect_size, y + rect_size);
				memDC.SelectObject(&white); // 도착지 원 그리기
			}
		}
	}
	memDC.SelectObject(&white_pen);
	for (int y = 0; y < miro.getRows(); y++) // 선으로 벽 지우기
	{ // 각 방의 정보를 토대로 벽 지우기
		for (int x = 0; x < miro.getCols(); x++)
		{
			if ((map[y][x].getSide() & 1) == 0)
			{
				if (map[y][x].Isvisited() && map[y][x - 1].Isvisited())
				{
					old_pen = memDC.SelectObject(&path_pen);
					memDC.MoveTo(startX + x * rect_size, startY + y * rect_size);
					memDC.LineTo(startX + x * rect_size, startY + (y + 1) * rect_size);
					memDC.SelectObject(old_pen);
				}
				else
				{
					memDC.MoveTo(startX + x * rect_size, startY + y * rect_size);
					memDC.LineTo(startX + x * rect_size, startY + (y + 1) * rect_size);
				}
			}
			if ((map[y][x].getSide() & 2) == 0)
			{
				if (map[y][x].Isvisited() && map[y][x + 1].Isvisited())
				{
					old_pen = memDC.SelectObject(&path_pen);
					memDC.MoveTo(startX + (x + 1) * rect_size, startY + y * rect_size);
					memDC.LineTo(startX + (x + 1) * rect_size, startY + (y + 1) * rect_size);
					memDC.SelectObject(old_pen);
				}
				else
				{
					memDC.MoveTo(startX + (x + 1) * rect_size, startY + y * rect_size);
					memDC.LineTo(startX + (x + 1) * rect_size, startY + (y + 1) * rect_size);
				}
			}
			if ((map[y][x].getSide() & 4) == 0)
			{
				if (map[y][x].Isvisited() && map[y - 1][x].Isvisited())
				{
					old_pen = memDC.SelectObject(&path_pen);
					memDC.MoveTo(startX + x * rect_size, startY + y * rect_size);
					memDC.LineTo(startX + (x + 1) * rect_size, startY + y * rect_size);
					memDC.SelectObject(old_pen);
				}
				else
				{
					memDC.MoveTo(startX + x * rect_size, startY + y * rect_size);
					memDC.LineTo(startX + (x + 1) * rect_size, startY + y * rect_size);
				}
			}
			if ((map[y][x].getSide() & 8) == 0)
			{
				if (map[y][x].Isvisited() && map[y + 1][x].Isvisited())
				{
					old_pen = memDC.SelectObject(&path_pen);
					memDC.MoveTo(startX + x * rect_size, startY + (y + 1) * rect_size);
					memDC.LineTo(startX + (x + 1) * rect_size, startY + (y + 1) * rect_size);
					memDC.SelectObject(old_pen);
				}
				else
				{
					memDC.MoveTo(startX + x * rect_size, startY + (y + 1) * rect_size);
					memDC.LineTo(startX + (x + 1) * rect_size, startY + (y + 1) * rect_size);
				}
			}
		}
	}
	if (prev_y != -1 && prev_x != -1)
	{
		cur = &map[prev_y][prev_x];
		memDC.SelectObject(red_pen);
		memDC.MoveTo(startX + cur->getCol() * rect_size + rect_size / 2,
			startY + cur->getRow() * rect_size + rect_size / 2);
		cur = cur->getPar();
		while (cur)
		{
			memDC.LineTo(startX + cur->getCol() * rect_size + rect_size / 2,
				startY + cur->getRow() * rect_size + rect_size / 2);
			cur = cur->getPar();
		}
	}
	dc.BitBlt(0, 0, m_rect_window.Width(), m_rect_window.Height(), &memDC, 0, 0, SRCCOPY);
	memDC.DeleteDC();
	bitmap.DeleteObject();
	UpdateWindow();
}

void CStaticCanvasControl::OnPaint()
{
	CPaintDC dc(this);// device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CStatic::OnPaint()을(를) 호출하지 마십시오.
	GetClientRect(&(this->m_rect_window));
	dc.FillRect(&(this->m_rect_window), &(this->m_white_brush)); // 미로 그리는 공간을 하얀 배경으로
}

void CStaticCanvasControl::DrawMazeOnGeneration(int row, int column, BOOL animate)
{
	Invalidate();
	CPaintDC dc(this);
	CPen m_black_pen(PS_SOLID, 2, RGB(0, 0, 0));

	if ((row < 4 || row > 30) || (column < 4 || column > 30))
		return;
	miro.setPar();
	miro.setVisitFalse();
	if (m_rect_window.Height() / row > m_rect_window.Width() / column)
		rect_size = m_rect_window.Width() / column;
	else
		rect_size = m_rect_window.Height() / row; // 미로의 방 크기 지정
	maze_height = rect_size * row; // 미로 높이
	maze_width = rect_size * column; // 미로 너비
	startY = (this->m_rect_window.Height() - maze_height) / 2; // 미로 시작 좌표(y)
	startX = (this->m_rect_window.Width() - maze_width) / 2; // 미로 시작 좌표(x)

	miro.setSize(row, column);
	miro.setSide();
	dc.SelectObject(&m_black_pen);
	for (int y = this->startY; y < this->startY + maze_height; y += rect_size)
	{
		for (int x = this->startX; x < this->startX + maze_width; x += rect_size)
			dc.Rectangle(x, y, x + rect_size, y + rect_size); // 미로를 그릴 표 생성
	}
	UpdateWindow();
	BuildMapByDfs(animate); // 메모리 상의 미로 벽 뚫기(애니메이션 체크 시 그림상에서도)
	miro.setVisitFalse();
	DrawMap(); // 애니메이션 미 체크 시 미로가 그려지지 않으므로 DrawMap()으로 미로 그리기
}

void CStaticCanvasControl::DrawPath(BOOL method, BOOL animate)
{
	if (red_y < 0 || red_x < 0 || blue_y < 0 || blue_x < 0 || (red_y == blue_y && red_x == blue_x)
		|| red_y >= miro.getRows() || red_x >= miro.getCols()
		|| blue_y >= miro.getRows() || blue_x >= miro.getCols())
		return; // 출발점(또는 도착점)이 입력되지 않았거나 적절한 위치가 아니라면 종료
	miro.setPar(); // 재탐색을 위해 경로 정보 초기화
	miro.setVisitFalse(); // 재탐색을 위해 방문 정보 초기화
	DrawMap(); // 미로 다시 그리기
	if (method == 1) // method가 선택되지 않으면 기본으로 0인데 이때는 탐색 X
		findPathByDfs(animate); // DFS 방식
	else if (method == 2)
		findPathByBfs(animate); // BFS 방식
	prev_y = blue_y;
	prev_x = blue_x;
}

void CStaticCanvasControl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	this->current_mouse_point = point;
	this->DrawMap(); // 마우스가 움직일 때마다 미로를 다시 그림
	CStatic::OnMouseMove(nFlags, point);
}

void CStaticCanvasControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate();
	CPaintDC dc(this);
	CBrush red(RGB(255, 0, 0));

	dc.SelectObject(&red);
	for (int y = 0; y < miro.getRows(); y++)
	{
		for (int x = 0; x < miro.getCols(); x++)
		{
			if (startX + x * rect_size <= point.x && point.x < startX + (x + 1) * rect_size
				&& startY + y * rect_size <= point.y && point.y < startY + (y + 1) * rect_size)
			{
				dc.Ellipse(startX + x * rect_size, startY + y * rect_size,
					startX + (x + 1) * rect_size, startY + (y + 1) * rect_size);
				red_y = y;
				red_x = x; // 클릭한 출발점에 원을 그리고, 출발점 좌표를 멤버 변수에 저장
			}
		}
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CStaticCanvasControl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate();
	CPaintDC dc(this);
	CBrush blue(RGB(0, 0, 255));

	dc.SelectObject(&blue);
	for (int y = 0; y < miro.getRows(); y++)
	{
		for (int x = 0; x < miro.getCols(); x++)
		{
			if (startX + x * rect_size <= point.x && point.x < startX + (x + 1) * rect_size
				&& startY + y * rect_size <= point.y && point.y < startY + (y + 1) * rect_size)
			{
				dc.Ellipse(startX + x * rect_size, startY + y * rect_size,
					startX + (x + 1) * rect_size, startY + (y + 1) * rect_size);
				blue_y = y;
				blue_x = x; // 클릭한 도작점에 원을 그리고, 도착점 좌표를 멤버 변수에 저장
			}
		}
	}
	CStatic::OnRButtonDown(nFlags, point);
}
