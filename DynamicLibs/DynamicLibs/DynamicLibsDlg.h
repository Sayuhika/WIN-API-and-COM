
// DynamicLibsDlg.h: файл заголовка
//

#pragma once
#include <Cpl.h>

// Диалоговое окно CDynamicLibsDlg
class CDynamicLibsDlg : public CDialogEx
{
// Создание
public:
	CDynamicLibsDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DYNAMICLIBS_DIALOG };
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
	CString pathToApplet;
	CString appletName;
	CString appletDescription;
	afx_msg void OnEnUpdateMfceditbrowse();
	HMODULE hDLL;
//	CStatic icon;
	afx_msg void OnBnClickedButtonLaunchapplet();
	afx_msg void OnClose();
	void GetAppletInfo(APPLET_PROC appletProc, int appletNumber);
	int appletCount;
	int appletNumber;
	afx_msg void OnBnClickedButtonAppletback();
	afx_msg void OnBnClickedButtonAppletnext();
	CStatic icon;
};
