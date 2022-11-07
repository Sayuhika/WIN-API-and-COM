
// DispatcherDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "Dispatcher.h"
#include "DispatcherDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CDispatcherDlg



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


// ����������� ��������� CDispatcherDlg

BOOL CDispatcherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������
	SetTimer(666,500,NULL);

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CDispatcherDlg::OnPaint()
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
HCURSOR CDispatcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDispatcherDlg::OnBnClickedCheck1() // Scan Button
{
	UpdateData(TRUE);

	if (scanFlag){
		availablePList.ResetContent(); // ���������� ������

		CFileFind Seeker; // ������ ������ ��� ������ ������
		BOOL foundFlag = Seeker.FindFile((LPCTSTR)(pathToFolder+"\\*.exe")); // ���� ��� �����

		while (foundFlag) {
			foundFlag = Seeker.FindNextFileW(); // �������� ���� � ���, ��� ���� ������
			availablePList.AddString((LPCTSTR)Seeker.GetFileName()); // ��������� � ������ ��������� ��� ����
		}
	}
}


void CDispatcherDlg::OnBnClickedButton1() // Open Button
{
	CString fileName;
	availablePList.GetText(availablePList.GetCurSel(), fileName);

	BOOL processWorkStatus;
	STARTUPINFO s = { sizeof(s) };
	PROCESS_INFORMATION pInf; // ��������� HANDLE-�� ���������� ��������

	processWorkStatus = ::CreateProcess(NULL, (pathToFolder+"\\"+fileName).GetBuffer(), NULL, NULL, FALSE, 0, NULL, pathToFolder.GetBuffer(), &s, &pInf);


	if (processWorkStatus) {
		int itemIndex = openPList.AddString((LPCTSTR)fileName); // ��������� � ������ ��������� ������� + ��������� ������ 
		openPList.SetItemData(itemIndex,(DWORD)pInf.hProcess); // ��������� HANDLE-� �������� � ������
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
		availablePList.ResetContent(); // ���������� ������

		CFileFind Seeker; // ������ ������ ��� ������ ������
		BOOL foundFlag = Seeker.FindFile((LPCTSTR)(pathToFolder + "\\*.exe")); // ���� ��� �����

		while (foundFlag) {
			foundFlag = Seeker.FindNextFileW(); // �������� ���� � ���, ��� ���� ������
			availablePList.AddString((LPCTSTR)Seeker.GetFileName()); // ��������� � ������ ��������� ��� ����
		}
	}
}


void CDispatcherDlg::OnTimer(UINT_PTR nIDEvent)
{
	// �������� ��� �� ��� ��� �������: e��� ���, ������� �� ������
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
