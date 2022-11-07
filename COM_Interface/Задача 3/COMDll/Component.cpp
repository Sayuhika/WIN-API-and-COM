#include "Component.h"
#include <Shlwapi.h>

bool operator == (Object obj1, Object obj2)
{
	if (obj1.Type != obj2.Type) return false;

	switch (obj1.Type)
	{
	case otInt: return(obj1.Value.Int == obj2.Value.Int);
	case otDouble: return(obj1.Value.Double == obj2.Value.Double);
	case otArray: return(obj1.Value.Array == obj2.Value.Array);
	default:
		throw "Ошибка сравнения: Успех. Тип не поддерживается.";
	}
}

HRESULT __stdcall CList::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == IID_IUnknown)
	{
		// Клиент запрашивает интерфейс IUnknown
		*ppv = static_cast<ICollection*>(this);
	}
	else if (iid == IID_ICollection)
	{
		// Клиент запрашивает интерфейс IX
		*ppv = static_cast<ICollection*>(this);
	}
	else if (iid == IID_IEnumerator)
	{
		// Клиент запрашивает интерфейс IY
		*ppv = static_cast<IEnumerator*>(this);
	}
	else
	{
		// Мы не поддерживаем запрашиваемый клиентом
		// интерфейс. Установить возвращаемый указатель
		// в NULL
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

ULONG __stdcall CList::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CList::Release()
{
	if (--m_cRef == 0)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}

HRESULT __stdcall CList::Add(Object obj)
{
	size++;
	if (size >= capacity)
	{
		Object* newContainer = new Object[2 * size];
		memcpy(newContainer, this->container, capacity * sizeof(Object));
		delete[capacity](this->container);
		capacity = 2 * size;
		this->container = newContainer;
	}
	this->container[size - 1] = obj;

	return S_OK;
}

HRESULT __stdcall CList::Remove(Object obj)
{
	int n;
	for (n = 0; n < size; n++) 
	{
		if (this->container[n] == obj) 
		{
			break;
		}
	}
	memcpy(this->container + n, this->container + n + 1, (size - n - 1) * sizeof(Object));
	size--;
	if (size <= capacity / 2)
	{
		Object* newContainer = new Object[capacity / 2];
		memcpy(newContainer, this->container, (capacity / 2) * sizeof(Object));
		delete[capacity](this->container);
		capacity /= 2;
		this->container = newContainer;
	}

	return S_OK;
}

HRESULT __stdcall CList::GetCount(unsigned *count) 
{
	*count = size;
	return S_OK;
}

HRESULT __stdcall CList::ToArray(ObjectArray **arr)
{
	*arr = (ObjectArray*) CoTaskMemAlloc(sizeof(ObjectArray));
	(*arr)->Count = size;
	(*arr)->Data = new Object[size];
	memcpy((*arr)->Data, this->container, size * sizeof(Object));
	return S_OK;
}

HRESULT __stdcall CList::Reset()
{
	counter = -1;
	return S_OK;
}

HRESULT __stdcall CList::MoveNext(int *result)
{
	if(counter < size - 1)
	{ 
		counter++;
		*result = TRUE;
	}
	else 
	{
		*result = FALSE;
	}
	return S_OK;
}

HRESULT __stdcall CList::GetCurrent(Object *obj)
{
	if((counter > size - 1)||(counter <=-1))
	{
		return E_ACCESSDENIED;
	}
	*obj = this->container[counter];
	return S_OK;
}

long g_cComponents = 0; // счётчик активных компонентов
long g_cServerLocks = 0; // счётчик блокировок 
HMODULE thisDLL;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		thisDLL = hModule;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

HRESULT __stdcall CListFactory::QueryInterface(REFIID iid, void** ppv)
{
	if (iid == IID_IUnknown)
	{
		// Клиент запрашивает интерфейс IUnknown
		*ppv = static_cast<IClassFactory*>(this);
	}
	else if (iid == IID_IClassFactory)
	{
		// Клиент запрашивает интерфейс IX
		*ppv = static_cast<IClassFactory*>(this);
	}
	else
	{
		// Мы не поддерживаем запрашиваемый клиентом
		// интерфейс. Установить возвращаемый указатель
		// в NULL
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	AddRef();
	return S_OK;
}

ULONG __stdcall CListFactory::AddRef()
{
	return ++m_cRef;
}

ULONG __stdcall CListFactory::Release()
{
	if (--m_cRef == 0)
	{
		delete this;
		return 0;
	}
	return m_cRef;
}

HRESULT __stdcall CListFactory::CreateInstance(IUnknown* pUnknownOuter, REFIID iid, void** ppv)
{
	CList* рList = new CList;
	if (рList == NULL) return E_OUTOFMEMORY;
	рList->AddRef();
	// Получить запрошенный интерфейс
	HRESULT hr = рList->QueryInterface(iid, ppv);
	рList->Release();
	return hr;
}

HRESULT __stdcall CListFactory::LockServer(BOOL bLock)
{
	if (bLock) g_cServerLocks++;
	else g_cServerLocks--;
	return S_OK;
}

// Получить фабрику класса
STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, void** ppv)
{
	// Создать фабрику класса
	CListFactory* pFactory = new CListFactory;
	if (pFactory == NULL) return E_OUTOFMEMORY;
	pFactory->AddRef();
	// Получить требуемый интерфейс
	HRESULT hr = pFactory->QueryInterface(iid, ppv);
	pFactory->Release();
	return hr;
}

STDAPI DllRegisterServer()
{
	LPCWSTR STR_CLSID;

	if (SUCCEEDED(StringFromCLSID(CLSID_CList, (LPOLESTR*)&STR_CLSID)))
	{
		std::wstring pathREG = L"SOFTWARE\\Classes\\CLSID\\";
		pathREG.append(STR_CLSID);
		CoTaskMemFree((LPVOID)STR_CLSID);

		LSTATUS ls = RegSetValue(HKEY_CURRENT_USER, pathREG.c_str(), REG_SZ, L"COM interface work", 0);

		if(ls == ERROR_SUCCESS)
		{
			DWORD size = 200;
			LPWSTR pathToDLL = new WCHAR[size];

			if (SUCCEEDED(GetModuleFileName(thisDLL,pathToDLL, size)))
			{
				pathREG.append(L"\\InprocServer32");
				RegSetValue(HKEY_CURRENT_USER, pathREG.c_str(), REG_SZ, pathToDLL, 0);
				delete[size] pathToDLL;
			}
		}
	}

	return S_OK;
}

STDAPI DllUnregisterServer() 
{
	PCWSTR STR_CLSID;

	if (SUCCEEDED(StringFromCLSID(CLSID_CList, (LPOLESTR*)&STR_CLSID)))
	{
		std::wstring pathREG = L"SOFTWARE\\Classes\\CLSID\\";
		pathREG.append(STR_CLSID);
		CoTaskMemFree((LPVOID)STR_CLSID);

		SHDeleteKey(HKEY_CURRENT_USER, pathREG.c_str());
	}

	return S_OK;
}

STDAPI DllCanUnloadNow()
{
	if ((g_cComponents == 0)&&(g_cServerLocks == 0))
	{
		return S_OK;
	}

	return S_FALSE;
}

