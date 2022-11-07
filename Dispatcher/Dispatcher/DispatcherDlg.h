
// DispatcherDlg.h : файл заголовка
//

#pragma once


// диалоговое окно CDispatcherDlg
class CDispatcherDlg : public CDialogEx
{
// Создание
public:
	CDispatcherDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_DISPATCHER_DIALOG };

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
	CString pathToFolder;
	int scanFlag;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton2();
	CListBox availablePList;
	CListBox openPList;
	afx_msg void OnEnUpdateMfceditbrowse1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
