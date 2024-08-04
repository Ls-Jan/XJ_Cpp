
#include"XJ_EnumFile.h"


bool XJ_EnumFile::EnumFile_Start(FileData* data, const wchar_t* path) {
	data->__handle__ = _wfindfirst(path, data);
	data->__valid__ = data->__handle__ !=-1L;
	return data->__valid__;
}

bool XJ_EnumFile::EnumFile_Valid(FileData* data){
	return data->__valid__;
}

bool XJ_EnumFile::EnumFile_Next(FileData* data) {
	data->__valid__ = _wfindnext(data->__handle__, data)==0;
	return data->__valid__;
}

bool XJ_EnumFile::EnumFile_End(FileData* data) {
	_findclose(data->__handle__);
	return true;
}

