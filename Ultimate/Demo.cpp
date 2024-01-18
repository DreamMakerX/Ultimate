#include "Ultimate.h"
#include <iostream>

void PrintSeparate()
{
	std::cout << "==============================Separate==============================" << std::endl;
}
void GetTime()
{
	//获取当前时间
	std::cout << "获取当前时间: " << GetStringTime().c_str() << std::endl;
	//获取1900年1月1日至今的秒数
	std::cout << "获取1900年1月1日至今的秒数: " << GetTimeStamp1900() << std::endl;
	//获取1970年1月1日至今的秒数
	std::cout << "获取1970年1月1日至今的秒数: " << GetTimeStamp1970() << std::endl;
	PrintSeparate();
}
void GetSplitString()
{
	std::string target = "name,age,skills";

	//字符串分割，保存至vector
	std::vector<std::string> resultVec;
	SplitString(target, resultVec, ",");
	std::cout << "字符串分割，保存至vector（\"name,age,skills\"）: " << std::endl;
	for (auto item : resultVec)
	{
		std::cout << item << std::endl;
	}

	//字符串分割，保存至unordered_set
	std::unordered_set<std::string> resultSet;
	SplitString(target, resultSet, ",");
	std::cout << "字符串分割，保存至unordered_set（\"name,age,skills\"）: " << std::endl;
	for (auto item : resultSet)
	{
		std::cout << item << std::endl;
	}

	//去除首尾目标字符
	std::cout << "去除首尾目标字符(\",Var1,\", \",\"): " << TrimSpecialChar(",Var1,", ",").c_str() << std::endl;
	//去除首尾目标字符,无目标字符，默认去除\t\n,.;:?!'\"+-*/=_<>()[]{}\\~@#$%^&
	std::cout << "去除首尾目标字符,不传入目标字符(\"#Var1@\"): " << TrimSpecialChar("#Var1@").c_str() << std::endl;
	
	//字符串转小写
	std::cout << "字符串转小写(\"TrUe\"): " << GetLowercase("TrUe").c_str() << std::endl;
	//字符串转大写
	std::cout << "字符串转大写(\"TrUe\"): " << GetUppercase("TrUe").c_str() << std::endl;

	PrintSeparate();
}
void Base64Encode()
{
	//byte数组转base64，为便于展示以字符串为例
	std::string str = "hello world!";
	std::string strBase64 = EncodeBinaryToBase64(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
	std::cout << str.c_str() << " -> byte数组转base64结果: " << strBase64.c_str() << std::endl;
	
	//base64转byte数组
	std::vector<unsigned char> rsp = DecodeBase64ToBinary(strBase64);
	std::string strBinary(rsp.begin(), rsp.end());
	std::cout << strBase64.c_str() << " -> base64转byte数组结果: " << strBinary.c_str() << std::endl;
	
	PrintSeparate();
}
void OperateFile()
{
	//写入文件
	std::string contentWrite = "在C++中，显式类型转换是一种由程序员明确指定的类型转换操作。";
	WriteFile("fileExample.txt", contentWrite.c_str(), contentWrite.length());
	std::cout << "写入文件: " << "WriteFile success" << std::endl;

	//读取文件
	std::vector<unsigned char> rsp = ReadFile("fileExample.txt");
	std::string contentRead(rsp.begin(), rsp.end());
	std::cout << "读取文件: " << contentRead.c_str() << std::endl;
	PrintSeparate();
}
void JudgeNumber()
{
	//判断字符串是否为数字
	std::cout << "判断字符串是否为数字(\"true\"): " << IsNumber("true") << std::endl;
	std::cout << "判断字符串是否为数字(\"zcc\"): " << IsNumber("zcc") << std::endl;
	std::cout << "判断字符串是否为数字(\"24zcc\"): " << IsNumber("24zcc") << std::endl;
	std::cout << "判断字符串是否为数字(\"zcc16\"): " << IsNumber("zcc16") << std::endl;
	std::cout << "判断字符串是否为数字(\"36.6\"): " << IsNumber("36.6") << std::endl;
	std::cout << "判断字符串是否为数字(\"101\"): " << IsNumber("101") << std::endl;

	PrintSeparate();
}
void ConvertType()
{
	//数据类型转换，支持string转数值，数值转字符串
	std::cout << "数据类型转换,数值转字符串(12): " << DataTypeConvert(12).c_str() << std::endl;
	std::cout << "数据类型转换,数值转字符串(76.4): " << DataTypeConvert(76.4).c_str() << std::endl;
	std::cout << "数据类型转换,字符串转double(\"64.3\"): " << DataTypeConvert<double>("64.3") << std::endl;
	std::cout << "数据类型转换,字符串转bool(\"True\"): " << DataTypeConvert<bool>("True") << std::endl;

	PrintSeparate();
}

void main()
{
	GetTime();

	GetSplitString();

	Base64Encode();

	OperateFile();

	JudgeNumber();

	ConvertType();

	std::cin.get();
}