// dllmain.cpp: ���������� DllMain.

#include "stdafx.h"
#include "resource.h"
#include "DArray_i.h"
#include "dllmain.h"

CDArrayModule _AtlModule;

// ����� ����� DLL
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
