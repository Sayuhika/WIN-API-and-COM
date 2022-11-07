
// SynchronizationOfThreadsMFCv2Dlg.h: файл заголовка
//

#pragma once


// Диалоговое окно CSynchronizationOfThreadsMFCv2Dlg
class CSynchronizationOfThreadsMFCv2Dlg : public CDialogEx
{
// Создание
public:
	CSynchronizationOfThreadsMFCv2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYNCHRONIZATIONOFTHREADSMFCV2_DIALOG };
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
	afx_msg void OnEnChangeEditmaintext();
//	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnDestroy();
	bool isSender;
	void ReceiveMessage();
	void MakeSender();
	HANDLE fileMap;
	HANDLE syncThread;
	HANDLE hEventSenderSend;
	HANDLE hEventSenderAlive;
	CEdit editText;
};
