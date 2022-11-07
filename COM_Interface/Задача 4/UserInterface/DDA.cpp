#include "DDA.h"

DDA::DDA(CLSID clsid)
{
	pIDispatch = NULL;
	HRESULT hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch,(void**)&pIDispatch);
	if(FAILED(hr)){throw new std::exception("�� ���� ������� ������ ������  \"DinArray\"");}

	OLECHAR* nameAdd = L"Add";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // ������ ���� IID_NULL 
		&nameAdd,     // ��� ������� 
		1,      // ����� ��� 
		GetUserDefaultLCID(), // ���������� ����������� 
		&idAdd     // ������������� ������������� 
	);
	if (FAILED(hr)) { throw new std::exception("�� ���� �������� ID ������ \"Add\""); }

	OLECHAR* nameRemove = L"Remove";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // ������ ���� IID_NULL 
		&nameRemove,     // ��� ������� 
		1,      // ����� ��� 
		GetUserDefaultLCID(), // ���������� ����������� 
		&idRemove     // ������������� ������������� 
	);
	if (FAILED(hr)) { throw new std::exception("�� ���� �������� ID ������ \"Remove\""); }

	OLECHAR* nameGetData = L"GetData";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // ������ ���� IID_NULL 
		&nameGetData,     // ��� ������� 
		1,      // ����� ��� 
		GetUserDefaultLCID(), // ���������� ����������� 
		&idGetData     // ������������� ������������� 
	);
	if (FAILED(hr)) { throw new std::exception("�� ���� �������� ID ������ \"GetData\""); }

	OLECHAR* namecount = L"count";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // ������ ���� IID_NULL 
		&namecount,     // ��� ������� 
		1,      // ����� ��� 
		GetUserDefaultLCID(), // ���������� ����������� 
		&idcount     // ������������� ������������� 
	);
	if (FAILED(hr)) { throw new std::exception("�� ���� �������� ID ������ \"count\""); }

	OLECHAR* namemean = L"mean";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // ������ ���� IID_NULL 
		&namemean,     // ��� ������� 
		1,      // ����� ��� 
		GetUserDefaultLCID(), // ���������� ����������� 
		&idmean     // ������������� ������������� 
	);
	if (FAILED(hr)) { throw new std::exception("�� ���� �������� ID ������ \"mean\""); }
}

DDA::~DDA()
{
	pIDispatch->Release();
}

HRESULT DDA::Add(DOUBLE value)
{
	_variant_t v_value(value, VT_R8);

	DISPPARAMS dispParamsNoArgs = {
		&v_value,
		NULL,
		1, // ���� ����������
		0 // ���� ����������� ����������
	};
	HRESULT hr = pIDispatch->Invoke(
		idAdd, // DISPID
		IID_NULL, // ������ ���� IID_NULL
		GetUserDefaultLCID(), // ���������� �����������
		DISPATCH_METHOD, // �����
		&dispParamsNoArgs, // ��������� ������
		NULL, // ����������
		NULL, // ����������
		NULL // ������ � ���������
	);

	return hr;
}

HRESULT DDA::Remove(DOUBLE value)
{
	_variant_t v_value(value, VT_R8);

	DISPPARAMS dispParamsNoArgs = {
		&v_value,
		NULL,
		1, // ���� ����������
		0 // ���� ����������� ����������
	};
	HRESULT hr = pIDispatch->Invoke(
		idRemove, // DISPID
		IID_NULL, // ������ ���� IID_NULL
		GetUserDefaultLCID(), // ���������� �����������
		DISPATCH_METHOD, // �����
		&dispParamsNoArgs, // ��������� ������
		NULL, // ����������
		NULL, // ����������
		NULL // ������ � ���������
	);

	return hr;
}

HRESULT DDA::GetData(SAFEARRAY** arr)
{
	VARIANT v_arr;

	DISPPARAMS dispParamsNoArgs = {
		NULL,
		NULL,
		0, // ���� ����������
		0 // ���� ����������� ����������
	};
	HRESULT hr = pIDispatch->Invoke(
		idGetData, // DISPID
		IID_NULL, // ������ ���� IID_NULL
		GetUserDefaultLCID(), // ���������� �����������
		DISPATCH_METHOD, // �����
		&dispParamsNoArgs, // ��������� ������
		&v_arr, // ����������
		NULL, // ����������
		NULL // ������ � ���������
	);

	*arr = v_arr.parray;

	return hr;
}

HRESULT DDA::count(ULONG* pVal)
{
	VARIANT v_pVal;

	DISPPARAMS dispParamsNoArgs = {
		NULL,
		NULL,
		0, // ���� ����������
		0 // ���� ����������� ����������
	};
	HRESULT hr = pIDispatch->Invoke(
		idcount, // DISPID
		IID_NULL, // ������ ���� IID_NULL
		GetUserDefaultLCID(), // ���������� �����������
		DISPATCH_METHOD, // �����
		&dispParamsNoArgs, // ��������� ������
		&v_pVal, // ����������
		NULL, // ����������
		NULL // ������ � ���������
	);

	_variant_t v_result(v_pVal);
	*pVal = v_result;

	return hr;
}

HRESULT DDA::mean(DOUBLE* pVal)
{
	VARIANT v_pVal;

	DISPPARAMS dispParamsNoArgs = {
		NULL,
		NULL,
		0, // ���� ����������
		0 // ���� ����������� ����������
	};
	HRESULT hr = pIDispatch->Invoke(
		idmean, // DISPID
		IID_NULL, // ������ ���� IID_NULL
		GetUserDefaultLCID(), // ���������� �����������
		DISPATCH_METHOD, // �����
		&dispParamsNoArgs, // ��������� ������
		&v_pVal, // ����������
		NULL, // ����������
		NULL // ������ � ���������
	);

	_variant_t v_result(v_pVal);
	*pVal = v_result;

	return hr;
}