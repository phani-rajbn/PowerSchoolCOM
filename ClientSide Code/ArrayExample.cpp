#include"..//SampleCOM/SampleCOM_i.h"//ATL will generate the IDL Header file as _i.h file....
#include"..//SampleCOM/SampleCOM_i.c"
#include<iostream>
using namespace std;

int main() {
	CoInitialize(NULL);
	ILateBindingObject* ptr = NULL;
	HRESULT hr = ::CoCreateInstance(CLSID_LateBindingObject, NULL, CLSCTX_INPROC_SERVER, IID_ILateBindingObject, (void**)& ptr);
	if (FAILED(hr)) {
		return 0;
	}
	SAFEARRAY* pSA = NULL;
	SAFEARRAYBOUND bound[1];//Single dimensional Array..
	bound[0].cElements = 10;
	bound[0].lLbound = 0;

	pSA = SafeArrayCreate(VT_I4, 1, bound);//Create the Array//

	for (long i = 0; i < bound[0].cElements; i++) {
		SafeArrayPutElement(pSA, &i, &i);//Set the values inside the Array....
	}
	VARIANTARG arg;
	VariantInit(&arg);//Initialize the arg...
	arg.vt = VT_ARRAY | VT_I4;//Define the type...
	arg.parray = pSA;//set the value...
	long rs = 0;
	ptr->AddNumbers(arg, &rs);
	cout << "The result is " << rs << endl;
	ptr->Release();
	SafeArrayDestroy(pSA);
	CoUninitialize();
}
