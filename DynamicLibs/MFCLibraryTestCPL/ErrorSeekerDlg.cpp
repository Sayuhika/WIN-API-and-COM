
// ErrorSeekerDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "MFCLibraryTestCPL.h"
#include "ErrorSeekerDlg.h"
#include "afxdialogex.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CErrorSeekerDlg



CErrorSeekerDlg::CErrorSeekerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ERRORSEEKER_DIALOG, pParent)
	, errorTextMessage(_T(""))
	, errorValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CErrorSeekerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, errorTextMessage);
	DDX_Text(pDX, IDC_EDIT1, errorValue);
}

BEGIN_MESSAGE_MAP(CErrorSeekerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CErrorSeekerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CErrorSeekerDlg

BOOL CErrorSeekerDlg::OnInitDialog()
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

void CErrorSeekerDlg::OnPaint()
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
HCURSOR CErrorSeekerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CErrorSeekerDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	
	wchar_t *temp = errorValue.GetBuffer();
	wchar_t *text;
	wchar_t *endptr = NULL;
	DWORD Error;

	if (errorValue.Find(L"0x") == 0) {
		Error = wcstoul(temp, &endptr, 16);
	}
	else {
		if (errorValue.Find('0') == 0) {
			Error = wcstoul(temp, &endptr, 8);
		}
		else {
			Error = wcstoul(temp, &endptr, 10);
		}
	}
	
	if (wcscmp(endptr,L"") == 0){
		::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, Error, 0, (LPTSTR)&text, 0, NULL);
		errorTextMessage = text;
	}
	else {
		errorTextMessage = "Unexceptable error value";
	}

	

	UpdateData(FALSE);
}
