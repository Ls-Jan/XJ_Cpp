
#include"XJ_Test.h"
#include<XJ_Functions/XJ_Pipe.h>
#include<XJ_Functions/XJ_Console.h>
#include<XJ_Functions/XJ_PseudoFork.h>

#include<locale>

void XJ_Test::EnumFile(const wchar_t* path) {
	setlocale(LC_ALL, ".ACP");
	XJ_EnumFile::FileData data;
	for (XJ_EnumFile::EnumFile_Start(&data, path); XJ_EnumFile::EnumFile_Valid(&data); XJ_EnumFile::EnumFile_Next(&data)) {
		if (data.attrib & _A_SUBDIR)
			wprintf_s(L"<%s>\n", data.name);
		else
			//wprintf_s(L"<%s(%fKB)>\n", data.name, 33);
			wprintf_s(L"<%s(%.2fKB)>\n", data.name, data.size / 1024.0);
		wchar_t buffer[32];
		_wctime_s(buffer, _countof(buffer), &data.time_write);
		wprintf_s(L"timeM:%s", buffer);
		printf_s("\n");
	}
}


void XJ_Test::PseudoFork(const char*tx) {
	HANDLE hin;
	HANDLE hout;
	XJ_PseudoFork::ProcData data{};

	//使用Fork_Start，并将子进程的输入输出重定向至管道hin和hout中
	DWORD pid = XJ_PseudoFork::Fork_Start(&data, L"", &hin, &hout);
	if (pid) {//主进程
		DWORD dwRead;
		CHAR chBuf[BUFSIZ] = "";

		while (true) {
			if (!ReadFile(hout, chBuf, BUFSIZ, &dwRead, NULL) || dwRead == 0)
				break;
			for (auto i = 0; chBuf[i]; ++i)//输出十六进制
				printf_s("%02X ", (unsigned char)chBuf[i]);
		}
		printf_s("\n");
	}
	else {//子进程
		printf_s(tx);//UTF-8编码依次是 E5A3B9 E8B4B0 E58F81
	}

	XJ_PseudoFork::Fork_Clear(&data);//清理数据
}



