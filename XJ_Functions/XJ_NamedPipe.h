#pragma once
#include<Windows.h>

//阻塞型半双工命名管道
//阻塞型：写入/读取时缓冲区不足的话将会被阻塞等待
//半双工：客户端/服务端可随意指定数据接收/发送方，但在确定后无法调换
namespace XJ_NamedPipe {
	//创建命名管道。
	//name为管道名；
	//size为缓存大小；
	//congestion为真时会进入阻塞状态直到被连接，该值为FALSE会为程序带来较大的不确定性；
	HANDLE NPipe_Create(LPCCH name, DWORD size, BOOL congestion = TRUE);
	//连接命名管道。
	//name为管道名；
	//congestion为真时会进入阻塞状态直到被连接；
	HANDLE NPipe_Link(LPCCH name, BOOL congestion = TRUE);
	//向命名管道发送数据，实际就是调用WriteFile。
	//pipe为管道句柄；
	//msg为要发送的字节流；
	//size为发送的字节个数；
	BOOL NPipe_Write(HANDLE pipe, LPCVOID msg, DWORD size);
	//从命名管道获取数据，实际就是调用ReadFile。
	//pipe为管道句柄；
	//msg为缓冲区；
	//size为最大字节读取个数，通常设置为msg大小；
	DWORD NPipe_Read(HANDLE pipe, LPVOID msg, DWORD size);
	//关闭命名管道
	//pipe为管道句柄；
	VOID NPipe_Close(HANDLE pipe);
}







