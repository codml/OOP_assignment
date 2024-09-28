#pragma once
#include <Windows.h>
#define LEN 900
#include <cstring>
#include <cstdlib>
#include <ctime>
// CStaticCanvasControl

class Data // �̷� ��ĭ�� ����Ű�� Ŭ����
{
private:
	bool Isvisit; // �湮 ����
	char side; // �� ����
	int row, col; // �ش� ���� ��ġ ����
	Data* par; // Ž�� �ÿ� ���� ���� ��ġ�� ����
public:
	Data();

	bool Isvisited(); // �������
	void setVisit(bool n);
	void setRow(int n);
	int getRow();
	void setCol(int n);
	int getCol();
	void setPar(Data* data);
	Data* getPar();
	void setSide();
	char getSide(); // ������� setter�� getter
	void deleteLeft();
	void deleteRight();
	void deleteUp();
	void deleteDown(); // ���� �Լ� �̸��� ������ ������ �� �����
};

class MyStack // DFS�� ���� ����
{
private:
	Data* arr[LEN]; // �̷��� ���� �ּҰ��� ���ÿ� �־��� �� ���̹Ƿ� ������ �迭
	int idx; // ���� ������ ũ��
public:
	MyStack();

	void Push(Data* data); // ���ÿ� ������ �߰�
	Data* Pop(); // ���ÿ��� ������ ����
	bool Isempty(); // ������� ����
};

class MyQueue
{
private:
	Data* arr[LEN + 1]; // circular queue�� �����Ͽ����Ƿ� �ִ� ũ�� + 1
	int front, rear; // ���� �ֱٿ� �߰��� ��ġ, ���� ���� �߰��� ��ġ

public:
	MyQueue();

	void Push(Data* data);
	Data* Pop();
	bool Isempty();
};

class Map // �̷� Ŭ����
{
private:
	Data map[30][30]; // �̷ΰ� �ִ� 30 by 30�̹Ƿ� �ִ� ũ�� �迭 ����
	int rows; // �̷��� �� ����
	int cols; // �̷��� �� ����

public:
	Map();

	void setSize(int row, int col);
	int getRows();
	int getCols();
	void* getMap(); // setter, getter
	bool findNeighbor(Data* ptr); // �ֺ��� � ĭ���ε� �̵��� �� ������ true
	bool findRoot(Data* ptr); // �ֺ��� �̵��� �� �ִ� root�� ������ true
	void setVisitFalse(); // ��� ���� �湮 ������ false�� �ٲ�
	void setSide(); // ��� ���� ���� �� ����
	void setPar(); // par ������ �ʱ�ȭ -> ��Ž�� �� ���� �߻� X 
};

class CStaticCanvasControl : public CStatic // static canvas Ŭ����
{
	DECLARE_DYNAMIC(CStaticCanvasControl)

public:
	CStaticCanvasControl();
	virtual ~CStaticCanvasControl();

private:
	CPen m_black_pen; // ���� ��
	CRect m_rect_window; // �̷θ� �׸� ����
	CBrush m_white_brush; // ��濡 ���� �Ͼ�� �귯��
	int startX; // �̷��� ���� ��ǥ
	int startY;
	int maze_height; // �̷��� ũ��
	int maze_width;
	int rect_size; // �̷��� �� �ϳ� ũ��
	int red_y, red_x, blue_y, blue_x; // �����, ������ ��ǥ
	int prev_y, prev_x; // ���콺 ȣ���� �� Ž�� �׸� ���� ����
	Map miro; // �̷� ��ü
	CPoint current_mouse_point; // ���콺 ȣ���� �� �ʿ��� ���� ���콺 Ŀ�� ��ġ
	void BuildMapByDfs(BOOL animate); // DFS�� �� ����
	void findPathByDfs(BOOL animate); // DFS�� Ž��
	void findPathByBfs(BOOL animate); // BFS�� Ž��
	void DrawMap(); // ���� �̷θ� �׷��ִ� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint(); // ����� ĥ�ϴ� �Լ�
	void DrawMazeOnGeneration(int row, int column, BOOL animate); // �̷� ����
	void DrawPath(BOOL method, BOOL animate); // ��� �׸��� �Լ�
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); // ���콺�� ������ �� ȣ��Ǵ� �Լ�
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); // ���� Ŭ�� �� ȣ��
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point); // ������ Ŭ�� �� ȣ��
};
