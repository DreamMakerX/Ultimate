#include "Ultimate.h"
#include <iostream>

void PrintSeparate()
{
	std::cout << "==============================Separate==============================" << std::endl;
}
void GetTime()
{
	//��ȡ��ǰʱ��
	std::cout << "��ȡ��ǰʱ��: " << GetStringTime().c_str() << std::endl;
	//��ȡ1900��1��1�����������
	std::cout << "��ȡ1900��1��1�����������: " << GetTimeStamp1900() << std::endl;
	//��ȡ1970��1��1�����������
	std::cout << "��ȡ1970��1��1�����������: " << GetTimeStamp1970() << std::endl;
	PrintSeparate();
}
void GetSplitString()
{
	std::string target = "name,age,skills";

	//�ַ����ָ������vector
	std::vector<std::string> resultVec;
	SplitString(target, resultVec, ",");
	std::cout << "�ַ����ָ������vector��\"name,age,skills\"��: " << std::endl;
	for (auto item : resultVec)
	{
		std::cout << item << std::endl;
	}

	//�ַ����ָ������unordered_set
	std::unordered_set<std::string> resultSet;
	SplitString(target, resultSet, ",");
	std::cout << "�ַ����ָ������unordered_set��\"name,age,skills\"��: " << std::endl;
	for (auto item : resultSet)
	{
		std::cout << item << std::endl;
	}

	//ȥ����βĿ���ַ�
	std::cout << "ȥ����βĿ���ַ�(\",Var1,\", \",\"): " << TrimSpecialChar(",Var1,", ",").c_str() << std::endl;
	//ȥ����βĿ���ַ�,��Ŀ���ַ���Ĭ��ȥ��\t\n,.;:?!'\"+-*/=_<>()[]{}\\~@#$%^&
	std::cout << "ȥ����βĿ���ַ�,������Ŀ���ַ�(\"#Var1@\"): " << TrimSpecialChar("#Var1@").c_str() << std::endl;
	
	//�ַ���תСд
	std::cout << "�ַ���תСд(\"TrUe\"): " << GetLowercase("TrUe").c_str() << std::endl;
	//�ַ���ת��д
	std::cout << "�ַ���ת��д(\"TrUe\"): " << GetUppercase("TrUe").c_str() << std::endl;

	PrintSeparate();
}
void Base64Encode()
{
	//byte����תbase64��Ϊ����չʾ���ַ���Ϊ��
	std::string str = "hello world!";
	std::string strBase64 = EncodeBinaryToBase64(reinterpret_cast<const unsigned char*>(str.c_str()), str.length());
	std::cout << str.c_str() << " -> byte����תbase64���: " << strBase64.c_str() << std::endl;
	
	//base64תbyte����
	std::vector<unsigned char> rsp = DecodeBase64ToBinary(strBase64);
	std::string strBinary(rsp.begin(), rsp.end());
	std::cout << strBase64.c_str() << " -> base64תbyte������: " << strBinary.c_str() << std::endl;
	
	PrintSeparate();
}
void OperateFile()
{
	//д���ļ�
	std::string contentWrite = "��C++�У���ʽ����ת����һ���ɳ���Ա��ȷָ��������ת��������";
	WriteFile("fileExample.txt", contentWrite.c_str(), contentWrite.length());
	std::cout << "д���ļ�: " << "WriteFile success" << std::endl;

	//��ȡ�ļ�
	std::vector<unsigned char> rsp = ReadFile("fileExample.txt");
	std::string contentRead(rsp.begin(), rsp.end());
	std::cout << "��ȡ�ļ�: " << contentRead.c_str() << std::endl;
	PrintSeparate();
}
void JudgeNumber()
{
	//�ж��ַ����Ƿ�Ϊ����
	std::cout << "�ж��ַ����Ƿ�Ϊ����(\"true\"): " << IsNumber("true") << std::endl;
	std::cout << "�ж��ַ����Ƿ�Ϊ����(\"zcc\"): " << IsNumber("zcc") << std::endl;
	std::cout << "�ж��ַ����Ƿ�Ϊ����(\"24zcc\"): " << IsNumber("24zcc") << std::endl;
	std::cout << "�ж��ַ����Ƿ�Ϊ����(\"zcc16\"): " << IsNumber("zcc16") << std::endl;
	std::cout << "�ж��ַ����Ƿ�Ϊ����(\"36.6\"): " << IsNumber("36.6") << std::endl;
	std::cout << "�ж��ַ����Ƿ�Ϊ����(\"101\"): " << IsNumber("101") << std::endl;

	PrintSeparate();
}
void ConvertType()
{
	//��������ת����֧��stringת��ֵ����ֵת�ַ���
	std::cout << "��������ת��,��ֵת�ַ���(12): " << DataTypeConvert(12).c_str() << std::endl;
	std::cout << "��������ת��,��ֵת�ַ���(76.4): " << DataTypeConvert(76.4).c_str() << std::endl;
	std::cout << "��������ת��,�ַ���תdouble(\"64.3\"): " << DataTypeConvert<double>("64.3") << std::endl;
	std::cout << "��������ת��,�ַ���תbool(\"True\"): " << DataTypeConvert<bool>("True") << std::endl;

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