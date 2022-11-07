#pragma once
#include <objbase.h>
#include <comutil.h>
#include <atlsafe.h>
#include <iostream>

class DDA
{
public:
	DDA(CLSID clsid);
	~DDA();
	HRESULT Add (DOUBLE value);
	HRESULT Remove (DOUBLE value);
	HRESULT GetData(SAFEARRAY** arr);
	HRESULT count(ULONG* pVal);
	HRESULT mean(DOUBLE* pVal);
private:
	IDispatch* pIDispatch;
	DISPID idAdd;
	DISPID idRemove;
	DISPID idGetData;
	DISPID idcount;
	DISPID idmean;
};