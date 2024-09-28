#pragma once
#include <Windows.h>
#define LEN 900
#include <cstring>
#include <cstdlib>
#include <ctime>
// CStaticCanvasControl

class Data // 미로 한칸을 가리키는 클래스
{
private:
	bool Isvisit; // 방문 여부
	char side; // 벽 정보
	int row, col; // 해당 방의 위치 정보
	Data* par; // 탐색 시에 이전 방의 위치를 저장
public:
	Data();

	bool Isvisited(); // 여기부터
	void setVisit(bool n);
	void setRow(int n);
	int getRow();
	void setCol(int n);
	int getCol();
	void setPar(Data* data);
	Data* getPar();
	void setSide();
	char getSide(); // 여기까지 setter와 getter
	void deleteLeft();
	void deleteRight();
	void deleteUp();
	void deleteDown(); // 각각 함수 이름에 쓰여진 방향의 벽 지우기
};

class MyStack // DFS에 쓰일 스택
{
private:
	Data* arr[LEN]; // 미로의 방의 주소값을 스택에 넣었다 뺄 것이므로 포인터 배열
	int idx; // 현재 스택의 크기
public:
	MyStack();

	void Push(Data* data); // 스택에 데이터 추가
	Data* Pop(); // 스택에서 데이터 빼기
	bool Isempty(); // 비었는지 여부
};

class MyQueue
{
private:
	Data* arr[LEN + 1]; // circular queue를 구현하였으므로 최대 크기 + 1
	int front, rear; // 가장 최근에 추가한 위치, 가장 먼저 추가한 위치

public:
	MyQueue();

	void Push(Data* data);
	Data* Pop();
	bool Isempty();
};

class Map // 미로 클래스
{
private:
	Data map[30][30]; // 미로가 최대 30 by 30이므로 최대 크기 배열 생성
	int rows; // 미로의 행 길이
	int cols; // 미로의 열 길이

public:
	Map();

	void setSize(int row, int col);
	int getRows();
	int getCols();
	void* getMap(); // setter, getter
	bool findNeighbor(Data* ptr); // 주변에 어떤 칸으로든 이동할 수 있으면 true
	bool findRoot(Data* ptr); // 주변에 이동할 수 있는 root가 있으면 true
	void setVisitFalse(); // 모든 방의 방문 정보를 false로 바꿈
	void setSide(); // 모든 방의 벽을 다 막음
	void setPar(); // par 변수를 초기화 -> 재탐색 시 문제 발생 X 
};

class CStaticCanvasControl : public CStatic // static canvas 클래스
{
	DECLARE_DYNAMIC(CStaticCanvasControl)

public:
	CStaticCanvasControl();
	virtual ~CStaticCanvasControl();

private:
	CPen m_black_pen; // 검정 펜
	CRect m_rect_window; // 미로를 그릴 공간
	CBrush m_white_brush; // 배경에 쓰일 하얀색 브러쉬
	int startX; // 미로의 시작 좌표
	int startY;
	int maze_height; // 미로의 크기
	int maze_width;
	int rect_size; // 미로의 방 하나 크기
	int red_y, red_x, blue_y, blue_x; // 출발점, 도착점 좌표
	int prev_y, prev_x; // 마우스 호버링 시 탐색 그림 유지 위함
	Map miro; // 미로 객체
	CPoint current_mouse_point; // 마우스 호버링 시 필요한 현재 마우스 커서 위치
	void BuildMapByDfs(BOOL animate); // DFS로 맵 생성
	void findPathByDfs(BOOL animate); // DFS로 탐색
	void findPathByBfs(BOOL animate); // BFS로 탐색
	void DrawMap(); // 현재 미로를 그려주는 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint(); // 배경을 칠하는 함수
	void DrawMazeOnGeneration(int row, int column, BOOL animate); // 미로 생성
	void DrawPath(BOOL method, BOOL animate); // 경로 그리는 함수
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); // 마우스가 움직일 때 호출되는 함수
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); // 왼쪽 클릭 시 호출
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point); // 오른쪽 클릭 시 호출
};
