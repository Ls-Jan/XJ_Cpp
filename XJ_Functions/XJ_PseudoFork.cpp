

#include"XJ_PseudoFork.h"
#include"XJ_Pipe.h"
#include<stdio.h>

DWORD XJ_PseudoFork::Fork_Start(ProcData* data, LPCWSTR argv, PHANDLE hin, PHANDLE hout) {
	if (data == nullptr)
		return FALSE;
	LPCWSTR cmd = GetCommandLineW();
	if (data->__info__.argvLst == nullptr) {
		int count = 0;
		int pass = 0;
		LPWSTR* lst = CommandLineToArgvW(cmd, &count);//获取本进程的命令行信息
		LPWSTR argv = lst[count - 1];//获取末位参数。该参数形如：X%aaa。原本应该是有双引号的，被“优化”了，真的神烦这种小动作，上古API各种搞事挖坑
		if (count > 1) {
			for (LPWSTR p = argv; *p != 0; ++p) {//找到第一个百分号并进行记录，X为深度，aaa为父进程调用Fork_Start时额外传入的数据
				if (*p == '%') {
					int len = lstrlenW(p);//计算剩余长度
					LPWSTR tmp = new WCHAR[len];
					memcpy(tmp, p + 1, sizeof(WCHAR) * len);
					tmp[len - 1] = 0;
					data->argv = tmp;
					break;
				}
				pass = pass * 10 + (*p - '0');
			}
		}
		data->__info__.argvLst = lst;
		if (data->__info__.argc == 0) {
			data->__info__.argc = count;
			data->__info__.pass = pass;
			data->__info__.count = pass;
		}
	}
	if (data->__info__.count > 0) {
		--data->__info__.count;
		return FALSE;
	}
	data->__info__.pass += 1;
	WCHAR cmdLine[BUFSIZ] = L"";
	memset(cmdLine, 0, sizeof(cmdLine));
	swprintf_s(cmdLine, L"%s \"%d%%%s\"", cmd, data->__info__.pass, argv);//命令格式为：cmd "X%aaa"
	return XJ_Pipe::Proc_Create(cmdLine, hin, hout);
}

BOOL XJ_PseudoFork::Fork_Clear(ProcData* data) {
	if (data == nullptr)
		return FALSE;
	if (data->__info__.argvLst == nullptr)
		return FALSE;
	LocalFree(data->__info__.argvLst);
	if (data->argv != nullptr)
		delete[] data->argv;
	data->__info__.argvLst = nullptr;
	data->argv = nullptr;
	return TRUE;
}

