#include "subtitles.h"
#include "assetmanager.h"
#include "settings.h"
#include "utility.h"

Subtitles::Subtitles()
{
    _parser = nullptr;
    _subParserFactory = nullptr;
    _currentSub = _sub.end();
    _subChanged = true;
    _selectedTextRange.first = sf::Vector2i(0, 0);
    _selectedTextRange.second = sf::Vector2i(0, 0);
    inSelectProcess = false;

    _subsSelectRects.setFillColor(SUBS_SELECT_COLOR);
}

Subtitles::~Subtitles()
{
    for (auto& i : _text)
    {
        delete i;
        i = nullptr;
    }

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

    for (int i{ 0 }; i < _subsSelectedLinesBounds.size(); ++i)
    {
        _subsSelectRects.setPosition(_subsSelectedLinesBounds.at(i).left, _subsSelectedLinesBounds.at(i).top);
        _subsSelectRects.setSize(sf::Vector2f(_subsSelectedLinesBounds.at(i).width, _subsSelectedLinesBounds.at(i).height));

        window.draw(_subsSelectRects);
    }

    for(auto& i: _text)
        window.draw(*i);
}

void Subtitles::setText(long playtime)
{
    if (_sub.empty())
        return;

    std::wstring wstr{};

    if (_currentSub == _sub.end())
    {
        clearText();

        if (playtime >= (*_sub.begin())->getStartTime())
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
    _text.back()->setString(wstr);
}

// Uses Windows.h (specific to windows)
//std::wstring Subtitles::convertToWideString(const std::string& str) const
//{
//    std::wstring wstr{};
//
//    int len = str.length();
//    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, NULL, 0);
//    wstr.resize(unicodeLen);
//    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, &wstr[0], unicodeLen);
//
//    return wstr;
//}

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
    _subsSelectedLinesBounds.clear();

    _selectedTextRange.first = sf::Vector2i(0, 0);
    _selectedTextRange.second = sf::Vector2i(0, 0);
}

void Subtitles::changeSubPlayback(sf::Time playtime)
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

    //auto letterCount{ _text.size() };

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
            letterRect.top = letter.getPosition().y + SUBS_SIZE * SUBS_POS_Y_FACTOR;
            letterRect.height = SUBS_SIZE;

            // To remove empty space between letters rects, exceot last letter
            if (j != _text.size() - 1)
                letterRect.width = _text.at(i)->findCharacterPos(j + 1).x - letter.getPosition().x;

            _lettersBounds.at(i).push_back(letterRect);
        }
    }
}

void Subtitles::startSelect(sf::RenderWindow& window, const sf::View& areaView)
{
    inSelectProcess = true;

    _subsSelectedLinesBounds.clear();

    _selectedTextRange.first = sf::Vector2i(0, 0);
    _selectedTextRange.second = sf::Vector2i(0, 0);

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, areaView);

    createLettersBounds();

    for (std::size_t i{ 0 }; i < _lettersBounds.size(); ++i)
    {
        for (std::size_t j{ 0 }; j < _lettersBounds.at(i).size(); ++j)
        {
            // Check what letter contains contains the mouse position
            if (_lettersBounds.at(i).at(j).contains(mousePosView))
            {
                _selectedTextRange.first = sf::Vector2i(i, j);
                _selectedTextRange.second = sf::Vector2i(i, j);
                return;
            }
        }
    }
}

void Subtitles::setSelect(sf::RenderWindow& window, const sf::View& areaView)
{
    if (!inSelectProcess || _lettersBounds.empty())
        return;
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, areaView);

    for (int i{0}; i < _lettersBounds.size(); ++i)
    {
        for (int j{ 0 }; j < _lettersBounds.at(i).size(); ++j)
        {
            sf::FloatRect rect;
            rect.top = _lettersBounds.at(i).begin()->top;
            rect.height = _lettersBounds.at(i).begin()->height;
            rect.width = _lettersBounds.at(i).at(j).width*0.2f;
            rect.left = _lettersBounds.at(i).at(j).left + _lettersBounds.at(i).at(j).width*0.4f;

            if (rect.contains(mousePosView))
            {
                _selectedTextRange.second = sf::Vector2i(i, j);
                changeSelectedLinesBounds();
                break;
            }
        }
    }
}

void Subtitles::endSelect()
{
    inSelectProcess = false;
}


void Subtitles::swapSelection(const sf::Vector2i& select_first, const sf::Vector2i& select_second)
{
    sf::Vector2i first{ select_first }, second{ select_second };

    //swap range indexes
    if (first.x > second.x)
    {
        std::swap(_selectedTextRange.first, _selectedTextRange.second);
    }
    else if (first.x == second.x && first.y > second.y)
    {
        std::swap(_selectedTextRange.first, _selectedTextRange.second);
    }
}

void Subtitles::changeSelectedLinesBounds()
{
    if (_lettersBounds.empty())
        return ;

    sf::Vector2i first{ _selectedTextRange.first }, second{ _selectedTextRange.second }, swap{};

    // Could be optimized, not to be called every time, but instead specific indexes could be removed or added
    _subsSelectedLinesBounds.clear();

    //swap range indexes
    if (first.x > second.x)
    {
        swap = first;
        first = second;
        second = swap;
    }
    else if (first.x == second.x && first.y > second.y)
    {
        swap = first;
        first = second;
        second = swap;
    }

    // Если выделение на одной и той же линии
    if (first.x == second.x)
    {
        //// Если ничего не выделено
        if(first.y == second.y)
        {
            sf::FloatRect rect4{};

            _subsSelectedLinesBounds.push_back(rect4);
            return ;
        }

        sf::FloatRect rect;
        rect.left = _lettersBounds.at(first.x).at(first.y).getPosition().x;
        rect.top = _lettersBounds.at(first.x).at(first.y).getPosition().y;
        rect.height = SUBS_SIZE;
        rect.width = _lettersBounds.at(second.x).at(second.y).getPosition().x - rect.left 
                    + _lettersBounds.at(second.x).at(second.y).getSize().x;

        _subsSelectedLinesBounds.push_back(rect);
    }
    else
    {
        sf::FloatRect rect1;
        rect1.left = _lettersBounds.at(first.x).at(first.y).getPosition().x;
        rect1.top = _lettersBounds.at(first.x).at(first.y).getPosition().y;

        rect1.height = SUBS_SIZE;
        auto lastLetterIndex = _lettersBounds.at(first.x).size() - 1;
        rect1.width = _lettersBounds.at(first.x).at(lastLetterIndex).getPosition().x - rect1.left
                     + _lettersBounds.at(first.x).at(lastLetterIndex).getSize().x;
        _subsSelectedLinesBounds.push_back(rect1);

        for (int i{ first.x + 1 }; i < second.x; ++i)
        {
            sf::FloatRect rect;
            rect.left = _lettersBounds.at(i).begin()->getPosition().x;
            rect.top = _lettersBounds.at(i).begin()->getPosition().y;
            rect.height = SUBS_SIZE;
            auto lastLetterIndex = _lettersBounds.at(i).size() - 1;
            rect.width = _lettersBounds.at(i).at(lastLetterIndex).getPosition().x - rect.left
                + _lettersBounds.at(i).at(lastLetterIndex).getSize().x;
            _subsSelectedLinesBounds.push_back(rect);
        }

        sf::FloatRect rect2;
        rect2.left = _lettersBounds.at(second.x).begin()->getPosition().x;
        rect2.top = _lettersBounds.at(second.x).begin()->getPosition().y;
        rect2.height = SUBS_SIZE;
        rect2.width = _lettersBounds.at(second.x).at(second.y).getPosition().x - rect2.left
            + _lettersBounds.at(second.x).at(second.y).getSize().x;
        _subsSelectedLinesBounds.push_back(rect2);
    }
}

std::wstring Subtitles::getSelectedString()
{
    swapSelection(_selectedTextRange.first, _selectedTextRange.second);

    std::wstring wstr{};

    for (int i{ 0 }; i < _text.size(); ++i)
    {
        std::wstring substr{};
        std::wstring sfstr = _text.at(i)->getString();

        if (i == _selectedTextRange.first.x)
        {
            std::wstring sfstr = _text.at(i)->getString();

            if (_selectedTextRange.first.x == _selectedTextRange.second.x)
            {
                if (_selectedTextRange.first.y == _selectedTextRange.second.y)
                    return wstr;

                substr = sfstr.substr(_selectedTextRange.first.y, _selectedTextRange.second.y - _selectedTextRange.first.y + 1);
                wstr += substr;

                return wstr;
            }
            else
            {
                substr = sfstr.substr(_selectedTextRange.first.y, sfstr.size());
            }
        }
        else if (i == _selectedTextRange.second.x)
        {
            substr = L" " + sfstr.substr(0, _selectedTextRange.second.y + 1);
            wstr += substr;
            break;
        }
        else
            substr = L" " + sfstr.substr(_selectedTextRange.first.y, sfstr.size());

        wstr += substr;
    }

    return wstr;
}