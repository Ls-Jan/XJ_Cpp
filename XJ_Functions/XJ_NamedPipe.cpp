
#include"XJ_NamedPipe.h"


HANDLE XJ_NamedPipe::NPipe_Create(LPCCH name, DWORD size, BOOL congestion) {//创建命名管道
	CHAR pipeName[1024] = "//./Pipe/";
	strcat_s(pipeName, name);
	HANDLE pipe = CreateNamedPipeA(//管道创建时自带“非阻塞的等待连接”
		pipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		size,
		size,
		NMPWAIT_USE_DEFAULT_WAIT,
		0);
	if (pipe == INVALID_HANDLE_VALUE)//句柄值无效
		return NULL;
	if (congestion)
		ConnectNamedPipe(pipe, NULL);//进入阻塞状态，强制等待直到被连接
	return pipe;
}

HANDLE XJ_NamedPipe::NPipe_Link(LPCCH name, BOOL congestion) {//连接命名管道(congestion为真时会进入阻塞状态直到被连接)
	CHAR pipeName[1024] = "//./Pipe/";
	strcat_s(pipeName, name);

	if (congestion) {
		while (!WaitNamedPipeA(pipeName, NMPWAIT_WAIT_FOREVER)) {//等待管道可用
			if (GetLastError() == ERROR_FILE_NOT_FOUND) {//如果管道不存在，那就等会儿继续
				Sleep(150);
				continue;
			}
			else//其余不明情况直接pass
				break;
		}
	}

	HANDLE pipe = CreateFileA(
		pipeName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (pipe == INVALID_HANDLE_VALUE)//句柄值无效
		pipe = NULL;
	return pipe;
}

BOOL XJ_NamedPipe::NPipe_Write(HANDLE pipe, LPCVOID msg, DWORD size) {//向命名管道发送数据
	DWORD len_msg = size;
	DWORD len_pipe = 0;
	while (len_msg > 0) {
		if (!WriteFile(pipe, msg, len_msg, &len_pipe, NULL))
			return FALSE;
		msg = (BYTE*)msg + len_pipe;//调整指针位置
		len_msg -= len_pipe;//剩余的字节个数
	}
	return TRUE;
}

DWORD XJ_NamedPipe::NPipe_Read(HANDLE pipe, LPVOID msg, DWORD size) {//从命名管道获取数据
	DWORD len_msg = size;
	DWORD len_pipe = 0;
	DWORD len_read = 0;
	while (len_msg > 0) {
		if (!PeekNamedPipe(pipe, msg, NULL, NULL, &len_pipe, NULL) || len_pipe == 0)//判空
			break;
		if (!ReadFile(pipe, msg, min(len_pipe, len_msg), &len_pipe, NULL)) //读取数据
			break;
		msg = (BYTE*)msg + len_pipe;//调整指针位置
		len_read += len_pipe;
		len_msg -= len_pipe;//剩余的字节个数
	}
	return len_read;
}

VOID XJ_NamedPipe::NPipe_Close(HANDLE pipe) {//关闭命名管道
	DisconnectNamedPipe(pipe);//关闭管道
	CloseHandle(pipe);//关闭句柄
}

