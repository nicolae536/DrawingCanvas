#include "pch.h"
#include "StringUtils.h"
#include <algorithm>
#include <iterator>
#include <ctype.h>
//#include <codecvt>


/****************************************************************
* StringToPlatformString
*****************************************************************/
Platform::String^ StringUtils::StringToPlatformString(const std::string& iString)
{
    return ref new Platform::String(StringUtils::StringToWString(iString).c_str());
}

/****************************************************************
* PlatformStringToString
*****************************************************************/
std::string StringUtils::PlatformStringToString(Platform::String^ iPlatformString)
{
    return StringUtils::WStringToString(iPlatformString->Data());
}

/****************************************************************
* StringToWString
*****************************************************************/
std::wstring StringUtils::StringToWString(const std::string& iString)
{
    std::wstring wString;
    wString.assign(iString.begin(), iString.end());
    //std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    //wString = converter.from_bytes(iString);
    return wString;
}

/****************************************************************
* WStringToString
*****************************************************************/
std::string StringUtils::WStringToString(const std::wstring& iWString)
{
    std::string str;
    str.assign(iWString.begin(), iWString.end());
    return str;
}

/****************************************************************
* WStringToPlatformString
*****************************************************************/
Platform::String^ StringUtils::WStringToPlatformString(const std::wstring& iWString)
{
    return ref new Platform::String(iWString.c_str());
}

/****************************************************************
* PlatformStringToWString
*****************************************************************/
std::wstring StringUtils::PlatformStringToWString(Platform::String^ iPlatformString)
{
    return std::wstring(iPlatformString->Data());
}

//****************************************************************
// RemoveExtraSpaces (std::string)
//****************************************************************
std::string StringUtils::RemoveExtraSpaces(const std::string& iString)
{
    std::string outputString;

    std::unique_copy(iString.begin(), iString.end(), std::back_insert_iterator<std::string>(outputString),
        [](char first, char second) { return isspace(first) && isspace(second); });

    return outputString;
}

//****************************************************************
// RemoveExtraSpaces (std::wstring)
//****************************************************************
std::wstring StringUtils::RemoveExtraSpaces(const std::wstring& iString)
{
    std::wstring outputString;

    std::unique_copy(iString.begin(), iString.end(), std::back_insert_iterator<std::wstring>(outputString),
        [](char first, char second) { return isspace(first) && isspace(second); });

    return outputString;
}

//****************************************************************
// ReplaceAllFast (std::string)
//****************************************************************
void StringUtils::ReplaceAllFast(std::string& ioString, const std::string& iFrom, const std::string& iTo)
{
    std::string outputString;
    outputString.reserve(ioString.length());  // avoids a few memory allocations

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while (std::string::npos != (findPos = ioString.find(iFrom, lastPos)))
    {
        outputString.append(ioString, lastPos, findPos - lastPos);
        outputString += iTo;
        lastPos = findPos + iFrom.length();
    }

    outputString += ioString.substr(lastPos);

    ioString.swap(outputString);
}

//****************************************************************
// ReplaceAllFast (std::wstring)
//****************************************************************
void StringUtils::ReplaceAllFast(std::wstring& ioString, const std::wstring& iFrom, const std::wstring& iTo)
{
    std::wstring outputString;
    outputString.reserve(ioString.length());  // avoids a few memory allocations

    std::wstring::size_type lastPos = 0;
    std::wstring::size_type findPos;

    while (std::wstring::npos != (findPos = ioString.find(iFrom, lastPos)))
    {
        outputString.append(ioString, lastPos, findPos - lastPos);
        outputString += iTo;
        lastPos = findPos + iFrom.length();
    }

    // Care for the rest after last occurrence
    outputString += ioString.substr(lastPos);

    ioString.swap(outputString);
}

//****************************************************************
// CaseInsensitiveCompare (std::string)
//****************************************************************
bool StringUtils::CaseInsensitiveCompare(const std::string& iFirstString, const std::string& iSecondString)
{
    return std::equal(iFirstString.begin(), iFirstString.end(), iSecondString.begin(), iSecondString.end(),
        [](char a, char b)
        {
            return tolower(a) == tolower(b);
        });
}


//****************************************************************
// CaseInsensitiveCompare (std::wstring)
//****************************************************************
bool StringUtils::CaseInsensitiveCompare(const std::wstring& iFirstString, const std::wstring& iSecondString)
{
    return std::equal(iFirstString.begin(), iFirstString.end(), iSecondString.begin(), iSecondString.end(),
        [](wchar_t a, wchar_t b)
        {
            return tolower(a) == tolower(b);
        });
}