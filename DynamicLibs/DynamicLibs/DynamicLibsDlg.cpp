
// DynamicLibsDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "DynamicLibs.h"
#include "DynamicLibsDlg.h"
#include "afxdialogex.h"
#include <string> 


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CDynamicLibsDlg



CDynamicLibsDlg::CDynamicLibsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DYNAMICLIBS_DIALOG, pParent)
	, pathToApplet(_T(""))
	, appletName(_T(""))
	, appletDescription(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDynamicLibsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE, pathToApplet);
	DDX_Text(pDX, IDC_EDIT_appletName, appletName);
	DDX_Text(pDX, IDC_EDIT_appletDescription, appletDescription);
	DDX_Control(pDX, IDPCICON, icon);
}

BEGIN_MESSAGE_MAP(CDynamicLibsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_UPDATE(IDC_MFCEDITBROWSE, &CDynamicLibsDlg::OnEnUpdateMfceditbrowse)
	ON_BN_CLICKED(IDC_BUTTON_LAUNCHAPPLET, &CDynamicLibsDlg::OnBnClickedButtonLaunchapplet)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_APPLETBACK, &CDynamicLibsDlg::OnBnClickedButtonAppletback)
	ON_BN_CLICKED(IDC_BUTTON_APPLETNEXT, &CDynamicLibsDlg::OnBnClickedButtonAppletnext)
END_MESSAGE_MAP()


// Обработчики сообщений CDynamicLibsDlg

BOOL CDynamicLibsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

void CDynamicLibsDlg::OnPaint()
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
HCURSOR CDynamicLibsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDynamicLibsDlg::GetAppletInfo(APPLET_PROC appletProc, int appletNumber) {
	CPLINFO appletInfo; // хранит информацию об апплете
	appletProc(this->GetSafeHwnd(), CPL_INQUIRE, appletNumber, (LPARAM)&appletInfo);
	wchar_t tempInfo[1024];

	// Вытаскиваем информацию из апплета:
	// Имя
	if (LoadString(hDLL, (UINT)appletInfo.idName, (LPWSTR)tempInfo, sizeof(tempInfo))) {
		appletName = tempInfo;
	}
	// Инфо
	if (LoadString(hDLL, (UINT)appletInfo.idInfo, (LPWSTR)tempInfo, sizeof(tempInfo))) {
		appletDescription = tempInfo;
	}
	// Иконка
	if (appletInfo.idIcon != 0xcccccccc) {
		//HANDLE appletIcon = LoadImage(hDLL, (LPCWSTR)("#"+ std::to_string(appletInfo.idIcon)).c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
		HICON appletIcon = LoadIcon(hDLL, (LPCWSTR)(appletInfo.idIcon));
		icon.SetIcon((HICON)appletIcon);
	}
}

void CDynamicLibsDlg::OnEnUpdateMfceditbrowse()
{
	UpdateData(TRUE);

	if (hDLL != NULL) {
		APPLET_PROC appletProc = (APPLET_PROC)GetProcAddress(hDLL,"CPlApplet");
		appletProc(this->GetSafeHwnd(), CPL_EXIT, 0, 0);
		FreeLibrary(hDLL);
	}
	
	hDLL = LoadLibrary(pathToApplet);
	APPLET_PROC appletProc = (APPLET_PROC)GetProcAddress(hDLL, "CPlApplet");
	
	if (appletProc == NULL) {
		// Если апплет не загрузился, закрываем библиотеку
		MessageBox(L"Похоже библиотека разбился",L"Ошибка");
		if (hDLL != NULL) {
			FreeLibrary(hDLL);
			hDLL = NULL;
		}
	}
	else {
		if (appletProc(this->GetSafeHwnd(),CPL_INIT, 0, 0)) {
			appletCount = appletProc(this->GetSafeHwnd(), CPL_GETCOUNT, 0, 0); // получаем значение кол-ва апплетов в выбранной библиотеке
			
			appletNumber = appletCount-1;
			GetAppletInfo(appletProc, appletNumber);
		}
	}

	UpdateData(FALSE);
}


void CDynamicLibsDlg::OnBnClickedButtonLaunchapplet()
{
	UpdateData(TRUE);

	APPLET_PROC appletProc = (APPLET_PROC)GetProcAddress(hDLL, "CPlApplet");

	if (appletProc == NULL) {
		// Если апплет не загрузился, закрываем библиотеку
		MessageBox(L"Похоже библиотека разбился", L"Ошибка");
	}
	else {
		CPLINFO appletInfo;
		appletProc(this->GetSafeHwnd(), CPL_DBLCLK, appletNumber, (LPARAM)&appletInfo);
	}
}


void CDynamicLibsDlg::OnClose()
{
	if (hDLL != NULL) {
		APPLET_PROC appletProc = (APPLET_PROC)GetProcAddress(hDLL, "CPlApplet");
		appletProc(this->GetSafeHwnd(), CPL_EXIT, 0, 0);
		FreeLibrary(hDLL);
	}

	CDialogEx::OnClose();
}


void CDynamicLibsDlg::OnBnClickedButtonAppletback()
{
	APPLET_PROC appletProc = (APPLET_PROC)GetProcAddress(hDLL, "CPlApplet");

	if (appletProc == NULL) {
		// Если апплет не загрузился, закрываем библиотеку
		MessageBox(L"Похоже библиотека разбился", L"Ошибка");
	}
	else {
		appletNumber--;

		// Проверяем границы спина
		if (appletNumber < 0) {
			appletNumber = appletCount - 1;
		}

		GetAppletInfo(appletProc, appletNumber);
	}

	UpdateData(FALSE);
}


void CDynamicLibsDlg::OnBnClickedButtonAppletnext()
{
	APPLET_PROC appletProc = (APPLET_PROC)GetProcAddress(hDLL, "CPlApplet");

	if (appletProc == NULL) {
		// Если апплет не загрузился, закрываем библиотеку
		MessageBox(L"Похоже библиотека разбился", L"Ошибка");
	}
	else {
		appletNumber++;

		// Проверяем границы спина
		if (appletNumber >= appletCount) {
			appletNumber = 0;
		}

		GetAppletInfo(appletProc, appletNumber);
	}

	UpdateData(FALSE);
}
