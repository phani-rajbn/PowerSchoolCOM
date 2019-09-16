// LateBindingObject.cpp : Implementation of CLateBindingObject

#include "pch.h"
#include "LateBindingObject.h"


// CLateBindingObject



STDMETHODIMP CLateBindingObject::SquareRoot(int no, int* iRes)
{
	// TODO: Add your implementation code here
	*iRes = no * no;
	return S_OK;
}


STDMETHODIMP CLateBindingObject::AddNumbers(VARIANT theArray, LONG* lSum)
{
	//SAFEARRAY is the data structure used to create and define arrays in COM. It is Array as Reference type, so its similar to .NET's Array concept...
	if ((theArray.vt & VT_I4) && (theArray.vt & VT_ARRAY)) {
		//Check if the data type is LONG and an Array and then continue.....
		SAFEARRAY* pSA;//create an object....
		pSA = theArray.parray;//get the Array passed as arg....
		long lBound, uBound;
		SafeArrayGetLBound(pSA, 1, &lBound);//get the lower bound of the Array....
		SafeArrayGetUBound(pSA, 1, &uBound);//get the upper bound of the Array....
		
		LONG result =0;
		long item = 0;
		for (long i = lBound; i <= uBound; i++)
		{
			SafeArrayGetElement(pSA, &i, &item);//get the value at the specific location...
			result += item;//Add the value into the result...
		}
		*lSum = result;//Set the value to the parameter....
		//SafeArrayDestroy(pSA);
	}
	else
		return E_ABORT;
	return S_OK;
}
