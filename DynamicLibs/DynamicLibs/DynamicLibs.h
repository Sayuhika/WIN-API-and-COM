
// DynamicLibs.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// основные символы


// CDynamicLibsApp:
// Сведения о реализации этого класса: DynamicLibs.cpp
//

class CDynamicLibsApp : public CWinApp
{
public:
	CDynamicLibsApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CDynamicLibsApp theApp;
