
// CodeerrorDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "Codeerror.h"
#include "CodeerrorDlg.h"
#include "afxdialogex.h"
#include "stdlib.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CCodeerrorDlg



CCodeerrorDlg::CCodeerrorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCodeerrorDlg::IDD, pParent)
	, EC_text_value(_T(""))
	, EC_number_value(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCodeerrorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, EC_number_value);
	DDX_Text(pDX, IDC_MESSAGE_OE, EC_text_value);
	DDX_Text(pDX, IDC_EDIT1, EC_number_value);
}

BEGIN_MESSAGE_MAP(CCodeerrorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCodeerrorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// обработчики сообщений CCodeerrorDlg

BOOL CCodeerrorDlg::OnInitDialog()
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

void CCodeerrorDlg::OnPaint()
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
HCURSOR CCodeerrorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCodeerrorDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	int EC_NV(0);

	// Проверка на разрядность 
	if ((EC_number_value[0] == '0') && ((EC_number_value[1] == 'x') || (EC_number_value[1] == 'X')))
	{
		EC_NV = wcstol(EC_number_value, NULL, 16);
	}
	else 
		if((EC_number_value[0] == '0') && ((EC_number_value[1] != 'x') || (EC_number_value[1] != 'X')))
		{
			EC_NV = wcstol(EC_number_value, NULL, 8);
		}
		else 
			{
			EC_NV = _ttoi(EC_number_value);
			}

	DWORD Error = EC_NV;
	wchar_t *text; 
	::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, Error, 0, (LPTSTR)&text,0,NULL);
	EC_text_value = text;

	::LocalFree(text);
	UpdateData(FALSE);
	// TODO: добавьте свой код обработчика уведомлений
}
