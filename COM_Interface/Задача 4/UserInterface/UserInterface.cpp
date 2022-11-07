#include <iostream>
using namespace std;

#define DISPATCH

#ifndef DISPATCH
#import "../DArrayDll/x64/Debug/DArray.tlb"
using namespace DArrayLib;
#else
#include "DDA.h"
#endif

int main()
{
	CoInitialize(NULL);

	// ���������������� ���������� OLE 
	HRESULT hr = OleInitialize(NULL);
	
	// �������� CLSID ���������� 
	wchar_t progid[] = L"DArrayLib.CDinArray";
	CLSID clsid;
	hr = CLSIDFromProgID(progid, &clsid);

	if (SUCCEEDED(hr)) 
	{
		try 
		{ 
			double Pi = 3.14159265359;
			double Exp = 2.71828182846;
			double Fi = 1.61803398875;
			ULONG value;
			double mean;
			SAFEARRAY* pCArray;
			CComSafeArray<double> *CArray = NULL;

			setlocale(LC_ALL, "Russian");

#ifdef DISPATCH
			DDA DinArr(clsid);

			if (SUCCEEDED(DinArr.Add(Pi)))
			{
				cout << "�������� ������� Pi: " << Pi << endl;
			};
			if (SUCCEEDED(DinArr.Add(Exp)))
			{
				cout << "�������� ������� Exp: " << Exp << endl;
			};
			if (SUCCEEDED(DinArr.Add(Fi)))
			{
				cout << "�������� ������� Fi: " << Fi << endl;
			};

			if (SUCCEEDED(DinArr.count(&value)))
			{
				cout << "����� ��������� � �������: " << value << endl;
			};
			if (SUCCEEDED(DinArr.mean(&mean)))
			{
				cout << "������� �������� ��������� �������: " << mean << endl;
			};

			// ��������� �������� ������� � �������������� Remove
			if (SUCCEEDED(DinArr.Remove(Exp)))
			{
				cout << "Exp ������ �� �������" << endl;
			};
			if (SUCCEEDED(DinArr.count(&value)))
			{
				cout << "����� ��������� � �������: " << value << endl;
			};
			if (SUCCEEDED(DinArr.mean(&mean)))
			{
				cout << "������� �������� ��������� �������: " << mean << endl;
			};

			if (SUCCEEDED(DinArr.GetData(&pCArray)))
			{
				CArray = new CComSafeArray<double>(pCArray);
				cout << "������ ������� ������ �� ������. ���������� ��������� � ���� �������: " << CArray->GetCount() << endl;
			};
#else
			IDinArrayPtr IDAp = NULL;
			IDAp = IDinArrayPtr(__uuidof(CDinArray));

			if (SUCCEEDED(IDAp->Add(Pi)))
			{
			cout << "�������� ������� Pi: " << Pi << endl;
			};
			if (SUCCEEDED(IDAp->Add(Exp)))
			{
			cout << "�������� ������� Exp: " << Exp << endl;
			};
			if (SUCCEEDED(IDAp->Add(Fi)))
			{
			cout << "�������� ������� Fi: " << Fi << endl;
			};

			if (SUCCEEDED(IDAp->count(&value)))
			{
			cout << "����� ��������� � �������: " << value << endl;
			};
			if (SUCCEEDED(IDAp->mean(&mean)))
			{
			cout << "������� �������� ��������� �������: " << mean << endl;
			};

			// ��������� �������� ������� � �������������� Remove
			if (SUCCEEDED(IDAp->Remove(Exp)))
			{
			cout << "Exp ������ �� �������" << endl;
			};
			if (SUCCEEDED(DinArr.count(&value)))
			{
			cout << "����� ��������� � �������: " << value << endl;
			};
			if (SUCCEEDED(IDAp->mean(&mean)))
			{
			cout << "������� �������� ��������� �������: " << mean << endl;
			};

			if (SUCCEEDED(IDAp->GetData(&pCArray)))
			{
			CArray = new CComSafeArray<double>(pCArray);
			cout << "������ ������� ������ �� ������. ���������� ��������� � ���� �������: " << CArray->GetCount() << endl;
			};
#endif // DISPATCH

			return 0;
		}
		catch (exception e) 
		{
			cout << e.what() << endl;
		};	
	}

	return 1;
}