
// Dispatcher.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CDispatcherApp:
// � ���������� ������� ������ ��. Dispatcher.cpp
//

class CDispatcherApp : public CWinApp
{
public:
	CDispatcherApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CDispatcherApp theApp;