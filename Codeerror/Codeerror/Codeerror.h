
// Codeerror.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CCodeerrorApp:
// � ���������� ������� ������ ��. Codeerror.cpp
//

class CCodeerrorApp : public CWinApp
{
public:
	CCodeerrorApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CCodeerrorApp theApp;