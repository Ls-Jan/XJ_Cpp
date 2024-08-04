#pragma once

#include<io.h>
//用于指定目录的遍历，关键数据结构为_wfinddata_t，相关的宏是_A_XXX
// C++遍历目录：https://blog.csdn.net/siyacaodeai/article/details/112732678
namespace XJ_EnumFile {
	struct FileData :_wfinddata_t {
		int __valid__;//命名空间被各种污染，很多单双下划线起头的名称都已经被宏给占用，太搞了
		intptr_t __handle__;
	};

	//开始遍历
	bool EnumFile_Start(FileData* data, const wchar_t* path);
	//判断FileData是否有效
	bool EnumFile_Valid(FileData* data);
	//遍历下一个
	bool EnumFile_Next(FileData* data);
	//结束遍历
	bool EnumFile_End(FileData* data);
};

