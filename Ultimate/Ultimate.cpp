#include <io.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sys/timeb.h>
#include "Ultimate.h"
#include <Wincrypt.h>

#pragma comment(lib, "crypt32.lib")

ULONGLONG GetTimeStamp1900(bool local)
{
	//��ȡ1900��1��1�����������
	FILETIME ft;
	SYSTEMTIME st;
	GetSystemTime(&st); // gets current time
	SystemTimeToFileTime(&st, &ft); // converts to file time format
	ULONGLONG tickCount = ((((ULONGLONG)ft.dwHighDateTime) << 32) + ft.dwLowDateTime) / 10000;

	//��ȡʱ��
	TIME_ZONE_INFORMATION timeZoneInfo;
	GetTimeZoneInformation(&timeZoneInfo);
	long timeZone = timeZoneInfo.Bias / (-60);

	//���ص���ʱ���ϵͳʱ��
	if(local)
		return tickCount + timeZone * 60 * 60;
	else
		return tickCount;
}
ULONGLONG GetTimeStamp1970(bool local)
{
	//��ȡ1970��1��1�����������
	struct timeb tb;
	ftime(&tb);

	//��ȡʱ��
	TIME_ZONE_INFORMATION timeZoneInfo;
	GetTimeZoneInformation(&timeZoneInfo);
	long timeZone = timeZoneInfo.Bias / (-60);

	//���ص���ʱ���ϵͳʱ��
	if(local)
		return tb.time + timeZone * 60 * 60;
	else
		return tb.time;//����Ҫ������ ==> tb.time*1000 + tb.millitm
}
std::string GetStringTime()
{
	char time[32] = { 0 };
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	sprintf_s(time, "%4d-%02d-%02d %02d:%02d:%02d.%03d", systime.wYear, systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);

	return time;
}

void SplitString(const std::string& origion, std::vector<std::string>& res, const std::string& spliter)
{
	//split string by spliter
	std::string::size_type startPos, endPos;
	endPos = origion.find(spliter);
	startPos = 0;
	while (std::string::npos != endPos)
	{
		res.push_back(origion.substr(startPos, endPos - startPos));
		startPos = endPos + spliter.size();
		endPos = origion.find(spliter, startPos);
	}
	if (startPos != origion.length()) {
		res.push_back(origion.substr(startPos));
	}
}
void SplitString(const std::string& origion, std::unordered_set<std::string>& res, const std::string& spliter)
{
	//split string by spliter
	std::string::size_type startPos, endPos;
	endPos = origion.find(spliter);
	startPos = 0;
	while (std::string::npos != endPos)
	{
		res.insert(origion.substr(startPos, endPos - startPos));
		startPos = endPos + spliter.size();
		endPos = origion.find(spliter, startPos);
	}
	if (startPos != origion.length()) {
		res.insert(origion.substr(startPos));
	}
}
std::string GetLowercase(const std::string& s)
{
	std::string result = s;
	std::transform(result.begin(), result.end(), result.begin(), ::tolower);
	return result;
}
std::string GetUppercase(const std::string& s)
{
	std::string result = s;
	std::transform(result.begin(), result.end(), result.begin(), ::toupper);
	return result;
}

std::string EncodeBinaryToBase64(const unsigned char* body, const unsigned int& len)
{
	DWORD encode_length = 0;
	char* encode_char = NULL;

	CryptBinaryToStringA(body, len, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, NULL, &encode_length);

	if (encode_length)
	{
		encode_char = (char*)malloc(encode_length);
		ZeroMemory(encode_char, encode_length);
		CryptBinaryToStringA(body, len, CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, encode_char, &encode_length);
	}

	std::string base64_string = encode_char;
	free(encode_char);

	return base64_string;
}
std::string EncodeBinaryToBase64(const std::vector<unsigned char>& bytes)
{
	DWORD encode_length = 0;
	char* encode_char = NULL;

	CryptBinaryToStringA(bytes.data(), bytes.size(), CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, NULL, &encode_length);

	if (encode_length)
	{
		encode_char = (char*)malloc(encode_length);
		ZeroMemory(encode_char, encode_length);
		CryptBinaryToStringA(bytes.data(), bytes.size(), CRYPT_STRING_BASE64 | CRYPT_STRING_NOCRLF, encode_char, &encode_length);
	}

	std::string base64_string = encode_char;
	free(encode_char);

	return base64_string;
}
std::vector<unsigned char> DecodeBase64ToBinary(const std::string& base64_string)
{
	DWORD decode_length = 0;
	CryptStringToBinaryA(base64_string.c_str(), NULL, CRYPT_STRING_BASE64, NULL, &decode_length, NULL, NULL);

	std::vector<unsigned char> bytes(decode_length);
	CryptStringToBinaryA(base64_string.c_str(), NULL, CRYPT_STRING_BASE64, bytes.data(), &decode_length, NULL, NULL);

	return bytes;
}

bool MakeDirectory(const std::string& folderPath)
{
	//creat dir,multi-level
	std::string strDir;
	int nPos = folderPath.find_first_of("/\\");
	while (nPos != -1)
	{
		strDir = folderPath.substr(0, nPos);
		if (!MakeDirectorySingle(strDir))
			return false;
		nPos = folderPath.find_first_of("/\\", nPos + 1);
	}
	MakeDirectorySingle(folderPath);

	return true;
}
bool MakeDirectorySingle(const std::string& folderPath)
{
	//creat dir
	BOOL flag = FALSE;
	DWORD bRes = GetFileAttributesA(folderPath.c_str());
	//���ļ��в����ڣ������ļ���
	if (bRes == 0xFFFFFFFF)
		CreateDirectoryA(folderPath.c_str(), nullptr);
	else if (bRes & FILE_ATTRIBUTE_DIRECTORY)	//�ļ��д���
		flag = CreateDirectoryA(folderPath.c_str(), nullptr); // flag Ϊ true ˵�������ɹ�
	else
		return false;

	return true;
}
bool GetFileName(const std::string& str, std::string& path, std::string& fileName)
{
	int found = str.find_last_of("/\\");
	if (found != -1)
	{
		path = str.substr(0, found);
		fileName = str.substr(found + 1);
	}
	else
		return false;

	return true;
}

std::vector<unsigned char> ReadFile(std::string filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file) {
		return {};
	}

	// ��ȡ�ļ���С
	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// ����һ���㹻���vector���洢�ļ�����
	std::vector<unsigned char> fileData(fileSize);

	// һ���Զ�ȡ�ļ����ݵ�vector��
	file.read(reinterpret_cast<char*>(fileData.data()), fileSize);

	if (file.fail()) {
		std::cout << "�ļ���ȡʧ��: " << filename << std::endl;
		return {};
	}

	file.close();

	return fileData;
}
long WriteFile(std::string filename, const char* buffer, std::size_t length) {
	std::ofstream file(filename, std::ios::binary);

	if (!file) {
		return FileOperateError_OpenFailed;
	}

	// д�뻺�������ݵ��ļ�
	file.write(buffer, length);

	if (file.fail()) {
		return FileOperateError_WriteFailed;
	}

	file.close();

	return FileOperateError_Success;
}
void GetFiles(std::string path, std::string extension, std::vector<std::string>& files, std::vector<__time64_t>& timers)
{
	//��ȡ�ļ����������ļ���
	//�ļ����
	intptr_t   hFile = 0;

	struct _finddata_t fileinfo;
	std::string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				;
			}
			else
			{
				std::string szbuf = fileinfo.name;
				size_t isd = szbuf.find("." + extension);
				if (isd > 0) {
					files.push_back(fileinfo.name);
					timers.push_back(fileinfo.time_write);
				}
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

void CloseSingleThread(HANDLE& handle, const DWORD& time)
{
	if (handle != INVALID_HANDLE_VALUE)
	{
		WaitForSingleObject(handle, INFINITE);
		CloseHandle(handle);

		handle = INVALID_HANDLE_VALUE;
	}
}

bool IsNumber(const std::string& s) {
	std::istringstream iss(s);
	double value;

	// ���Դ��ַ�������ȡ������
	if (iss >> value) {
		// �����ȡ���Ƿ񵽴��ַ���ĩβ
		char c;
		if (iss >> c) {
			// �����ȡ�������ַ�����˵��������Ч�ĸ�������ʽ
			return false;
		}
		else {
			// ��ȡ�ɹ��ҵ����ַ���ĩβ��˵������Ч�ĸ�������ʽ
			return true;
		}
	}
	else {
		// ��ȡʧ�ܣ�˵��������Ч�ĸ�������ʽ
		return false;
	}
}
CString String2CString(const char* target)
{
	//std::string to CString
	CString result;
#ifdef _UNICODE		
	//�����unicode����	
	int num = MultiByteToWideChar(0, 0, target, -1, NULL, 0);
	result.GetBufferSetLength(num + 1);
	MultiByteToWideChar(0, 0, target, -1, result.GetBuffer(), num);
	result.ReleaseBuffer();

	return result;
#else		
	//����Ƕ��ֽڹ���	
	result.Format("%s", target);
	return result;
#endif 	
}
std::string CStringtoString(CString target)
{
	//CString to std::string
#ifdef _UNICODE		
	//�����unicode����		
	USES_CONVERSION;
	std::string result(W2A(target));
	return result;
#else		
	//����Ƕ��ֽڹ��� 	
	std::string result(target.GetString());
	return result;
#endif	
}