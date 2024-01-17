#include "Ultimate.h"
#include <iostream>

void PrintSeparate()
{
	std::cout << "==============================Separate==============================" << std::endl;
}
void GetTime()
{
	//��ȡ��ǰʱ��
	std::cout << "GetStringTime: " << GetStringTime().c_str() << std::endl;
	//��ȡ1900��1��1�����������
	std::cout << "GetTimeStamp1900: " << GetTimeStamp1900() << std::endl;
	//��ȡ1970��1��1�����������
	std::cout << "GetTimeStamp1970: " << GetTimeStamp1970() << std::endl;
	PrintSeparate();
}
void GetSplitString()
{
	std::string target = "name,age,skills";

	//�ַ����ָ������vector
	std::vector<std::string> resultVec;
	SplitString(target, resultVec, ",");

	//�ַ����ָ������unordered_set
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
	//�ַ���תСд
	std::cout << "GetLowercase(\"TrUe\"): " << GetLowercase("TrUe").c_str() << std::endl;
	//�ַ���ת��д
	std::cout << "GetUppercase(\"TrUe\"): " << GetUppercase("TrUe").c_str() << std::endl;

	PrintSeparate();
}
void Base64Encode()
{
	//byte����תbase64��Ϊ����չʾ���ַ���Ϊ��
	std::string str = "hello world!";
	std::string strBase64 = EncodeBinaryToBase64(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
	std::cout << str.c_str() << " -> EncodeBinaryToBase64 result: " << strBase64.c_str() << std::endl;
	
	//base64תbyte����
	std::vector<unsigned char> rsp = DecodeBase64ToBinary(strBase64);
	std::string strBinary(rsp.begin(), rsp.end());
	std::cout << strBase64.c_str() << " -> DecodeBase64ToBinary result: " << strBinary.c_str() << std::endl;
	
	PrintSeparate();
}
void OperateFile()
{
	//д���ļ�
	std::string contentWrite = "��C++�У���ʽ����ת����һ���ɳ���Ա��ȷָ��������ת��������";
	WriteFile("fileExample.txt", contentWrite.c_str(), contentWrite.length());
	std::cout << "WriteFile success" << std::endl;

	//��ȡ�ļ�
	std::vector<unsigned char> rsp = ReadFile("fileExample.txt");
	std::string contentRead(rsp.begin(), rsp.end());
	std::cout << "ReadFile: " << contentRead.c_str() << std::endl;
	PrintSeparate();
}
void JudgeNumber()
{
	//�ж��ַ����Ƿ�Ϊ����
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
	//��������ת����֧��stringת��ֵ����ֵת�ַ���
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