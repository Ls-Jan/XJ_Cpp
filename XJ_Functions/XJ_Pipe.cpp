
#include"XJ_Pipe.h"

BOOL XJ_Pipe::Pipe_Create(PHANDLE phWr, PHANDLE phRd) {
	if (phWr == nullptr || phRd == nullptr)
		return FALSE;
	SECURITY_ATTRIBUTES saAttr;
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;
	return CreatePipe(phRd, phWr, &saAttr, 0);
}

DWORD XJ_Pipe::Proc_Create(LPWSTR cmdLine, PHANDLE phin, PHANDLE phout) {
	HANDLE hin_Wr = NULL;
	HANDLE hin_Rd = NULL;
	HANDLE hout_Wr = NULL;
	HANDLE hout_Rd = NULL;
	//hin_Wr和hout_Rd是给主进程使用的
	//hin_Rd和hout_Wr给子进程使用
	if (phin != NULL) {
		XJ_Pipe::Pipe_Create(&hin_Wr, &hin_Rd);
		*phin = hin_Wr;
		SetHandleInformation(hin_Wr, HANDLE_FLAG_INHERIT, 0);
	}
	if (phout != NULL) {
		XJ_Pipe::Pipe_Create(&hout_Wr, &hout_Rd);
		*phout = hout_Rd;
		SetHandleInformation(hout_Rd, HANDLE_FLAG_INHERIT, 0);
	}

	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));
	if (TRUE) {
		STARTUPINFOW si;
		BOOL bSuccess = FALSE;


		WCHAR title[32] = L"SubProcess";
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.hStdError = hout_Wr;
		si.hStdOutput = hout_Wr;
		si.hStdInput = hin_Rd;
		si.dwFlags |= STARTF_USESTDHANDLES;
		si.lpTitle = title;

		bSuccess = CreateProcessW(NULL,
			cmdLine,     // command line 
			NULL,          // process security attributes 
			NULL,          // primary thread security attributes 
			TRUE,          // handles are inherited 
			0,             // creation flags 
			NULL,          // use parent's environment 
			NULL,          // use parent's current directory 
			&si,  // STARTUPINFO pointer 
			&pi);  // receives PROCESS_INFORMATION 
		//printf_s("%d\n",bSuccess);
		 // If an error occurs, exit the application. 
		if (!bSuccess)
			return FALSE;
		else {
			// Close handles to the child process and its primary thread.
			// Some applications might keep these handles to monitor the status
			// of the child process, for example. 
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			// Close handles to the stdin and stdout pipes no longer needed by the child process.
			// If they are not explicitly closed, there is no way to recognize that the child process has ended.
			if (hin_Rd)
				CloseHandle(hin_Rd);
			if (hout_Wr)
				CloseHandle(hout_Wr);
		}
	}
	return 	pi.dwProcessId;
}



