#pragma once
#include <set>
#include <afx.h>
#include <string>
#include <vector>
#include <sstream>
#include <stdint.h>
#include <unordered_set>

enum FileOperateError
{
	FileOperateError_Success = 0,
	FileOperateError_OpenFailed = -1,
	FileOperateError_WriteFailed,
	FileOperateError_BadPointer,
};

/// <summary>
///  时间
/// </summary>
///
extern ULONGLONG GetTimeStamp1900(bool local = true);
extern ULONGLONG GetTimeStamp1970(bool local = true);
extern std::string GetStringTime();

/// <summary>
///  字符串
/// </summary>
///
extern std::vector<std::string> SplitString(const std::string& origion,  const std::string& spliter);
extern std::vector<std::string> SplitString(std::string input, int len, bool reverse = false);
extern std::unordered_set<std::string> SplitStringSet(const std::string& origion, const std::string& spliter);
extern std::string TrimSpecialChar(const std::string& str, const std::string& specialChar = "");
extern std::string TrimFrontSpecialChar(const std::string& str, const std::string& specialChar = "");
extern std::string TrimBackSpecialChar(const std::string& str, const std::string& specialChar = "");
extern std::string RemoveDuplicateString(const std::string& str, const std::string& duplicate);
extern std::string GetLowercase(const std::string& s);
extern std::string GetUppercase(const std::string& s);
extern std::string Convert2Chinese(const std::string& numString);
extern std::string Convert2BigChinese(const std::string& numString);
extern std::string ConvertSingle2Chinese(const std::string& numString);

/// <summary>
///  编码
/// </summary>
///
extern std::string EncodeBinaryToBase64(const unsigned char* body, const unsigned int& len);
extern std::string EncodeBinaryToBase64(const std::vector<unsigned char>& bytes);
extern std::vector<unsigned char> DecodeBase64ToBinary(const std::string& base64_string);

/// <summary>
///  文件夹
/// </summary>
///
extern bool MakeDirectory(const std::string& folderPath);
extern bool MakeDirectorySingle(const std::string& folderPath);
extern bool GetFileName(const std::string& str, std::string& path, std::string& fileName);

/// <summary>
///  文件读写
/// </summary>
///
extern std::vector<unsigned char> ReadFile(std::string filename);
extern long WriteFile(std::string filename, const char* buffer, std::size_t length);
extern void GetFiles(std::string path, std::string extension, std::vector<std::string>& files, std::vector<__time64_t>& timers);

/// <summary>
///  线程相关
/// </summary>
///
extern void CloseSingleThread(HANDLE& handle, const DWORD& time = 3000);

/// <summary>
///  类型转换
/// </summary>
///
extern CString String2CString(const char* target);
extern std::string CStringtoString(CString target);
extern bool IsNumber(const std::string& s);
template<class T>
T DataTypeConvert(const std::string& value)
{
	if (IsNumber(value))
	{
		return static_cast<T>(std::stod(value));
	}
	else
	{
		if (!GetLowercase(value).compare("true"))
		{
			return static_cast<T>(std::stod("1"));
		}
		else
		{
			return static_cast<T>(std::stod("0"));
		}
	}
}
template<class T>
T DataTypeConvert(const char* value)
{
    return DataTypeConvert<T>((std::string)value);
}
template<class T>
std::string DataTypeConvert(const T& value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

/// <summary>
///  数组
/// </summary>
///
template<class T>
void MakeArray(T** ptr, const size_t& count)
{
	if (count == 0)
	{
		*ptr = nullptr;
	}
	else
	{
		*ptr = new T[count];
		memset(*ptr, 0, count * sizeof(T));
	}
}
template<class T>
void DeleteArray(T** ptr)
{
	if (*ptr != nullptr)
	{
		delete[] * ptr;
		*ptr = nullptr;
	}
}