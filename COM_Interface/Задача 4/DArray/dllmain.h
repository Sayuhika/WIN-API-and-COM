// dllmain.h: объ€вление класса модул€.

class CDArrayModule : public ATL::CAtlDllModuleT< CDArrayModule >
{
public :
	DECLARE_LIBID(LIBID_DArrayLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DARRAY, "{5D08A397-8738-4EEA-A2DD-1FFC132D5984}")
};

extern class CDArrayModule _AtlModule;
