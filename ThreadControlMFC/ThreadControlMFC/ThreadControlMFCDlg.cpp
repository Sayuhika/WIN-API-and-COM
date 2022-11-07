
// ThreadControlMFCDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "ThreadControlMFC.h"
#include "ThreadControlMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int ThreadNumber1(1), ThreadNumber2(2);
// Диалоговое окно CThreadControlMFCDlg

DWORD WINAPI ThreadJob(LPVOID param) {
	int number = *(int*)param;

	while (TRUE) {
		double x = 1;
		//double x = pow(time(0) * 3.1415926, time(0) * 3.1415926);
		//x = pow(cos(x), sin(x)) * sin(1 / x) * cos(x * x) + pow(sin(x), cos(x)) * cos(1 / x) * sin(x * x);

		switch ((number))
		{
		case 1:
			if (theApp.TSleep1) {
				Sleep(0);
			}
		
			InterlockedExchangeAdd(&(theApp.counter1), 1);
			break;
		case 2:
			if (theApp.TSleep2) {
				Sleep(0);
			}
			
			InterlockedExchangeAdd(&(theApp.counter2), 1);
			break;
		default:
			break;
		}
	}
	return 0;
}

CThreadControlMFCDlg::CThreadControlMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THREADCONTROLMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CThreadControlMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, ThreadLoad1);
	DDX_Control(pDX, IDC_PROGRESS2, ThreadLoad2);
	DDX_Control(pDX, IDC_SLIDER1, PriorityThread1);
	DDX_Control(pDX, IDC_SLIDER2, PriorityThread2);
}

BEGIN_MESSAGE_MAP(CThreadControlMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START_STOP, &CThreadControlMFCDlg::OnBnClickedButtonStartStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_THREAD1_SLEEP, &CThreadControlMFCDlg::OnBnClickedCheckThread1Sleep)
	ON_BN_CLICKED(IDC_CHECK_THREAD2_SLEEP, &CThreadControlMFCDlg::OnBnClickedCheckThread2Sleep)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// Обработчики сообщений CThreadControlMFCDlg

BOOL CThreadControlMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetTimer(100, 200, NULL);
	
	PriorityThread1.SetRange(THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_HIGHEST);
	PriorityThread2.SetRange(THREAD_PRIORITY_LOWEST, THREAD_PRIORITY_HIGHEST);
	PriorityThread1.SetTicFreq(1);
	PriorityThread2.SetTicFreq(1);
	PriorityThread1.SetPos(THREAD_PRIORITY_NORMAL);
	PriorityThread2.SetPos(THREAD_PRIORITY_NORMAL);
	ThreadLoad1.SetRange(0, 100);
	ThreadLoad2.SetRange(0, 100);
	SetProcessAffinityMask(GetCurrentProcess(), 0x1);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CThreadControlMFCDlg::OnPaint()
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
HCURSOR CThreadControlMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CThreadControlMFCDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CThreadControlMFCDlg::OnBnClickedButtonStartStop()
{
	UpdateData(TRUE);
	
	isWorking = !isWorking;

	if (isWorking) {

		DWORD dwThreadID1, dwThreadID2;

		HThread1 = CreateThread(NULL, 0, &ThreadJob, (LPVOID)&ThreadNumber1, 0, &dwThreadID1);
		HThread2 = CreateThread(NULL, 0, &ThreadJob, (LPVOID)&ThreadNumber2, 0, &dwThreadID2);
	}
	else {
		TerminateThread(HThread1, 0);
		TerminateThread(HThread2, 0);

		WaitForSingleObject(HThread1, INFINITE);
		WaitForSingleObject(HThread2, INFINITE);

		CloseHandle(HThread1);
		CloseHandle(HThread2);

		ThreadLoad1.SetPos(0);
		ThreadLoad2.SetPos(0);
	}
}


void CThreadControlMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	
	UpdateData(TRUE);

	if (isWorking) {
		int result1 = (int)InterlockedExchange(&(theApp.counter1), 0);
		int result2 = (int)InterlockedExchange(&(theApp.counter2), 0);

		double load1 = 100.0 * result1 / (result1 + result2);
		double load2 = 100.0 - load1;

		ThreadLoad1.SetPos((int)load1);
		ThreadLoad2.SetPos((int)load2);

		UpdateData(FALSE);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CThreadControlMFCDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	UpdateData(TRUE);

	if (isWorking) {
		SetThreadPriority(HThread1, PriorityThread1.GetPos());
		SetThreadPriority(HThread2, PriorityThread2.GetPos());

		UpdateData(FALSE);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CThreadControlMFCDlg::OnBnClickedCheckThread1Sleep()
{
	theApp.TSleep1 = !theApp.TSleep1;
}

void CThreadControlMFCDlg::OnBnClickedCheckThread2Sleep()
{
	theApp.TSleep2 = !theApp.TSleep2;
}
