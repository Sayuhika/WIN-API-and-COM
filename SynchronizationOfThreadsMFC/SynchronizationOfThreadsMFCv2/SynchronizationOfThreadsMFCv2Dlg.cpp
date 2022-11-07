
// SynchronizationOfThreadsMFCv2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "SynchronizationOfThreadsMFCv2.h"
#include "SynchronizationOfThreadsMFCv2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CSynchronizationOfThreadsMFCv2Dlg



CSynchronizationOfThreadsMFCv2Dlg::CSynchronizationOfThreadsMFCv2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYNCHRONIZATIONOFTHREADSMFCV2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSynchronizationOfThreadsMFCv2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITMAINTEXT, editText);
}

BEGIN_MESSAGE_MAP(CSynchronizationOfThreadsMFCv2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDITMAINTEXT, &CSynchronizationOfThreadsMFCv2Dlg::OnEnChangeEditmaintext)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// Обработчики сообщений CSynchronizationOfThreadsMFCv2Dlg

DWORD WINAPI threadJob(LPVOID param) {
	HANDLE eventsToWait[2] = { ((CSynchronizationOfThreadsMFCv2Dlg*)param)->hEventSenderAlive, ((CSynchronizationOfThreadsMFCv2Dlg*)param)->hEventSenderSend};

	while (true) {
		DWORD wait = WaitForMultipleObjects(2, eventsToWait, FALSE, INFINITE);
		if (wait == WAIT_OBJECT_0) {
			((CSynchronizationOfThreadsMFCv2Dlg*)param)->MakeSender();
		}
		else if(wait == WAIT_OBJECT_0 + 1){
			((CSynchronizationOfThreadsMFCv2Dlg*)param)->ReceiveMessage();
		}
	};

	return(0);
}

void CSynchronizationOfThreadsMFCv2Dlg::ReceiveMessage()
{
	LPTSTR textBuffer = (LPTSTR)MapViewOfFile(fileMap, FILE_MAP_READ, 0, 0, 256);
	editText.SetWindowText(textBuffer);
	UnmapViewOfFile(textBuffer); 
}

void CSynchronizationOfThreadsMFCv2Dlg::MakeSender() {
	
	SetWindowText(L"Отправитель");
	fileMap = OpenFileMapping(FILE_MAP_WRITE, FALSE, L"fileMap");
	isSender = true;
	editText.SetReadOnly(FALSE);

	hEventSenderAlive = OpenEvent(EVENT_MODIFY_STATE, FALSE, L"textSenderAlive");
	hEventSenderSend = OpenEvent(EVENT_MODIFY_STATE, FALSE, L"textSender");

	ResetEvent(hEventSenderAlive);
	TerminateThread(syncThread, 0);
}

BOOL CSynchronizationOfThreadsMFCv2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

		// Определение роли окна
	if (OpenEvent(SYNCHRONIZE, FALSE, L"textSender")) {
		SetWindowText(L"Получатель");
		fileMap = OpenFileMapping(FILE_MAP_READ, FALSE, L"fileMap");
		isSender = false;
		editText.SetReadOnly(TRUE);
		DWORD threadID;
		hEventSenderSend = OpenEvent(SYNCHRONIZE, FALSE, L"textSender");
		hEventSenderAlive = OpenEvent(SYNCHRONIZE, FALSE, L"textSenderAlive");
		syncThread = CreateThread(NULL, 0, &threadJob, (LPVOID)this, 0, &threadID);
	}
	else {
		SetWindowText(L"Отправитель");
		hEventSenderSend = CreateEvent(NULL, TRUE, FALSE, L"textSender");
		hEventSenderAlive = CreateEvent(NULL, FALSE, FALSE, L"textSenderAlive");
		isSender = true;
		fileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, L"fileMap");
	}

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CSynchronizationOfThreadsMFCv2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CSynchronizationOfThreadsMFCv2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSynchronizationOfThreadsMFCv2Dlg::OnEnChangeEditmaintext()
{
	if (isSender) 
	{
		// Считываем текст с окна-отправителя в фаил объекта ядра
		LPTSTR textBuffer = (LPTSTR)MapViewOfFile(fileMap, FILE_MAP_ALL_ACCESS, 0, 0, 256);
		editText.GetWindowText(textBuffer, INT_MAX);
		UnmapViewOfFile(textBuffer);

		// Триггерим получателей на получение текста
		PulseEvent(hEventSenderSend);
	}
	
}

void CSynchronizationOfThreadsMFCv2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (syncThread != NULL) {
		TerminateThread(syncThread, 0);
	}
	if (isSender) {
		SetEvent(hEventSenderAlive);

		CloseHandle(hEventSenderAlive);
		CloseHandle(hEventSenderSend);
	}
}
