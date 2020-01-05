#pragma once

#include <string>

namespace StringUtils {
    Platform::String^ StringToPlatformString(const std::string& iString);

    std::string PlatformStringToString(Platform::String^ iPlatformString);

    std::wstring StringToWString(const std::string& iString);

    std::string WStringToString(const std::wstring& iWString);

    Platform::String^ WStringToPlatformString(const std::wstring& iWString);

    std::wstring PlatformStringToWString(Platform::String^ iPlatformString);

    std::string RemoveExtraSpaces(const std::string& iString);

    std::wstring RemoveExtraSpaces(const std::wstring& iString);

    void ReplaceAllFast(std::string& ioString, const std::string& iFrom, const std::string& iTo);

    void ReplaceAllFast(std::wstring& ioString, const std::wstring& iFrom, const std::wstring& iTo);

    bool CaseInsensitiveCompare(const std::string& iFirstString, const std::string& iSecondString);

    bool CaseInsensitiveCompare(const std::wstring& iFirstString, const std::wstring& iSecondString);

};