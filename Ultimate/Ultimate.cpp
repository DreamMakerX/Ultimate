#include <io.h>
#include <map>
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

std::vector<std::string> SplitString(const std::string& origion, const std::string& spliter)
{
	//split string by spliter
	std::vector<std::string> result;
	std::string::size_type startPos, endPos;
	endPos = origion.find(spliter);
	startPos = 0;
	while (std::string::npos != endPos)
	{
		result.push_back(origion.substr(startPos, endPos - startPos));
		startPos = endPos + spliter.size();
		endPos = origion.find(spliter, startPos);
	}
	if (startPos != origion.length()) {
		result.push_back(origion.substr(startPos));
	}
	return result;
}
std::vector<std::string> SplitString(std::string input, int len, bool reverse) {
	std::vector<std::string> result;

	if (len <= 0 || len >= input.size()) {
		result.push_back(input);
		return result;
	}

	if (reverse)
	{
		int pos = input.size();
		while (pos > 0) {
			int count = min(len, pos);
			result.push_back(input.substr(pos - count, count));
			pos -= count;
		}
	}
	else
	{
		int index = 0;
		while (index < input.size()) {
			result.push_back(input.substr(index, len));
			index += len;
		}
	}

	return result;
}
std::unordered_set<std::string> SplitStringSet(const std::string& origion, const std::string& spliter)
{
	//split string by spliter
	std::unordered_set<std::string> result;
	std::string::size_type startPos, endPos;
	endPos = origion.find(spliter);
	startPos = 0;
	while (std::string::npos != endPos)
	{
		result.insert(origion.substr(startPos, endPos - startPos));
		startPos = endPos + spliter.size();
		endPos = origion.find(spliter, startPos);
	}
	if (startPos != origion.length()) {
		result.insert(origion.substr(startPos));
	}
	return result;
}
std::string TrimSpecialChar(const std::string& str, const std::string& specialChar)
{
	return TrimBackSpecialChar(TrimFrontSpecialChar(str, specialChar), specialChar);;
}
std::string TrimFrontSpecialChar(const std::string& str, const std::string& specialChar)
{
	if (specialChar.empty())
	{
		std::string defaultSpecialChar = "\t\n,.;:?!'\"+-*/=_<>()[]{}\\~@#$%^&";
		return TrimFrontSpecialChar(str, defaultSpecialChar);
	}
	auto start = str.find_first_not_of(specialChar);

	if (start != std::string::npos)
	{
		return str.substr(start, str.length() - start);
	}

	return str;
}
std::string TrimBackSpecialChar(const std::string& str, const std::string& specialChar)
{
	if (specialChar.empty())
	{
		std::string defaultSpecialChar = "\t\n,.;:?!'\"+-*/=_<>()[]{}\\~@#$%^&";
		return TrimBackSpecialChar(str, defaultSpecialChar);
	}
	auto end = str.find_last_not_of(specialChar);

	if (end != std::string::npos)
	{
		return str.substr(0, end + 1);
	}

	return str;
}
std::string RemoveDuplicateString(const std::string& str, const std::string& duplicate)
{
	if (duplicate.empty()) {
		return str;
	}

	size_t pos = 0;
	std::string result = str;
	while ((pos = result.find(duplicate + duplicate, pos)) != std::string::npos) {
		result.replace(pos, 2 * duplicate.length(), duplicate);
	}

	return result;
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
std::string ConvertSingle2Chinese(const std::string& numString)
{
	std::string result;
	std::string units[] = { "", "ʮ", "��", "ǧ" };
	std::map<char, std::string> values = {
		{'0',"��"},
		{'1',"һ"},
		{'2',"��"},
		{'3',"��"},
		{'4',"��"},
		{'5',"��"},
		{'6',"��"},
		{'7',"��"},
		{'8',"��"},
		{'9',"��"} };
	size_t len = numString.length();
	for (int i = len - 1; i >= 0; --i)
	{
		std::string value = values[numString[i]];
		std::string unit = units[len - i - 1];
		//��ֵΪ�㣬ɾ����ֵ�ĵ�λ
		if (!value.compare("��"))
		{
			unit = "";
		}
		result = value + unit + result;
	}
	//ȥ���ظ�����
	result = RemoveDuplicateString(result, "��");
	//ȥ��ĩβ����
	result = TrimBackSpecialChar(result, "��");

	return result;
}
std::string Convert2Chinese(const std::string& numString) {
	//������������תΪ����Сд���֣�����/���ڣ�
	if (numString.size() > 16)
	{
		return "����ֵ����ת����Χ";
	}
	std::string result;
	std::string units[] = { "", "��", "��", "��" };
	std::vector<std::string> groups = SplitString(numString, 4, true);
	size_t len = groups.size();
	for (int i = 0; i < len; ++i)
	{
		std::string value = ConvertSingle2Chinese(groups[i]);
		std::string unit = units[i];
		//����Ϊ�գ����ӵ�λ
		if (!value.compare("��"))
		{
			unit = "";
		}
		result = value + unit + result;
	}
	//ȥ����β����
	return TrimSpecialChar(result, "��");
}
std::string Convert2BigChinese(const std::string& numString)
{
	std::string chinese = Convert2Chinese(numString);

	std::map<std::string, std::string> digitMap{
		{"��","��"},
		{"һ","Ҽ"},
		{"��","��"},
		{"��","��"},
		{"��","��"},
		{"��","��"},
		{"��","½"},
		{"��","��"},
		{"��","��"},
		{"��","��"},
		{"ʮ","ʰ"},
		{"��","��"},
		{"ǧ","Ǫ"},
		{"��","��"},
		{"��","��"},
		{"��","��"} };
	std::string output;
	for (int i = 0; i < chinese.length(); i += 2) {
		std::string digit = chinese.substr(i, 2);
		if (digitMap.find(digit) != digitMap.end()) {
			output += digitMap[digit];
		}
		else {
			output += digit;
		}
	}
	return output;
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