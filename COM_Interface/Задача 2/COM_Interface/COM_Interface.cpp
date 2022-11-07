#include <iostream>
#include "../COMDLL/Interfaces.h"

using namespace std;

int main()
{
	// Создать компонент
	CoInitialize(NULL);
	ICollection* pICollection = NULL;
	HRESULT hr = CoCreateInstance(CLSID_CLIST, NULL, CLSCTX_INPROC_SERVER, IID_ICollection, (void**)&pICollection);
	if (FAILED(hr))
	{
		return 2;
	}

	// Объекты
	Object PI;
	PI.Type = otDouble;
	PI.Value.Double = 3.14159265358;

	Object Exp;
	Exp.Type = otDouble;
	Exp.Value.Double = 2.718281828;

	Object IntValue;
	IntValue.Type = otInt;
	IntValue.Value.Int = 123456789;

	Object ArrObj;
	ArrObj.Type = otArray;
	ArrObj.Value.Array = new ObjectArray{ new Object[3]{PI, Exp, IntValue}, 3};


	Object objResult;

	ObjectArray* arr;

	unsigned int count;
	// Работа с объектами

	setlocale(LC_ALL, "Russian");
	if (SUCCEEDED(hr))
	{
		cout << "Начало работы с pICollection" << endl;
		cout << endl;
		pICollection->Add(PI);
		cout << "Был добавлен объект PI;" << endl;
		pICollection->Add(Exp);
		cout << "Был добавлен объект Exp;" << endl;
		pICollection->Add(IntValue);
		cout << "Был добавлен объект IntValue;" << endl;
		pICollection->GetCount(&count);
		cout << "Число элементов в списке: " << count << endl;
		pICollection->Remove(PI);
		cout << "Был удален объект PI;" << endl;
		pICollection->GetCount(&count);
		cout << "Число элементов в списке: " << count << endl;
		pICollection->Add(PI);
		cout << "Был добавлен объект PI;" << endl;
		pICollection->Add(ArrObj);
		cout << "Был добавлен объект ArrObj типа ObjectArray;" << endl;
		pICollection->GetCount(&count);
		cout << "Число элементов в списке: " << count << endl;
		pICollection->ToArray(&arr);
		cout << "Список преобразован в массив:" << endl;
		for (unsigned i = 0; i < (arr->Count); i++)
		{
			cout << i + 1 << ") ";
			switch (arr->Data[i].Type)
			{
			case otInt:
				cout << arr->Data[i].Value.Int << endl;
				break;
			case otDouble:
				cout << arr->Data[i].Value.Double << endl;
				break;
			case otArray:
				cout << "размер массива ArrObj: "<<arr->Data[i].Value.Array->Count << endl;
				break;
			default:
				break;
			}
			 
		}
		cout << endl;
		cout << "Конец работы с pICollection" << endl;
		cout << endl;
	}

	IEnumerator* pIEnumerator = NULL;
	hr = pICollection->QueryInterface(IID_IEnumerator, (void**)&pIEnumerator);

	if (SUCCEEDED(hr))
	{
		cout << "Начало работы с pIEnumerator" << endl;
		cout << endl;

		// Схема Reset() -> MoveNext() -> GetCurrent() -> ...

		//Reset()
		pIEnumerator->Reset(); 
		cout << "Сброс итератора до -1" << endl;

		// MoveNext()
		if ((pIEnumerator->MoveNext(&count) == S_OK) && (count == TRUE)) 
		{
			cout << "Итератор сместился на 1" << endl;
		}
		else
		{
			cout << "Итератор не сместился" << endl;
		}

		// GetCurrent()
		if (SUCCEEDED(pIEnumerator->GetCurrent(&objResult))) 
		{
			cout << "Получен объект по итератору 0 со значением: " << objResult.Value.Double << endl;
		}
		else
		{
			cout << "Объект не был найден" << endl;
		}

		// MoveNext()
		if ((pIEnumerator->MoveNext(&count) == S_OK) && (count == TRUE))
		{
			cout << "Итератор сместился на 1" << endl;
		}
		else
		{
			cout << "Итератор не сместился" << endl;
		}

		// GetCurrent()
		if (SUCCEEDED(pIEnumerator->GetCurrent(&objResult)))
		{
			cout << "Получен объект по итератору 1 со значением: " << objResult.Value.Int << endl;
		}
		else
		{
			cout << "Объект не был найден" << endl;
		}
		cout << endl;
		pIEnumerator->Release();
		cout << "Конец работы с pIEnumerator" << endl;
		cout << endl;
	}
	IEnumerator* pIEnumeratorfromICollection = 0;
	hr = pICollection->QueryInterface(IID_IEnumerator, (void**)&pIEnumeratorfromICollection);
	if (SUCCEEDED(hr))
	{
		cout << "Начало работы с pIEnumeratorfromICollection" << endl;
		cout << endl;

		// Схема Reset() -> MoveNext() -> GetCurrent() -> ...

		//Reset()
		pIEnumeratorfromICollection->Reset();
		cout << "Сброс итератора до 0" << endl;

		//MoveNext()
		if ((pIEnumeratorfromICollection->MoveNext(&count) == S_OK) && (count == TRUE))
		{
			cout << "Итератор сместился на 1" << endl;
		}
		else
		{
			cout << "Итератор не сместился" << endl;
		}

		//GetCurrent()
		if (SUCCEEDED(pIEnumeratorfromICollection->GetCurrent(&objResult)))
		{
			cout << "Получен объект по итератору 0 со значением: " << objResult.Value.Double << endl;
		}
		else
		{
			cout << "Объект не был найден" << endl;
		}

		cout << endl;
		pIEnumeratorfromICollection->Release();
		cout << "Конец работы с pIEnumeratorfromICollection" << endl;
		cout << endl;
	}
	
	pICollection->Release();
	int a;
	cin >> a;
	return 0;
}


