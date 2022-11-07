#pragma once
#include <objbase.h>

//////////////////////////////////////////////////////////////////////////
// Тип объекта

enum ObjectType
{
	// целый
	otInt,

	// вещественный
	otDouble,

	// массив
	otArray
};

//////////////////////////////////////////////////////////////////////////
// Объект - значение произвольного типа (предварительное объявление)

struct Object;

//////////////////////////////////////////////////////////////////////////
// ObjectArray - Массив значений Object

struct ObjectArray
{
	// элементы массива
	Object *Data;

	// количество элементов массива
	unsigned Count;
};

//////////////////////////////////////////////////////////////////////////
// Объект - значение произвольного типа

struct Object
{
	// тип объекта
	ObjectType Type;

	union
	{
		// значение целого типа
		int Int;

		// значение вещественного типа
		double Double;

		// значение типа "массив"
		ObjectArray *Array;
	} Value;
};

bool operator == (Object obj1, Object obj2)
{
	if (obj1.Type != obj2.Type) return false;

	switch (obj1.Type)
	{
	case otInt: return (obj1.Value.Int == obj2.Value.Int);
	case otDouble: return (obj1.Value.Double == obj2.Value.Double);
	case otArray: return (obj1.Value.Array == obj2.Value.Array);
	default:
		throw "Ошибка сравнения: Успех. Тип не поддерживается.";
	}
}
//////////////////////////////////////////////////////////////////////////
// Интерфейс коллекции
// {37F7727A-0174-4F2B-ADE9-271B949AA229}

static const GUID IID_ICollection = 
{ 0x37f7727a, 0x174, 0x4f2b, { 0xad, 0xe9, 0x27, 0x1b, 0x94, 0x9a, 0xa2, 0x29 } };

interface ICollection : public IUnknown
{
	// добавить элемент в коллекцию
	virtual HRESULT __stdcall Add(Object obj) = 0;

	// удалить элемент из коллекции
	virtual HRESULT __stdcall Remove(Object obj) = 0;

	// получить количество элементов коллекции
	virtual HRESULT __stdcall GetCount(unsigned *count) = 0;

	// преобразовать коллекцию в массив
	virtual HRESULT __stdcall ToArray(ObjectArray **arr) = 0;
};


//////////////////////////////////////////////////////////////////////////
// Интерфейс перечислителя
// {7BAAB13D-AC13-484C-A1A0-132B28136425}

static const GUID IID_IEnumerator = 
{ 0x7baab13d, 0xac13, 0x484c, { 0xa1, 0xa0, 0x13, 0x2b, 0x28, 0x13, 0x64, 0x25 } };

interface IEnumerator : public IUnknown
{
	// возврат в исходное состояние
	virtual HRESULT __stdcall Reset() = 0;

	// переход к следующему элементу
	virtual HRESULT __stdcall MoveNext(unsigned int *result) = 0;

	// получить текущий элемент
	virtual HRESULT __stdcall GetCurrent(Object *obj) = 0;
};


//////////////////////////////////////////////////////////////////////////
// Тип функции создания экземпляра компонента

typedef IUnknown* (*CREATEINSTANCEPROC)();


//////////////////////////////////////////////////////////////////////////
// Экспортируемая функция создания экземпляра компонента

extern "C" __declspec(dllexport) IUnknown* CreateInstance();
