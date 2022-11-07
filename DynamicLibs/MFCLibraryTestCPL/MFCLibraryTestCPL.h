// MFCLibraryTestCPL.h: основной файл заголовка для библиотеки DLL MFCLibraryTestCPL
//

#pragma once
#include <Cpl.h>

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// CMFCLibraryTestCPLApp
// Реализацию этого класса см. в файле MFCLibraryTestCPL.cpp
//

class CMFCLibraryTestCPLApp : public CWinApp
{
public:
	CMFCLibraryTestCPLApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

LONG APIENTRY CPlApplet(HWND hWnd, UINT message, LPARAM param1, LPARAM param2);