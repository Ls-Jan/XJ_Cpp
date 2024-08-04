#pragma once


#include<Windows.h>

//匿名管道的创建，
//因为其通常用于子进程的创建，同时将子进程创建代码也放入其中
//https://learn.microsoft.com/zh-cn/windows/win32/procthread/creating-a-child-process-with-redirected-input-and-output
namespace XJ_Pipe {
	//创建单向匿名管道，一个输入一个输出
	BOOL Pipe_Create(PHANDLE phWr,PHANDLE phRd);
	//创建子进程，对应参数若不为空则会对子进程进行输入输出的重定向。
	//使用W子串是因为极大可能会出现Unicode独有字符，使用A字串则必然出现乱码从而无法准确运行。
	//成功创建则会返回子进程的pid
	DWORD Proc_Create(LPWSTR cmdLine,PHANDLE phin,PHANDLE phout);
}


