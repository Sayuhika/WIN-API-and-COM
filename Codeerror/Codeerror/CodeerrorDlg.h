
// CodeerrorDlg.h : ���� ���������
//

#pragma once


// ���������� ���� CCodeerrorDlg
class CCodeerrorDlg : public CDialogEx
{
// ��������
public:
	CCodeerrorDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
	enum { IDD = IDD_CODEERROR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
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
