#pragma once
#include <iostream>
#include "COMlist_h.h"


//////////////////////////////////////////////////////////////////////////
// Класс списка
class CList : public ICollection, public IEnumerator
{
	Object* container;
	int size;
	int capacity;
	int counter;

	// Счётчик ссылок
	ULONG m_cRef;

	// Следующие методы вызываются только через указатели на
	// соответствующие интерфейсы, поэтому в компоненте могут быть закрытыми!
public:
	////////////////////////////
	// Методы IUnknown
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();
	
	////////////////////////////
	// Методы ICollection
	HRESULT __stdcall Add(Object obj);
	HRESULT __stdcall Remove(Object obj);
	HRESULT __stdcall GetCount(unsigned *count);
	HRESULT __stdcall ToArray(ObjectArray **arr);

	////////////////////////////
	// Методы IEnumerator
	HRESULT __stdcall Reset();
	HRESULT __stdcall MoveNext(int *result);
	HRESULT __stdcall GetCurrent(Object *obj);

public:

	// Конструктор
	CList() : m_cRef(0) 
	{
		size = 0;
		capacity = 0;
		container = nullptr;
	}

	// Деструктор
	~CList() { std::cout << __FUNCTION__ << std::endl; }
};

class CListFactory :public IClassFactory
{
	// Счётчик ссылок
	ULONG m_cRef;

public:
	////////////////////////////
	// Методы IUnknown
	HRESULT __stdcall QueryInterface(REFIID iid, void** ppv);
	ULONG __stdcall AddRef();
	ULONG __stdcall Release();

	////////////////////////////
	// Методы IClassFactory
	HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, REFIID iid, void** ppv);
	HRESULT __stdcall LockServer(BOOL bLock);

	// Конструктор
	CListFactory() : m_cRef(0) {}

	// Деструктор
	~CListFactory() {}
};
