#include "subtitles.h"
#include "assetmanager.h"
#include "settings.h"

Subtitles::Subtitles()
{
    _parser = nullptr;
    _subParserFactory = nullptr;
    _currentSub = _sub.end();
}

Subtitles::~Subtitles()
{
    for (auto& i : _text)
    {
        if(i)
            delete i;

        i = nullptr;
    }

    _text.clear();


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

    std::string str{};

    if (_currentSub == _sub.end())
    {
        for (auto& i : _text)
        {
            if (i)
                delete i;

            i = nullptr;
        }

        _text.clear();

        if (playtime >= _sub.at(0)->getStartTime())
            _currentSub = _sub.begin();

        return;
    }

    if (playtime >= (*_currentSub)->getEndTime())
    {
        ++_currentSub;

        for (auto& i : _text)
        {
            if (i)
                delete i;

            i = nullptr;
        }

        _text.clear();
        //_text.at(0)->setString(L"");
        return;
    }
    else if (playtime >= (*_currentSub)->getStartTime())
    {
        str = (*_currentSub)->getText();

        createTextLine(str);

        for (auto& i : str)
        {
            if (i == '\n')
            {
                // переписать под substring
                createTextLine(str);
            }
        }
    }
    else
    {
        for (auto& i : _text)
        {
            if (i)
                delete i;

            i = nullptr;
        }

        _text.clear();
        //_text.at(0)->setString(L"");
        return;
    }

    for (auto& i : _text)
    {
        i->setString(convertToWideString(str));
    }

    //sf::FloatRect textBounds = _text.at(0)->getLocalBounds();
    //_text.setOrigin(textBounds.left + textBounds.width * 0.5f, textBounds.top + textBounds.height * 0.5f);
    //_text.setPosition(SUBS_POS_X - _text.getGlobalBounds().width * 0.5f, SUBS_POS_Y);
}

void Subtitles::createTextLine(const std::string& str)
{
    if (str == "")
        return;

    _text.push_back(new sf::Text());
    _text.back()->setFont(AssetManager::getFont(SUBS_FONT));

    _text.back()->setCharacterSize(SUBS_SIZE);

    _text.back()->setFillColor(SUBS_COLOR);

    _text.back()->setPosition(SUBS_POS);

    std::wstring wstr = convertToWideString(str);
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

void Subtitles::changeCurrentSub(sf::Time playtime)
{
    if (_sub.empty())
        return;

    _currentSub = _sub.end();

    std::vector<SubtitleItem*>::reverse_iterator it{ _sub.rend() }, prev{ _sub.rend() };

    while(it != _sub.rbegin())
    {
        --it;

        if (playtime.asMilliseconds() > (*it)->getStartTime())
            _currentSub = prev.base();

        --prev;
    }
}