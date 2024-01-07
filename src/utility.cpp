#include "utility.h"

// Uses Windows.h (specific to windows)
std::wstring convertToWideString(const std::string& str)
{
    std::wstring wstr{};

    int len = str.length();
    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, NULL, 0);
    wstr.resize(unicodeLen);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, &wstr[0], unicodeLen);

    return wstr;
}