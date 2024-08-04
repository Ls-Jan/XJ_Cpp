#pragma once


#include<Windows.h>

namespace XJ_Other {
	//获取剪切板的文本内容(UTF-16LE)。
	//返回的字串指针务必调用delete[]进行释放。
	LPWSTR GetClipboardText(HWND hwnd = NULL);
	//具有重定向效果的打印函数，作为printf_s的高级平替。
	//调用SetStdHandle即可重定向输出。
	VOID RedirectPrint(const char* fmt, ...);
};

