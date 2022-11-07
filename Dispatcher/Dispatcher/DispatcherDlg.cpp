
// DispatcherDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Dispatcher.h"
#include "DispatcherDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CDispatcherDlg



CDispatcherDlg::CDispatcherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDispatcherDlg::IDD, pParent)
	, pathToFolder(_T(""))
	, scanFlag(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDispatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, pathToFolder);
	DDX_Check(pDX, IDC_CHECK1, scanFlag);
	DDX_Control(pDX, IDC_LIST1, availablePList);
	DDX_Control(pDX, IDC_LIST2, openPList);
}

BEGIN_MESSAGE_MAP(CDispatcherDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CDispatcherDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CDispatcherDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDispatcherDlg::OnBnClickedButton2)
	ON_EN_UPDATE(IDC_MFCEDITBROWSE1, &CDispatcherDlg::OnEnUpdateMfceditbrowse1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// обработчики сообщений CDispatcherDlg

BOOL CDispatcherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	SetTimer(666,500,NULL);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CDispatcherDlg::OnPaint()
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
HCURSOR CDispatcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDispatcherDlg::OnBnClickedCheck1() // Scan Button
{
	UpdateData(TRUE);

	if (scanFlag){
		availablePList.ResetContent(); // Сбрасываем список

		CFileFind Seeker; // Объект класса для поиска файлов
		BOOL foundFlag = Seeker.FindFile((LPCTSTR)(pathToFolder+"\\*.exe")); // Ищем ехе файлы

		while (foundFlag) {
			foundFlag = Seeker.FindNextFileW(); // Получаем флаг о том, что файл найден
			availablePList.AddString((LPCTSTR)Seeker.GetFileName()); // Добавляем в список найденный ехе файл
		}
	}
}


void CDispatcherDlg::OnBnClickedButton1() // Open Button
{
	CString fileName;
	availablePList.GetText(availablePList.GetCurSel(), fileName);

	BOOL processWorkStatus;
	STARTUPINFO s = { sizeof(s) };
	PROCESS_INFORMATION pInf; // Хранилище HANDLE-ов созданного процесса

	processWorkStatus = ::CreateProcess(NULL, (pathToFolder+"\\"+fileName).GetBuffer(), NULL, NULL, FALSE, 0, NULL, pathToFolder.GetBuffer(), &s, &pInf);


	if (processWorkStatus) {
		int itemIndex = openPList.AddString((LPCTSTR)fileName); // Добавляем в список запущеный процесс + сохраняем индекс 
		openPList.SetItemData(itemIndex,(DWORD)pInf.hProcess); // Сохраняем HANDLE-ы процесса в список
		CloseHandle(pInf.hThread);
	}
}


void CDispatcherDlg::OnBnClickedButton2() // Stop Button
{
	HANDLE hProcess = (HANDLE)openPList.GetItemData(openPList.GetCurSel());
	TerminateProcess(hProcess, EXCEPTION_BREAKPOINT);
	CloseHandle(hProcess);

	openPList.DeleteString(openPList.GetCurSel());
}


void CDispatcherDlg::OnEnUpdateMfceditbrowse1()
{
	UpdateData(TRUE);

	if (scanFlag) {
		availablePList.ResetContent(); // Сбрасываем список

		CFileFind Seeker; // Объект класса для поиска файлов
		BOOL foundFlag = Seeker.FindFile((LPCTSTR)(pathToFolder + "\\*.exe")); // Ищем ехе файлы

		while (foundFlag) {
			foundFlag = Seeker.FindNextFileW(); // Получаем флаг о том, что файл найден
			availablePList.AddString((LPCTSTR)Seeker.GetFileName()); // Добавляем в список найденный ехе файл
		}
	}
}


void CDispatcherDlg::OnTimer(UINT_PTR nIDEvent)
{
	// Выясняем жив ли еще наш процесс: eсли нет, удаляем из списка
	for (int i = 0; i < openPList.GetCount();i++) {
		HANDLE hProcess = (HANDLE)openPList.GetItemData(i);
		
		DWORD exitCode = STILL_ACTIVE;
		GetExitCodeProcess(hProcess, &exitCode);

		if (exitCode != STILL_ACTIVE) {
			CloseHandle(hProcess);
			openPList.DeleteString(i);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}
