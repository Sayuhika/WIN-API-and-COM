// MFCLibraryTestCPL.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "MFCLibraryTestCPL.h"
#include "ErrorSeekerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		должен стоять в качестве первого оператора в
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//

// CMFCLibraryTestCPLApp

BEGIN_MESSAGE_MAP(CMFCLibraryTestCPLApp, CWinApp)
END_MESSAGE_MAP()


// Создание CMFCLibraryTestCPLApp

CMFCLibraryTestCPLApp::CMFCLibraryTestCPLApp()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}


// Единственный объект CMFCLibraryTestCPLApp

CMFCLibraryTestCPLApp theApp;


// Инициализация CMFCLibraryTestCPLApp

BOOL CMFCLibraryTestCPLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

LONG APIENTRY CPlApplet(HWND hWnd, UINT message, LPARAM param1, LPARAM param2) {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LPCPLINFO appletInfo;
	LONG returnCode = 0;

	switch (message)
	{
	case CPL_INIT:
		return TRUE;
	case CPL_GETCOUNT:
		return 1L;
	case CPL_INQUIRE:
		appletInfo = (LPCPLINFO)param2;
		appletInfo->idIcon = IDR_MAINFRAME;
		appletInfo->idName = IDS_STRING_APPLETNAME;
		appletInfo->idInfo = IDS_STRING_APPLETDESCRIPTION;
		appletInfo->lData = 0L;
		break;
	case CPL_DBLCLK: {
		CWnd parent;
		parent.Attach(hWnd);
		CErrorSeekerDlg Dlg;
		INT_PTR responce = Dlg.DoModal();

		if (responce == -1) {
			MessageBox(hWnd, L"Fail Success", L"Complit", MB_OK);
		}

		parent.Detach();
	}
		break;
	default:
		break;
	}

	return returnCode;
}