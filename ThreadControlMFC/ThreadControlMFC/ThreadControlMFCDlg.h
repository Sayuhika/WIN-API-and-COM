
// ThreadControlMFCDlg.h: файл заголовка
//

#pragma once

#include <afxwin.h>
#include <afxcmn.h>

// Диалоговое окно CThreadControlMFCDlg
class CThreadControlMFCDlg : public CDialogEx
{
// Создание
public:
	CThreadControlMFCDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREADCONTROLMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonStartStop();
	HANDLE HThread1, HThread2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CProgressCtrl ThreadLoad1;
	CProgressCtrl ThreadLoad2;
	bool isWorking;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheckThread2Sleep();
	afx_msg void OnBnClickedCheckThread1Sleep();
	CSliderCtrl PriorityThread1;
	CSliderCtrl PriorityThread2;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
