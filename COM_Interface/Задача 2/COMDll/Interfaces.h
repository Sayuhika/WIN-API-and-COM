#pragma once
#include <objbase.h>

//////////////////////////////////////////////////////////////////////////
// ��� �������

enum ObjectType
{
	// �����
	otInt,

	// ������������
	otDouble,

	// ������
	otArray
};

//////////////////////////////////////////////////////////////////////////
// ������ - �������� ������������� ���� (��������������� ����������)

struct Object;

//////////////////////////////////////////////////////////////////////////
// ObjectArray - ������ �������� Object

struct ObjectArray
{
	// �������� �������
	Object *Data;

	// ���������� ��������� �������
	unsigned Count;
};

//////////////////////////////////////////////////////////////////////////
// ������ - �������� ������������� ����

struct Object
{
	// ��� �������
	ObjectType Type;

	union
	{
		// �������� ������ ����
		int Int;

		// �������� ������������� ����
		double Double;

		// �������� ���� "������"
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
		throw "������ ���������: �����. ��� �� ��������������.";
	}
}
//////////////////////////////////////////////////////////////////////////
// ��������� ���������
// {37F7727A-0174-4F2B-ADE9-271B949AA229}

static const GUID IID_ICollection = 
{ 0x37f7727a, 0x174, 0x4f2b, { 0xad, 0xe9, 0x27, 0x1b, 0x94, 0x9a, 0xa2, 0x29 } };

interface ICollection : public IUnknown
{
	// �������� ������� � ���������
	virtual HRESULT __stdcall Add(Object obj) = 0;

	// ������� ������� �� ���������
	virtual HRESULT __stdcall Remove(Object obj) = 0;

	// �������� ���������� ��������� ���������
	virtual HRESULT __stdcall GetCount(unsigned *count) = 0;

	// ������������� ��������� � ������
	virtual HRESULT __stdcall ToArray(ObjectArray **arr) = 0;
};


//////////////////////////////////////////////////////////////////////////
// ��������� �������������
// {7BAAB13D-AC13-484C-A1A0-132B28136425}

static const GUID IID_IEnumerator = 
{ 0x7baab13d, 0xac13, 0x484c, { 0xa1, 0xa0, 0x13, 0x2b, 0x28, 0x13, 0x64, 0x25 } };

interface IEnumerator : public IUnknown
{
	// ������� � �������� ���������
	virtual HRESULT __stdcall Reset() = 0;

	// ������� � ���������� ��������
	virtual HRESULT __stdcall MoveNext(unsigned int *result) = 0;

	// �������� ������� �������
	virtual HRESULT __stdcall GetCurrent(Object *obj) = 0;
};

// {A324528D-8BB8-43E2-90BA-7C972A084FA1}
static const CLSID CLSID_CLIST = { 0xa324528d, 0x8bb8, 0x43e2, { 0x90, 0xba, 0x7c, 0x97, 0x2a, 0x8, 0x4f, 0xa1 } };


