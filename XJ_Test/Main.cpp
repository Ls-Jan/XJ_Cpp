
//本项目主要对XJ_Functions项目中的代码进行测试


#include"XJ_Test.h"

#include<windows.h>
#include<locale>
#include<stdio.h>
#include<vector>
#include"XJ_Functions/XJ_Pipe.h"
#include"XJ_Functions/XJ_Console.h"
#include"XJ_Functions/XJ_PseudoFork.h"



int wmain(int argc, wchar_t* argv[]) {
	XJ_Test::PseudoFork("壹贰叁");
	//XJ_Test::EnumFile();
	
	return 0;
}










