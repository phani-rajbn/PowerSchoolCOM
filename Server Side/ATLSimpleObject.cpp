// ATLSimpleObject.cpp : Implementation of CATLSimpleObject

#include "pch.h"
#include "ATLSimpleObject.h"


// CATLSimpleObject



STDMETHODIMP CATLSimpleObject::AddFunc(int iVal1, int iVal2, int* iRes)
{
	// TODO: Add your implementation code here
	*iRes = iVal1 + iVal2;
	return S_OK;
}
