// DinArray.cpp: реализация CDinArray

#include "stdafx.h"
#include "DinArray.h"
#include "atlsafe.h"
#include <vector>
#include <list>


// CDinArray
std::list<double> tempArray;

STDMETHODIMP CDinArray::Add(DOUBLE value)
{

	tempArray.push_back(value);
	
	return S_OK;
}


STDMETHODIMP CDinArray::Remove(DOUBLE value)
{
	tempArray.remove(value);

	return S_OK;
}


STDMETHODIMP CDinArray::get_count(ULONG* pVal)
{
	*pVal = tempArray.size();

	return S_OK;
}


STDMETHODIMP CDinArray::get_mean(DOUBLE* pVal)
{
	double result = 0;

	for (auto i : tempArray)
	{
		result += i;
	}
	result /= tempArray.size();
	*pVal = result;

	return S_OK;
}


STDMETHODIMP CDinArray::GetData(SAFEARRAY** arr)
{
	CComSafeArray<double> cArray;

	for (auto i : tempArray)
	{
		cArray.Add(i);
	}

	*arr = cArray.Detach();

	return S_OK;
}
