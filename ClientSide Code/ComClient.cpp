#include"../SampleComDll/SampleComDll_h.h"
#include"../SampleComDll/SampleComDll_i.c"
//Include the MIDL generated Header and .C files which contain the C, C++ defns for IIDs and interfaces....

#include<iostream>
#include "ComClient.h"
using namespace std;

void coCreateInstance()
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr)) {
		cout << "Failed to load COM library...\nUpgrade to Windows NT" << endl;
		return 0;
	}
	IAddComponent* pAdd = NULL;
	hr = ::CoCreateInstance(CLSID_MathComponent, NULL, CLSCTX_INPROC_SERVER, IID_IAddComponent, reinterpret_cast<void**> (&pAdd));
	if (FAILED(hr)) {
		cout << "CoCreateInstance failed" << endl;
		return 0;
	}
	int result = 0;
	pAdd->AddFunc(123, 234, &result);
	cout << "The Added value: " << result << endl;

	ISubComponent* pSub = NULL;
	pAdd->QueryInterface(IID_ISubComponent, (void**)& pSub);
	pAdd->Release();//Dont forget this.....

	pSub->SubFunc(123, 23, &result);
	cout << "The Subtracted value: " << result << endl;
	result = pSub->Release();
	if (result == 0) {
		cout << "Object deleted from the memory" << endl;
	}
	CoUninitialize();
}

void createMultipleCOMobjects() {
	HRESULT hr = CoInitialize(NULL);
	IClassFactory* pFact = NULL;
	hr = ::CoGetClassObject(CLSID_MathComponent, CLSCTX_INPROC_SERVER, NULL, IID_IClassFactory, (void**)& pFact);

	if (FAILED(hr)) {
		cout << "OOPS!!!" << endl;
		return;
	}
	IAddComponent* pAdd = NULL;
	int res = 0;
	pFact->CreateInstance(NULL, IID_IAddComponent, (void**)& pAdd);
	pAdd->AddFunc(123, 234, &res);
	cout << "RES: " << res << endl;
	pFact->Release();
	pAdd->Release();
}
int main() {
	//coCreateInstance();
	createMultipleCOMobjects();
	return 0;
}

