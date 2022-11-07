// dllmain.cpp: реализация DllMain.

#include "stdafx.h"
#include "resource.h"
#include "DArray_i.h"
#include "dllmain.h"

CDArrayModule _AtlModule;

// Точка входа DLL
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
