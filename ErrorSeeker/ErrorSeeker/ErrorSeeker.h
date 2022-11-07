
// ErrorSeeker.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// CErrorSeekerApp:
// Сведения о реализации этого класса: ErrorSeeker.cpp
//

class CErrorSeekerApp : public CWinApp
{
public:
	CErrorSeekerApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CErrorSeekerApp theApp;
