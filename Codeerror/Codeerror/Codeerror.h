
// Codeerror.h : главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CCodeerrorApp:
// О реализации данного класса см. Codeerror.cpp
//

class CCodeerrorApp : public CWinApp
{
public:
	CCodeerrorApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CCodeerrorApp theApp;