// DinArray.h: объявление CDinArray

#pragma once
#include "resource.h"       // основные символы



#include "DArray_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Однопотоковые COM-объекты не поддерживаются должным образом платформой Windows CE, например платформами Windows Mobile, в которых не предусмотрена полная поддержка DCOM. Определите _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA, чтобы принудить ATL поддерживать создание однопотоковых COM-объектов и разрешить использование его реализаций однопотоковых COM-объектов. Для потоковой модели в вашем rgs-файле задано значение 'Free', поскольку это единственная потоковая модель, поддерживаемая не-DCOM платформами Windows CE."
#endif

using namespace ATL;


// CDinArray

class ATL_NO_VTABLE CDinArray :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDinArray, &CLSID_DinArray>,
	public IDispatchImpl<IDinArray, &IID_IDinArray, &LIBID_DArrayLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDinArray()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DINARRAY)


BEGIN_COM_MAP(CDinArray)
	COM_INTERFACE_ENTRY(IDinArray)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(Add)(DOUBLE value);
	STDMETHOD(Remove)(DOUBLE value);
	STDMETHOD(get_count)(ULONG* pVal);
	STDMETHOD(get_mean)(DOUBLE* pVal);
	STDMETHOD(GetData)(SAFEARRAY** arr);
};

OBJECT_ENTRY_AUTO(__uuidof(DinArray), CDinArray)
