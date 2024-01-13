#include "exploreritem.h"
#include "settings.h"
#include "stdafx.h"

ExplorerItem::ExplorerItem(const std::string& str, unsigned int id, float playTime)
{
    Init(str, id, playTime);
}

void ExplorerItem::Init(const std::string& str, unsigned int id, float playTime)
{
    _id = id;

    _text.setString(str);

    _bounds.top = _id * EXPLORER_ITEM_SIZE_Y;
    _bounds.left = 0.f;
    _bounds.width = WIDTH;
    _bounds.height = EXPLORER_ITEM_SIZE_Y;

    _text.setPosition(0.f, _bounds.top);

    static sf::Font font;
    font.loadFromFile(EXPLORER_ITEM_FONT);

    _text.setFont(font);
    _text.setCharacterSize(EXPLORER_ITEM_TEXT_SIZE);
    _text.setFillColor(EXPLORER_ITEM_TEXT_COLOR);

    bool _selected = false;
    _playTime = sf::seconds(playTime);
}

void ExplorerItem::setSelect(bool select)
{
    _selected = select;
}
