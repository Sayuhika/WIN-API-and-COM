#include "DDA.h"

DDA::DDA(CLSID clsid)
{
	pIDispatch = NULL;
	HRESULT hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch,(void**)&pIDispatch);
	if(FAILED(hr)){throw new std::exception("Не могу создать объект класса  \"DinArray\"");}

	OLECHAR* nameAdd = L"Add";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // должно быть IID_NULL 
		&nameAdd,     // имя функции 
		1,      // число имён 
		GetUserDefaultLCID(), // информация локализации 
		&idAdd     // диспетчерский идентификатор 
	);
	if (FAILED(hr)) { throw new std::exception("Не могу получить ID метода \"Add\""); }

	OLECHAR* nameRemove = L"Remove";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // должно быть IID_NULL 
		&nameRemove,     // имя функции 
		1,      // число имён 
		GetUserDefaultLCID(), // информация локализации 
		&idRemove     // диспетчерский идентификатор 
	);
	if (FAILED(hr)) { throw new std::exception("Не могу получить ID метода \"Remove\""); }

	OLECHAR* nameGetData = L"GetData";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // должно быть IID_NULL 
		&nameGetData,     // имя функции 
		1,      // число имён 
		GetUserDefaultLCID(), // информация локализации 
		&idGetData     // диспетчерский идентификатор 
	);
	if (FAILED(hr)) { throw new std::exception("Не могу получить ID метода \"GetData\""); }

	OLECHAR* namecount = L"count";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // должно быть IID_NULL 
		&namecount,     // имя функции 
		1,      // число имён 
		GetUserDefaultLCID(), // информация локализации 
		&idcount     // диспетчерский идентификатор 
	);
	if (FAILED(hr)) { throw new std::exception("Не могу получить ID метода \"count\""); }

	OLECHAR* namemean = L"mean";
	hr = pIDispatch->GetIDsOfNames(
		IID_NULL,     // должно быть IID_NULL 
		&namemean,     // имя функции 
		1,      // число имён 
		GetUserDefaultLCID(), // информация локализации 
		&idmean     // диспетчерский идентификатор 
	);
	if (FAILED(hr)) { throw new std::exception("Не могу получить ID метода \"mean\""); }
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
		1, // Ноль аргументов
		0 // Ноль именованных аргументов
	};
	HRESULT hr = pIDispatch->Invoke(
		idAdd, // DISPID
		IID_NULL, // Должно быть IID_NULL
		GetUserDefaultLCID(), // Информация локализации
		DISPATCH_METHOD, // Метод
		&dispParamsNoArgs, // Аргументы метода
		NULL, // Результаты
		NULL, // Исключение
		NULL // Ошибка в аргументе
	);

	return hr;
}

HRESULT DDA::Remove(DOUBLE value)
{
	_variant_t v_value(value, VT_R8);

	DISPPARAMS dispParamsNoArgs = {
		&v_value,
		NULL,
		1, // Ноль аргументов
		0 // Ноль именованных аргументов
	};
	HRESULT hr = pIDispatch->Invoke(
		idRemove, // DISPID
		IID_NULL, // Должно быть IID_NULL
		GetUserDefaultLCID(), // Информация локализации
		DISPATCH_METHOD, // Метод
		&dispParamsNoArgs, // Аргументы метода
		NULL, // Результаты
		NULL, // Исключение
		NULL // Ошибка в аргументе
	);

	return hr;
}

HRESULT DDA::GetData(SAFEARRAY** arr)
{
	VARIANT v_arr;

	DISPPARAMS dispParamsNoArgs = {
		NULL,
		NULL,
		0, // Ноль аргументов
		0 // Ноль именованных аргументов
	};
	HRESULT hr = pIDispatch->Invoke(
		idGetData, // DISPID
		IID_NULL, // Должно быть IID_NULL
		GetUserDefaultLCID(), // Информация локализации
		DISPATCH_METHOD, // Метод
		&dispParamsNoArgs, // Аргументы метода
		&v_arr, // Результаты
		NULL, // Исключение
		NULL // Ошибка в аргументе
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
		0, // Ноль аргументов
		0 // Ноль именованных аргументов
	};
	HRESULT hr = pIDispatch->Invoke(
		idcount, // DISPID
		IID_NULL, // Должно быть IID_NULL
		GetUserDefaultLCID(), // Информация локализации
		DISPATCH_METHOD, // Метод
		&dispParamsNoArgs, // Аргументы метода
		&v_pVal, // Результаты
		NULL, // Исключение
		NULL // Ошибка в аргументе
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
		0, // Ноль аргументов
		0 // Ноль именованных аргументов
	};
	HRESULT hr = pIDispatch->Invoke(
		idmean, // DISPID
		IID_NULL, // Должно быть IID_NULL
		GetUserDefaultLCID(), // Информация локализации
		DISPATCH_METHOD, // Метод
		&dispParamsNoArgs, // Аргументы метода
		&v_pVal, // Результаты
		NULL, // Исключение
		NULL // Ошибка в аргументе
	);

	_variant_t v_result(v_pVal);
	*pVal = v_result;

	return hr;
}