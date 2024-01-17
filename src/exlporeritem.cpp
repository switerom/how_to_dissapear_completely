#include "exploreritem.h"

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

    // Set preview texture to a sprite
    // Preview name contains video name + timing
    std::string previewFileName{ str };
    size_t pos = str.find('.');  

    if (pos != std::string::npos) 
    {
        previewFileName = str.substr(0, pos) + "_" + std::to_string(static_cast<int>(playTime)) + PREVIEW_FORMAT;
        previewFileName = PREVIEW_DIR + previewFileName;

        _spr.setTexture(AssetManager::getTexture(previewFileName));

        sf::Vector2f img_size{ sf::Vector2f(_spr.getTextureRect().width, _spr.getTextureRect().height) };
        sf::Vector2f frame_size{ EXPLORER_ITEM_WIDTH, EXPLORER_ITEM_HEIGHT };
        float crop_factor = findCropFactor(img_size, frame_size);
        _spr.setScale(crop_factor, crop_factor);

        shiftImagePos(_spr, sf::FloatRect(_bounds.left, _bounds.top, EXPLORER_ITEM_WIDTH, EXPLORER_ITEM_HEIGHT));
    }
}

void ExplorerItem::setSelect(bool select)
{
    _selected = select;
}

void ExplorerItem::Draw(sf::RenderWindow& window) const const
{
    window.draw(_text);

    if (_spr.getTexture() != NULL)
        window.draw(_spr);
}

