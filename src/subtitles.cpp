#include "subtitles.h"
#include "assetmanager.h"
#include "settings.h"

Subtitles::Subtitles()
{
    _parser = nullptr;
    _subParserFactory = nullptr;
    _currentSub = _sub.end();
    _subChanged = true;
    _selectedTextRange.first = sf::Vector2i(0, 0);
    _selectedTextRange.second = sf::Vector2i(0, 0);
    inSelectProcess = false;
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

    for (auto& i : _lettersBounds)
        i.clear();

    _lettersBounds.clear();
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

std::vector<sf::FloatRect> Subtitles::getTextBounds() const
{
    std::vector<sf::FloatRect> subsBounds;

    for (auto& i : _text)
        subsBounds.push_back(i->getGlobalBounds());

    return subsBounds;
}

void Subtitles::createLettersBounds()
{
    for (auto& i : _lettersBounds)
        i.clear();

    _lettersBounds.clear();

    // Add letters bounds to a container
    for (std::size_t i{ 0 }; i < _text.size(); ++i)
    {
        _lettersBounds.push_back(std::vector<sf::FloatRect>{}); // Maybe dynamically allocate

        for (std::size_t j = 0; j < _text.at(i)->getString().getSize(); ++j)
        {
            sf::Text letter(_text.at(i)->getString()[j], AssetManager::getFont(SUBS_FONT), _text.at(i)->getCharacterSize());

            // Set the position for the individual letter
            letter.setPosition(_text.at(i)->findCharacterPos(j));

            // Calculate the bounds for the individual letter
            sf::FloatRect letterRect{ letter.getLocalBounds() };

            letterRect.left = letter.getPosition().x + letterRect.left;
            letterRect.top = letter.getPosition().y + letterRect.top;

            _lettersBounds.at(i).push_back(letterRect);
        }
    }
}

void Subtitles::startSelect(sf::RenderWindow& window, const sf::View& areaView)
{
    inSelectProcess = true;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, areaView);

    createLettersBounds();

    for (std::size_t i{ 0 }; i < _lettersBounds.size(); ++i)
    {
        for (std::size_t j{ 0 }; j < _lettersBounds.at(i).size(); ++j)
        {
            // Check which letter contains contains the mouse position
            if (_lettersBounds.at(i).at(j).contains(mousePosView))
            {
                _selectedTextRange.first = sf::Vector2i(i, j);
                return;
            }
        }
    }

    _selectedTextRange.first = sf::Vector2i(0, 0);
}

void Subtitles::setSelect(sf::RenderWindow& window, const sf::View& areaView)
{
    if (!inSelectProcess || _lettersBounds.empty())
        return;
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, areaView);

    int index1{}, index2{};

    //std::cout << "Mouse Y: " << mousePosView.y << '\n';

    for (int i{0}; i < _lettersBounds.size(); ++i)
    {
        for (int j{ 0 }; j < _lettersBounds.at(i).size(); ++j)
        {
            float topBound = _lettersBounds.at(i).at(0).top;
            float bottomBound = _lettersBounds.at(i).at(0).top + _lettersBounds.at(i).at(0).height;

            if (mousePosView.y > topBound && mousePosView.y < bottomBound)
            {
                index1 = i;
                break;
            }
        }

        for (int j{ 0 }; j < _lettersBounds.at(i).size(); ++j)
        {
            float leftBound = _lettersBounds.at(i).at(j).left;
            float rightBound = _lettersBounds.at(i).at(j).left + _lettersBounds.at(i).at(j).width;

            if (mousePosView.x > leftBound && mousePosView.x < rightBound)
            {
                index2 = j;
                break;
            }
        }
    }

    std::cout << "Index 1: " << _selectedTextRange.first.x << '\t' << _selectedTextRange.first.y << '\t';
    std::cout << "Index 2: " << _selectedTextRange.second.x << '\t' << _selectedTextRange.second.y << '\n';

    _selectedTextRange.second = sf::Vector2i(index1, index2);
}

void Subtitles::endSelect()
{
    inSelectProcess = false;

    //std::cout << "Index 1: " << _selectedTextRange.first.x << '\t' << _selectedTextRange.first.y << '\t';
    //std::cout << "Index 2: " << _selectedTextRange.second.x << '\t' << _selectedTextRange.second.y << '\n';
}