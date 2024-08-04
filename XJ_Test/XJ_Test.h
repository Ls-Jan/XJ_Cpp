#pragma once

#include<XJ_Functions/XJ_EnumFile.h>


namespace XJ_Test {
	//测试文件的遍历，星号*作为通配符使用
	void EnumFile(const wchar_t* path=L"*");
	//使用XJ_PseudoFork创建子进程并重定向标准输入输出。
	//子进程将会执行printf_s(tx)；
	//主进程将会获取子进程的标准输出并以十六进制进行显示。
	void PseudoFork(const char* tx = "ABC");
};


