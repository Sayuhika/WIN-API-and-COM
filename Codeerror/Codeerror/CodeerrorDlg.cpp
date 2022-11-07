
// CodeerrorDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "Codeerror.h"
#include "CodeerrorDlg.h"
#include "afxdialogex.h"
#include "stdlib.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CCodeerrorDlg



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


// ����������� ��������� CCodeerrorDlg

BOOL CCodeerrorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CCodeerrorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CCodeerrorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCodeerrorDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	int EC_NV(0);

	// �������� �� ����������� 
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
	// TODO: �������� ���� ��� ����������� �����������
}
