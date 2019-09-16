// dllmain.cpp : Defines the entry point for the DLL application.
#include"SampleComDll.h"

//Optional Entry point for a DLL..
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		Msgbox(L"Dll loaded into the memory of the Process");
		break;
    case DLL_PROCESS_DETACH:
		Msgbox(L"Dll Unloaded from the process");
        break;
    }
    return TRUE;
}
///Every COM DLL must implement a set of EXPORT Functions for COM library to call......
STDAPI DllGetClassObject(REFCLSID rClsID, REFIID riid, LPVOID* ppv) {
	//Create the  instance of the CFactory and call its QUeryinterface....
	if (rClsID != CLSID_MathComponent) {
		return CLASS_E_CLASSNOTAVAILABLE;
	}
	CFactory* pFact = new CFactory();
	return pFact->QueryInterface(riid, ppv);

}

//Will go ahead with Manual Registeration, as usually COM registration is done thro ATL......
STDAPI DllRegisterServer() {
	return S_OK;
}
STDAPI DllUnregisterServer() {
	return S_OK;
}

STDAPI DllCanUnloadNow() {
	return S_OK;
}
