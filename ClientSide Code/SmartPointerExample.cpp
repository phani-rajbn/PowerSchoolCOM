#import "C:\Users\phani\OneDrive\Desktop\SampleComDll.tlb"
using namespace SampleComDllLib;
#include<iostream>
using namespace std;
int main() {
	CoInitialize(NULL);
	IAddComponentPtr ptr(__uuidof(MathComponent));
	int res = 0;
	ptr->AddFunc(123, 23, &res);
	cout << "THe Added value: " << res << endl;
}