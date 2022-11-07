#include "pch.h"
#include "Component.h"

IUnknown* CreateInstance()
{
	IUnknown* pI = static_cast<ICollection*>(new CList);
	pI->AddRef();
	return pI;
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
	*arr = new ObjectArray;
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

HRESULT __stdcall CList::MoveNext(unsigned int *result)
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
	if(counter > size - 1)
	{
		return E_ACCESSDENIED;
	}
	*obj = this->container[counter];
	return S_OK;
}