#include "npafile.hpp"

std::locale NpaFile::Locale;

NpaFile::NpaFile(const std::string& Name) : Name(Name)
{
}

NpaFile::~NpaFile()
{
}

void NpaFile::SetLocale(const char* LocaleStr)
{
    Locale = boost::locale::generator().generate(LocaleStr);
}

char* NpaFile::Decrypt(char* pBuff, uint32_t Size, uint32_t Offset)
{
    static const uint8_t Key[8] = { 0xBD, 0xAA, 0xBC, 0xB4, 0xAB, 0xB6, 0xBC, 0xB4 };
    for (uint32_t i = 0; i < Size; ++i)
        pBuff[i] ^= Key[(i + Offset) % 8];
    return pBuff;
}

char* NpaFile::Encrypt(char* pBuff, uint32_t Size)
{
    return Decrypt(pBuff, Size);
}

std::string NpaFile::ToUtf8(const std::string& String)
{
    return boost::locale::conv::to_utf<char>(String.c_str(), String.c_str() + String.size(), Locale);
}

std::string NpaFile::FromUtf8(const std::string& String)
{
    return boost::locale::conv::from_utf<char>(String.c_str(), String.c_str() + String.size(), Locale);
}
