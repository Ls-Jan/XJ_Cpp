
#include"XJ_Console.h"
#include<stdio.h>

void XJ_Console::PrintScreenBuffer(COORD pos, COORD size) {//获取控制台屏幕缓冲区信息并以十六进制进行输出
	const COORD anchor{ max(pos.X - size.X + 1, 0), max(pos.Y - size.Y + 1, 0) };
	CHAR_INFO* chars = new CHAR_INFO[size.X * size.Y];
	if (chars) {
		SMALL_RECT rect{ anchor.X,anchor.Y,anchor.X + size.X,anchor.Y + size.Y };//LTRB
		//控制台屏幕缓冲区：https://learn.microsoft.com/zh-cn/windows/console/console-screen-buffers
		ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), chars, size, COORD{ 0,0 }, &rect);
		
		printf_s("\n\n\n");
		for (auto i = 0; i < size.X; ++i) {
			for (auto j = 0; j < size.Y; ++j) {
				auto ch = chars[size.X * i + j];
				//CHAR_INFO：https://learn.microsoft.com/zh-cn/windows/console/char-info-str
				printf_s("%02X ", (unsigned short)ch.Char.UnicodeChar);
			}
			printf_s("\n");
		}
		delete[] chars;
	}
}

void XJ_Console::PrintBytes(const void* data, unsigned zeroCount, unsigned byteCount){//将字节流以十六进制进行输出，如果连遇'\0'的个数为zeroCount则结束输出
	unsigned char* ptr = (unsigned char*)data;
	int zero = 0;
	while (byteCount-->0) {
		if (*ptr == 0) {
			++zero;
			printf_s("00 ");
			if (zero >= zeroCount)
				break;
		}
		else {
			zero = 0;
			printf_s("%02X ", *ptr);//输出十六进制数时需使用unsigned类型：https://zhidao.baidu.com/question/940585561985892092.html
		}
		ptr += 1;
	}
	printf_s("\n");
}

COORD XJ_Console::GetCursorPos() {//获取控制台屏幕光标位置
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hout, &info);//似乎调用该函数时可以不需要fflush清空输出缓冲区？少了麻烦太好了
	return info.dwCursorPosition;
}


void XJ_Console::ResetStdout() {
	//freopen_s的用法：https://zhidao.baidu.com/question/1674282524377571187.html
	FILE *tmp;
	freopen_s(&tmp,"CON", "w", stdout);
}


