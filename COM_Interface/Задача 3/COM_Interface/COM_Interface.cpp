#include <iostream>
#import "../COMDll/x64/Debug/COMDll.tlb"

using namespace lib;
using namespace std;

int main()
{
	int mainResult = 0;
	// Создать компонент
	CoInitialize(NULL);

	ICollectionPtr ICp = NULL;
	IEnumeratorPtr IEp = NULL;

	try
	{
		ICp = ICollectionPtr(__uuidof(CList));
		

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
		ArrObj.Value.Array = new ObjectArray{ new Object[3]{PI, Exp, IntValue}, 3 };


		Object objResult;

		ObjectArray* arr = NULL;

		unsigned int count;
		// Работа с объектами

		setlocale(LC_ALL, "Russian");

		cout << "Начало работы с pICollection" << endl;
		cout << endl;
		ICp->Add(PI);
		cout << "Был добавлен объект PI;" << endl;
		ICp->Add(Exp);
		cout << "Был добавлен объект Exp;" << endl;
		ICp->Add(IntValue);
		cout << "Был добавлен объект IntValue;" << endl;
		ICp->GetCount(&count);
		cout << "Число элементов в списке: " << count << endl;
		ICp->Remove(PI);
		cout << "Был удален объект PI;" << endl;
		ICp->GetCount(&count);
		cout << "Число элементов в списке: " << count << endl;
		ICp->Add(PI);
		cout << "Был добавлен объект PI;" << endl;
		ICp->Add(ArrObj);
		cout << "Был добавлен объект ArrObj типа ObjectArray;" << endl;
		ICp->GetCount(&count);
		cout << "Число элементов в списке: " << count << endl;
		ICp->ToArray(&arr);
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
				cout << "размер массива ArrObj: " << arr->Data[i].Value.Array->Count << endl;
				break;
			default:
				break;
			}

		}
		cout << endl;
		cout << "Конец работы с pICollection" << endl;
		cout << endl;

		ICp->QueryInterface(__uuidof(IEnumerator), (void**)&IEp);

		cout << "Начало работы с pIEnumerator" << endl;
		cout << endl;

		// Схема Reset() -> MoveNext() -> GetCurrent() -> ...

		//Reset()
		IEp->Reset();
		cout << "Сброс итератора до -1" << endl;

		int iter;
		// MoveNext()
		if ((IEp->MoveNext(&iter) == S_OK) && (iter == TRUE))
		{
			cout << "Итератор сместился на 1" << endl;
		}
		else
		{
			cout << "Итератор не сместился" << endl;
		}

		// GetCurrent()
		if (SUCCEEDED(IEp->GetCurrent(&objResult)))
		{
			cout << "Получен объект по итератору 0 со значением: " << objResult.Value.Double << endl;
		}
		else
		{
			cout << "Объект не был найден" << endl;
		}

		// MoveNext()
		if ((IEp->MoveNext(&iter) == S_OK) && (iter == TRUE))
		{
			cout << "Итератор сместился на 1" << endl;
		}
		else
		{
			cout << "Итератор не сместился" << endl;
		}

		// GetCurrent()
		if (SUCCEEDED(IEp->GetCurrent(&objResult)))
		{
			cout << "Получен объект по итератору 1 со значением: " << objResult.Value.Int << endl;
		}
		else
		{
			cout << "Объект не был найден" << endl;
		}
		cout << endl;
		cout << "Конец работы с pIEnumerator" << endl;
		cout << endl;

		if (arr!=NULL)
		{
			CoTaskMemFree(arr);
		}
	}
	catch (_com_error cer)
	{
		wcout << cer.ErrorMessage() << endl;
		mainResult = 1;
	}

	ICp = NULL;
	IEp = NULL;

	//system("pause");
	CoUninitialize();

	return mainResult;
}
	
