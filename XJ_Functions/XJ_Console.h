#pragma once
#include<Windows.h>


//一些与控制台相关的操作
namespace XJ_Console {
	//将字节流以十六进制进行输出，
	//如果连遇0值的个数为zeroCount则结束输出。
	//可以指定byteCount以限制读取的字节个数。
	void PrintBytes(const void* data, unsigned zeroCount = 2,unsigned byteCount=INFINITE);
	//获取控制台屏幕缓冲区信息并以十六进制进行输出；
	//pos和size屏幕缓冲区的位置；
	void PrintScreenBuffer(COORD pos, COORD size = COORD{ 10,10 });
	//获取控制台屏幕光标位置
	COORD GetCursorPos();
	//重置stdout，使printf_s和std::cout重定向到当前控制台窗口
	void ResetStdout();

	//其他：
	//控制台虚拟终端序列(实现光标移动等)：https://learn.microsoft.com/zh-cn/windows/console/console-virtual-terminal-sequences
}







