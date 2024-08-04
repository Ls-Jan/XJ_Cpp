#pragma once

#include<Windows.h>

//伪fork，行为参考了Linux的fork函数，本质是利用子进程创建手段以实现fork效果。
//使得一份代码就可以进行多进程测试，项目的管理变得更加的轻松，可喜可贺。
//再强调一点，这不是真fork，因为子进程会从头执行代码而不是像fork那样将父进程进行拷贝。
namespace XJ_PseudoFork {
	//ProcData记录的是当前进程相关信息，而不是子进程的。
	//不应该创建多个ProcData对象，其实本来应该弄成单例类的，但想想算了不想搞全局量。
	//对象创建时务必后接空花括号或者使用memset之类的函数以便将数据置零。
	struct ProcData {
		struct {
			char pass;//需要跳过的Fork次数，每成功创建一个子进程该值都会加1
			char count;//每次调用Fork_Start该值都会减1直至为0，用于跳过前depth个子进程创建行为。当该值为0时再调用Fork_Start时将会创建新的子进程
			int argc;//命令行参数个数
			LPWSTR* argvLst;//命令行参数列表，该数据可能为nullptr
		}__info__;
		LPCWSTR argv;//父进程调用Fork_Start创建时传入的额外参数，该数据可能为nullptr
	};

	//创建子进程，可选择向子进程传递额外参数，并能对子进程进行重定向输入输出。
	//成功创建则会返回子进程的pid。
	DWORD Fork_Start(ProcData* data, LPCWSTR argv=L"", PHANDLE hin = nullptr, PHANDLE hout = nullptr);
	//清理ProcData数据。清理后的data->argv和data->__info__.argvLst数据不可用
	BOOL Fork_Clear(ProcData* data);
}

