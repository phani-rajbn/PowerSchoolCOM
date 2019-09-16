#pragma once
//include the MIDL generated header file and the .c file in UR Code...
#include"SampleComDll_h.h"
#include"SampleComDll_i.c"

void Msgbox(LPCWSTR strMessage) {
	MessageBox(NULL, strMessage, L"COM Programming", MB_OK);
}
//implement the COM Component...
class MathComponent : public IAddComponent, public ISubComponent {
private:
	ULONG m_lRefCount;
public:
	MathComponent() : m_lRefCount(0)
	{
		Msgbox(L"Com Object is created here");
	}
	//////////////////IUNknown methods//////////////////////////
	STDMETHOD(QueryInterface)(REFIID riid, void** ppv) {
		*ppv = NULL;
		if (riid == IID_IUnknown)
			* ppv = (IAddComponent*)this;
		else if (riid == IID_IAddComponent)
			* ppv = static_cast<IAddComponent*>(this);
		else if (riid == IID_ISubComponent)
			* ppv = static_cast<ISubComponent*>(this);
		else
			return E_NOINTERFACE;
		//U Call AddRef for every successfull QI.....
		((IAddComponent*)*ppv)->AddRef();
		return S_OK;
	}

	STDMETHOD_(ULONG, AddRef)() {
		//++m_lRefCount;
		return InterlockedIncrement(&m_lRefCount);
	}

	STDMETHOD_(ULONG, Release)() {
		ULONG ul = InterlockedDecrement(&m_lRefCount);
		if (ul == 0)
			delete this;
		return ul;
	}
	/////////////////////////Custom Methods//////////////////////
	virtual HRESULT __stdcall AddFunc(int iVal1, int iVal2, int* iRes) {
		*iRes = iVal1 + iVal2;
		return S_OK;//Everything is fine....
	}
	//STDMETHOD is a macro for HRESULT __stdcall virtual 
	STDMETHOD(SubFunc)(int iVal1, int iVal2, int* iRes) {
		*iRes = iVal1 - iVal2;
		return S_OK;//Everything is fine....
	}
};
///////////////////////////IClassFactory Component//////////////////////////////////////////
class CFactory : public IClassFactory {
	ULONG m_lRefCount;
public:
	CFactory() : m_lRefCount(0)
	{

	}
	//////////////////////////////////////IUnknown methods////////////////////////////////////
	STDMETHOD(QueryInterface)(REFIID riid, void** ppv) {
		*ppv = NULL;
		if ((riid == IID_IUnknown) || (riid == IID_IClassFactory))
			*ppv = (IClassFactory*)this;
		else
			return E_NOINTERFACE;
		//U Call AddRef for every successfull QI.....
		((IClassFactory*)* ppv)->AddRef();
		return S_OK;
	}

	STDMETHOD_(ULONG, AddRef)() {
		//++m_lRefCount;
		return InterlockedIncrement(&m_lRefCount);
	}

	STDMETHOD_(ULONG, Release)() {
		ULONG ul = InterlockedDecrement(&m_lRefCount);
		if (ul == 0)
			delete this;
		return ul;
	}
	//////////////////////////////IClassFactory methods//////////////////////////////////////////
	STDMETHOD(CreateInstance)(IUnknown* pOuter, REFIID riid, void** ppv) {
		if (pOuter != NULL)
			return CLASS_E_NOAGGREGATION;
		MathComponent* pCOM = new MathComponent();
		HRESULT hr =  pCOM->QueryInterface(riid, ppv);
		if (FAILED(hr)) {
			Msgbox(L"Create Instance failed for the Component");
			return hr;
		}
		return S_OK;
	}

	STDMETHOD(LockServer)(BOOL flock) {
		return S_OK;
	}
};
