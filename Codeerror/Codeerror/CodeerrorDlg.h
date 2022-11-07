
// CodeerrorDlg.h : файл заголовка
//

#pragma once


// диалоговое окно CCodeerrorDlg
class CCodeerrorDlg : public CDialogEx
{
// Создание
public:
	CCodeerrorDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_CODEERROR_DIALOG };

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
//	int EC_number_value;
	afx_msg void OnBnClickedOk();
	CString EC_text_value;
	CString EC_number_value;
};
