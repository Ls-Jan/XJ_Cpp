#include"XJ_Other.h"
#include<stdio.h>

LPWSTR XJ_Other::GetClipboardText(HWND hwnd) {
	//windows剪贴板数据：https://blog.csdn.net/yoryky/article/details/109118588
	//CF_宏：https://learn.microsoft.com/zh-cn/windows/win32/dataxchg/standard-clipboard-formats#constants
	LPWSTR rst = nullptr;
	OpenClipboard(hwnd);
	if (IsClipboardFormatAvailable(CF_UNICODETEXT)) {
		HANDLE h = GetClipboardData(CF_UNICODETEXT);//获取剪切板数据
		void* tx = GlobalLock(h);
		if (tx) {
			int len = lstrlenW((LPCWSTR)tx);
			if (len > 0) {
				len += 1;
				rst = new wchar_t[len];
				if (rst != nullptr) {
					memcpy_s(rst, len, tx, len);
				}
			}
		}
		GlobalUnlock(h);
		CloseClipboard();
	}
	return rst;
}

void XJ_Other::RedirectPrint(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);//va_start的第二参数必须是紧跟在省略号前面的参数，它是用来抓参数栈的地址的

	const int sz = BUFSIZ;
	char buf[sz] = "";
	vsprintf_s(buf, fmt, args);
	WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, max(sz, 1 + strnlen_s(buf, sz)), NULL, NULL);

	va_end(args);//还是尽量调用这个函数吧，作为一种规范
}
