#pragma once


#include<Windows.h>

//注意一下，A字串以1字节为单位，W字串则是2字节。
namespace XJ_String {
	//转换W字串至A字串，可以传入CodePage来指定转换的代码页(字符集)。
	//destination为空则仅计算转换后的A字串的长度；
	//unitCountDestination用于限制destination的长度，如果确保destination足够长那么该值可以赋值-1；
	//unitCountSource用于限制source的长度，如果确保source以NULL结尾那么该值可以赋值-1；
	int ConvertToA(LPCWSTR source, LPSTR destination = nullptr, INT codePage = CP_ACP, int  unitCountSource = -1, int  unitCountDestination = -1);
	//转换A字串至W字串，可以传入CodePage来指定转换的代码页(字符集)。
	//destination为空则仅计算转换后的W字串的长度；
	//unitCountDestination用于限制destination的长度，如果确保destination足够长那么该值可以赋值-1；
	//unitCountSource用于限制source的长度，如果确保source以NULL结尾那么该值可以赋值-1；
	int ConvertToW(LPCSTR source, LPWSTR destination = nullptr, INT codePage = CP_ACP, int unitCountSource = -1, int unitCountDestination = -1);
	//字符串编码转换，将一个以codePageSource为字符集的源字串source转换为字符集为codePageDestination的目标字串destination，
	//实际上就是以宽字符作为中间桥梁依次调用ConvertToW和ConvertToA转换字串罢了。
	//destination为空则仅计算转换后的字串的长度；
	//unitCountDestination用于限制destination的长度，如果确保destination足够长那么该值可以赋值-1；
	//unitCountSource用于限制source的长度，如果确保source以NULL结尾那么该值可以赋值-1；
	//codePageSource和codePageDestination分别指定source和destination的代码页；
	int ConvertStr(LPCSTR source, LPSTR destination, INT codePageSource, INT codePageDestination, int unitCountSource = -1, int unitCountDestination = -1);
};


