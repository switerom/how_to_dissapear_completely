#include "subtitles.h"
#include "assetmanager.h"
#include "settings.h"

Subtitles::Subtitles()
{
    _text.setFont(AssetManager::getFont(SUBS_FONT)); 

    _text.setCharacterSize(SUBS_SIZE); // in pixels, not points!

    _text.setFillColor(SUBS_COLOR);
    _text.setPosition(SUBS_POS);

    _parser = nullptr;
    _subParserFactory = nullptr;
}

void Subtitles::loadSubs(const std::string& sub_name)
{
    _sub.clear();

    if (_parser)
        delete _parser;

    if(_subParserFactory)
        delete _subParserFactory;

    _subParserFactory = new SubtitleParserFactory(SUBS_DIR + sub_name);
    _parser = _subParserFactory->getParser();
    _sub = _parser->getSubtitles();

    setText(0.f);
}

void Subtitles::Update(float dt)
{
    if (_sub.empty())
        return;

    //setText(dt);
}

void Subtitles::Draw(sf::RenderWindow& window)
{
    if (_sub.empty())
        return;

    window.draw(_text);
}

// Old version that deprecated and can be used if certain macros defined
//void Subtitles::setText(float playtime)
//{
//    std::wstring wide;
//
//    if (_sub.empty())
//        wide = L"";
//
//    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//    std::string narrow = _sub.at(0)->getText();
//    wide = converter.from_bytes(narrow);
//
//    _text.setString(wide);
//}

// Uses Windows.h (specific to windows)
void Subtitles::setText(float playtime)
{
    std::wstring wide;

    if (_sub.empty())
    {
        wide = L"";
        return;
    }

    std::string narrow = _sub.at(0)->getText();

    int len = narrow.length();
    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), len, NULL, 0);
    wide.resize(unicodeLen);
    MultiByteToWideChar(CP_UTF8, 0, narrow.c_str(), len, &wide[0], unicodeLen);

    _text.setString(wide);

    std::wcout << wide << '\n';
}


