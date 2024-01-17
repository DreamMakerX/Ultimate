#include "Ultimate.h"
#include <iostream>

void PrintSeparate()
{
	std::cout << "==============================Separate==============================" << std::endl;
}
void GetTime()
{
	//获取当前时间
	std::cout << "GetStringTime: " << GetStringTime().c_str() << std::endl;
	//获取1900年1月1日至今的秒数
	std::cout << "GetTimeStamp1900: " << GetTimeStamp1900() << std::endl;
	//获取1970年1月1日至今的秒数
	std::cout << "GetTimeStamp1970: " << GetTimeStamp1970() << std::endl;
	PrintSeparate();
}
void GetSplitString()
{
	std::string target = "name,age,skills";

	//字符串分割，保存至vector
	std::vector<std::string> resultVec;
	SplitString(target, resultVec, ",");

	//字符串分割，保存至unordered_set
	std::unordered_set<std::string> resultSet;
	SplitString(target, resultSet, ",");
	std::cout << "SplitString(vector): " << std::endl;
	for (auto item : resultVec)
	{
		std::cout << item << std::endl;
	}
	std::cout << "SplitString(unordered_set): " << std::endl;
	for (auto item : resultSet)
	{
		std::cout << item << std::endl;
	}
	//字符串转小写
	std::cout << "GetLowercase(\"TrUe\"): " << GetLowercase("TrUe").c_str() << std::endl;
	//字符串转大写
	std::cout << "GetUppercase(\"TrUe\"): " << GetUppercase("TrUe").c_str() << std::endl;

	PrintSeparate();
}
void Base64Encode()
{
	//byte数组转base64，为便于展示以字符串为例
	std::string str = "hello world!";
	std::string strBase64 = EncodeBinaryToBase64(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
	std::cout << str.c_str() << " -> EncodeBinaryToBase64 result: " << strBase64.c_str() << std::endl;
	
	//base64转byte数组
	std::vector<unsigned char> rsp = DecodeBase64ToBinary(strBase64);
	std::string strBinary(rsp.begin(), rsp.end());
	std::cout << strBase64.c_str() << " -> DecodeBase64ToBinary result: " << strBinary.c_str() << std::endl;
	
	PrintSeparate();
}
void OperateFile()
{
	//写入文件
	std::string contentWrite = "在C++中，显式类型转换是一种由程序员明确指定的类型转换操作。";
	WriteFile("fileExample.txt", contentWrite.c_str(), contentWrite.length());
	std::cout << "WriteFile success" << std::endl;

	//读取文件
	std::vector<unsigned char> rsp = ReadFile("fileExample.txt");
	std::string contentRead(rsp.begin(), rsp.end());
	std::cout << "ReadFile: " << contentRead.c_str() << std::endl;
	PrintSeparate();
}
void JudgeNumber()
{
	//判断字符串是否为数字
	std::cout << "IsNumber(\"true\"): " << IsNumber("true") << std::endl;
	std::cout << "IsNumber(\"zcc\"): " << IsNumber("zcc") << std::endl;
	std::cout << "IsNumber(\"24zcc\"): " << IsNumber("24zcc") << std::endl;
	std::cout << "IsNumber(\"zcc16\"): " << IsNumber("zcc16") << std::endl;
	std::cout << "IsNumber(\"36.6\"): " << IsNumber("36.6") << std::endl;
	std::cout << "IsNumber(\"101\"): " << IsNumber("101") << std::endl;

	PrintSeparate();
}
void ConvertType()
{
	//数据类型转换，支持string转数值，数值转字符串
	std::cout << "DataTypeConvert(12): " << DataTypeConvert(12).c_str() << std::endl;
	std::cout << "DataTypeConvert(76.4): " << DataTypeConvert(76.4).c_str() << std::endl;
	std::cout << "DataTypeConvert<double>(\"64.3\"): " << DataTypeConvert<double>("64.3") << std::endl;
	std::cout << "DataTypeConvert<bool>(\"True\"): " << DataTypeConvert<bool>("True") << std::endl;

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