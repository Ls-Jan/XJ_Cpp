
#include"XJ_String.h"

int XJ_String::ConvertToA(LPCWSTR source, LPSTR destination, INT codePage, int unitCountSource, int unitCountDestination) {
	//WideCharToMultiByte用法：https://www.cnblogs.com/vranger/p/3793123.html
	//WideCharToMultiByte：https://learn.microsoft.com/zh-cn/windows/win32/api/stringapiset/nf-stringapiset-widechartomultibyte
	if (source == nullptr)
		return 0;
	if (destination == nullptr)
		unitCountDestination = 0;//必须得是0才行？这API当时到底是怎么设计的？
	if (unitCountDestination < 0)
		unitCountDestination = unsigned int(-1) >> 1;
	return WideCharToMultiByte(codePage, NULL, source, unitCountSource, destination, unitCountDestination, NULL, NULL);
}

int XJ_String::ConvertToW(LPCSTR source, LPWSTR destination, INT codePage, int unitCountSource, int unitCountDestination) {
	//MultiByteToWideChar用法：https://www.cnblogs.com/vranger/p/3793205.html
	//MultiByteToWideChar：https://learn.microsoft.com/zh-cn/windows/win32/api/stringapiset/nf-stringapiset-multibytetowidechar
	if (source == nullptr)
		return 0;
	if (destination == nullptr)
		unitCountDestination = 0;
	if (unitCountDestination < 0)
		unitCountDestination = unsigned int(-1) >> 2;//垃圾API到处埋雷
	return MultiByteToWideChar(codePage, NULL, source, unitCountSource, destination, unitCountDestination);
}

int XJ_String::ConvertStr(LPCSTR source, LPSTR destination, INT codePageSource, INT codePageDestination, int unitCountSource, int unitCountDestination) {
	if (source == nullptr)
		return 0;
	int szW = XJ_String::ConvertToW(source, nullptr, codePageSource, unitCountSource);
	if (szW <= 0)
		return 0;
	WCHAR* txW = new WCHAR[szW];
	XJ_String::ConvertToW(source, txW, codePageSource, unitCountSource);
	int szA = XJ_String::ConvertToA(txW, destination, codePageDestination, -1, unitCountDestination);
	delete[]txW;
	return szA;
}

