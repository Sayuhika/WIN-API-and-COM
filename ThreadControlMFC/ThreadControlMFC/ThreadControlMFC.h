
// ThreadControlMFC.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// CThreadControlMFCApp:
// Сведения о реализации этого класса: ThreadControlMFC.cpp
//

class CThreadControlMFCApp : public CWinApp
{
public:
	CThreadControlMFCApp();
	unsigned int counter1, counter2;
	bool TSleep1, TSleep2;

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CThreadControlMFCApp theApp;
