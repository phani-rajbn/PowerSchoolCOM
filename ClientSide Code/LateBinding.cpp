#include<Windows.h>
#include<iostream>
#include <cstringt.h>
using namespace std;

int main() {
	HRESULT hr = ::CoInitialize(NULL);
	BSTR strName;
	strName = SysAllocString(L"SampleCOM.LateBindingObject");
	CLSID clsID;
	hr = CLSIDFromProgID(strName, &clsID);
	if (FAILED(hr)) {
		cout << "Failed to get the CLSID from ProgID" << endl;
		return 0;
	}
	IDispatch* ptr = NULL;
	hr = ::CoCreateInstance(clsID, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&ptr);
	if (FAILED(hr)) {
		cout << "CoCreateInstance failed" << endl;
		return 0;
	}
	BSTR strMethodName = SysAllocString(L"SquareRoot");
	DISPID diid;
	hr = ptr->GetIDsOfNames(IID_NULL, &strMethodName, 1, LOCALE_USER_DEFAULT, &diid);
	if (FAILED(hr)) {
		cout << "No ID found for this method, method name is wrong!!!!" << endl;
		return 0;
	}

	cout << "The DISPID is " << diid << endl;
	short res = 0;
	VARIANTARG* pArgs = new VARIANTARG[2];
	for (int i = 0; i < 2; i++) 
		VariantInit(&pArgs[i]);//
	pArgs[0].vt = VT_I4 | VT_BYREF;
	pArgs[0].piVal = &res;
	pArgs[1].vt = VT_I4;
	pArgs[1].iVal = 12;

	DISPPARAMS params;
	params.cArgs = 2;
	params.cNamedArgs = 0;
	params.rgdispidNamedArgs = NULL;
	params.rgvarg = pArgs;

	hr = ptr->Invoke(diid, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, NULL, NULL, NULL);
	if (FAILED(hr)) {
		cout << "Failed to invoke the method" << endl;
		return 0;
	}
	cout << "The result: " << res << endl;
	CoUninitialize();
}