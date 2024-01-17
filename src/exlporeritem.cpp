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

    _bounds.top = _id / EXPLORER_ITEM_RAWS * EXPLORER_ITEM_HEIGHT;

    auto var = (_id + 1) % EXPLORER_ITEM_RAWS;

    if(_id != 0)
        _bounds.left = (_id % EXPLORER_ITEM_RAWS) * EXPLORER_ITEM_WIDTH;
    else
        _bounds.left = 0.f;

    _bounds.width = EXPLORER_ITEM_WIDTH;
    _bounds.height = EXPLORER_ITEM_HEIGHT;

    _text.setPosition(_bounds.left, _bounds.top);

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
