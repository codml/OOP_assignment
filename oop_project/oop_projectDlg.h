
// oop_projectDlg.h: 헤더 파일
//

#pragma once

#include "CStaticCanvasControl.h"

// CoopprojectDlg 대화 상자
class CoopprojectDlg : public CDialogEx
{
// 생성입니다.
public:
	CoopprojectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OOP_PROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSolvingRadioGroupClicked(UINT uiID); // radio button grouping 하는 함수
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonExit(); // exit 버튼 누르면 호출됨
private:
	CStaticCanvasControl m_static_canvas_control; // canvas를 컨트롤하는 변수
public:
	afx_msg void OnBnClickedButtonGenerate(); // 미로 생성 버튼을 누르면 호출
	afx_msg void OnBnClickedButtonSolve(); // 미로 solve 버튼을 누르면 호출
private:
	int m_edit_row; // edit box에 들어온 값을 저장할 변수
	int m_edit_column; // edit box에 들어온 값을 저장할 변수
	BOOL m_solving_method; // 탐색 방식을 정하는 변수
	BOOL m_check_animate_generation; // 미로 생성 애니메이션 여부
private:
	BOOL m_check_animate_solve; // 미로 탐색 애니메이션 여부
};
