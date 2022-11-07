
// SynchronizationOfThreadsMFCv2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// CSynchronizationOfThreadsMFCv2App:
// Сведения о реализации этого класса: SynchronizationOfThreadsMFCv2.cpp
//

class CSynchronizationOfThreadsMFCv2App : public CWinApp
{
public:
	CSynchronizationOfThreadsMFCv2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CSynchronizationOfThreadsMFCv2App theApp;
