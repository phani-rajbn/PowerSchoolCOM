#include<iostream>
#include<objbase.h>
using namespace std;
#define IID_ISimple 101
#define IID_IExample 102
interface ICommon {
public:
	virtual void QueryInterface(UINT id, void** ppv) = 0;
	virtual int AddReference() =0;
	virtual int ReleaseReference() = 0;
};
interface ISimple :public ICommon {
public:
	virtual void SimpleFunc() = 0;//Pure virtual function....
};

interface IExample :public ICommon {
public:
	virtual void ExampleFunc() = 0;
};

class SimpleExample : public ISimple, public IExample {
private:
	int m_nValue;
	int m_nRefCount;
public:
	SimpleExample() : m_nValue(0), m_nRefCount(0)
	{
		cout << "The object is created" << endl;
	}
	virtual void SimpleFunc() {
		m_nValue = 123;
		cout << "Simple Function is invoked" << endl;
	}

	virtual void ExampleFunc() {
		cout << "The Value is " << m_nValue << endl;
		cout << "Example Function is invoked" << endl;
	}

	/////////////////ICommon methods////////////////
	virtual void QueryInterface(UINT id, void** ppv) {
		if (id == IID_ISimple)
			* ppv = (ISimple*)this;
		else if (id == IID_IExample)
			* ppv = (IExample*)this;
		else
			throw "Not a Valid interface";
		((ISimple*)*ppv)->AddReference();
	}

	virtual int AddReference() {
		m_nRefCount++;
		return m_nRefCount;
	}

	virtual int ReleaseReference() {
		--m_nRefCount;
		if (m_nRefCount == 0) {
			delete this;
			return 0;
		}
		return m_nRefCount;
	}
};

void CreateInstance(UINT id, void** ppV) {
	SimpleExample* pSimEx = new SimpleExample;
	pSimEx->QueryInterface(id, ppV);
}

int main() {
	ISimple* pSimple = NULL;
	CreateInstance(IID_ISimple, (void**)& pSimple);
	pSimple->SimpleFunc();

	////U R Creating a new Object everytime...
	IExample* pEx = NULL;
	pSimple->QueryInterface(IID_IExample, (void**)& pEx);
	pSimple->ReleaseReference();
	//CreateInstance(IID_IExample, (void**)&pEx);
	pEx->ExampleFunc();
	int count = pEx->ReleaseReference();
	if (count == 0) cout << "Object is deleted successfully" << endl;
	return 0;
}