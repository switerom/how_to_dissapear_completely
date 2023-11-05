#include "subtitles.h"
#include "assetmanager.h"
#include "settings.h"

Subtitles::Subtitles()
{
    _parser = nullptr;
    _subParserFactory = nullptr;
    _currentSub = _sub.end();
    _subChanged = true;
}

Subtitles::~Subtitles()
{
    clearText();

    delete _parser;
    delete _subParserFactory;
}

void Subtitles::loadSubs(const std::string& sub_name)
{
    for (auto& i : _sub)
    {
        delete i;
        i = nullptr;
    }

    _sub.clear();
    _currentSub = _sub.end();

    //delete _parser;
    //_parser = nullptr;
    //delete _subParserFactory;
    //_subParserFactory = nullptr;

    _subParserFactory = new SubtitleParserFactory(SUBS_DIR + sub_name);
    _parser = _subParserFactory->getParser();
    _sub = _parser->getSubtitles();

    if (!_sub.empty())
        _currentSub = _sub.begin();
    else
        _currentSub = _sub.end();
}

void Subtitles::Update(float dt)
{

}

void Subtitles::Draw(sf::RenderWindow& window)
{
    if (_currentSub == _sub.end())
        return;

    for(auto& i: _text)
        window.draw(*i);
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

void Subtitles::setText(long playtime)
{
    if (_sub.empty())
        return;

    std::wstring wstr{};

    if (_currentSub == _sub.end())
    {
        clearText();

        if (playtime >= _sub.at(0)->getStartTime())
            _currentSub = _sub.begin();

        return;
    }

    if (playtime >= (*_currentSub)->getEndTime())
    {
        ++_currentSub;
        _subChanged = true;

        clearText();
        return;
    }
    else if (playtime >= (*_currentSub)->getStartTime())
    {
        if (!_subChanged)
            return;

        _subChanged = false;
        wstr = convertToWideString((*_currentSub)->getText());

        std::wstring::size_type index = 0;
        std::wstring::size_type newLinePos;

        while ((newLinePos = wstr.find(L"\n", index)) != std::wstring::npos)
        {
            createTextLine(wstr.substr(index, newLinePos - index));
            index = newLinePos + 1;
        }

        // Handle the last line (or the only line if there are no newlines)
        createTextLine(wstr.substr(index));
    }
    else
    {
        clearText();
        return;
    }

    int num{ 0 };
    for (auto i{ _text.rbegin()}; i != _text.rend(); ++i)
    {
        sf::FloatRect textBounds = (*i)->getLocalBounds();
        (*i)->setOrigin(textBounds.left + textBounds.width * 0.5f, textBounds.top + textBounds.height * 0.5f + num * SUBS_LINES_INDENTATION);
        ++num;
    }
}

void Subtitles::createTextLine(const std::wstring& wstr)
{
    if (wstr == L"")
        return;

    _text.push_back(new sf::Text());
    _text.back()->setFont(AssetManager::getFont(SUBS_FONT));

    _text.back()->setCharacterSize(SUBS_SIZE);

    _text.back()->setFillColor(SUBS_COLOR);

    _text.back()->setPosition(SUBS_POS);

   // std::wstring wstr = convertToWideString(str);
    _text.back()->setString(wstr);
}

// Uses Windows.h (specific to windows)
std::wstring Subtitles::convertToWideString(const std::string& str) const
{
    std::wstring wstr{};

    int len = str.length();
    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, NULL, 0);
    wstr.resize(unicodeLen);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, &wstr[0], unicodeLen);

    return wstr;
}

void Subtitles::clearText()
{
    for (auto& i : _text)
    {
        delete i;
        i = nullptr;
    }

    _text.clear();
}

void Subtitles::changeCurrentSub(sf::Time playtime)
{
    if (_sub.empty())
        return;

    _currentSub = _sub.end();

    clearText();

    std::vector<SubtitleItem*>::iterator it{ _sub.begin() };

    for (auto it{_sub.begin()}; it != _sub.end(); ++it)
    {
        if (playtime.asMilliseconds() > (*it)->getStartTime() && playtime.asMilliseconds() < (*it)->getEndTime())
        {
            _subChanged = true;
            _currentSub = it;
            break;
        }
    }

    setText(playtime.asMilliseconds());
}