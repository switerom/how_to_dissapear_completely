#include "exploreritem.h"
#include "settings.h"
#include "stdafx.h"

ExplorerItem::ExplorerItem(const std::string& str, unsigned int id)
{
    Init(str, id);
}

void ExplorerItem::Init(const std::string& str, unsigned int id)
{
    _id = id;

    _text.setString(str);

    _text.setPosition(0.f, _id * EXPLORER_ITEM_SIZE_Y);

    static sf::Font font;
    font.loadFromFile(EXPLORER_ITEM_FONT);

    _text.setFont(font);
    _text.setCharacterSize(EXPLORER_ITEM_TEXT_SIZE);
    _text.setFillColor(EXPLORER_ITEM_TEXT_COLOR);
}