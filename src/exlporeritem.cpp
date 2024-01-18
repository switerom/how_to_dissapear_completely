#include "exploreritem.h"

ExplorerItem::ExplorerItem(const std::string& str, unsigned int id, float playTime, bool exists)
{
    Init(str, id, playTime, exists);
}

void ExplorerItem::Init(const std::string& str, unsigned int id, float playTime, bool exists)
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

    _text.setPosition(_bounds.left + EXPLORER_ITEM_TEXT_POS_X, _bounds.top + EXPLORER_ITEM_TEXT_POS_Y);

    static sf::Font font;
    font.loadFromFile(EXPLORER_ITEM_FONT);

    _text.setFont(font);
    _text.setCharacterSize(EXPLORER_ITEM_TEXT_SIZE);
    _text.setFillColor(EXPLORER_ITEM_TEXT_COLOR);

    _timeText.setFont(font);
    _timeText.setCharacterSize(EXPLORER_ITEM_TEXT_SIZE);
    _timeText.setFillColor(EXPLORER_ITEM_TEXT_COLOR);
    _timeText.setString(convertToTime(playTime));
    _timeText.setPosition(_bounds.left + EXPLORER_ITEM_TIME_POS_X, _bounds.top + EXPLORER_ITEM_TIME_POS_Y);

    bool _selected = false;

    if(exists)
        _playTime = sf::seconds(0.f);
    else
        _playTime = sf::seconds(playTime);

    std::string fileName = getPreviewFullPath(str, playTime);
    fitPreview(fileName);
}

std::string ExplorerItem::getPreviewFullPath(std::string filename, float playTime)
{
    size_t pos = filename.find('.');

    if (pos == std::string::npos)
        return "";

    filename = filename.substr(0, pos) + "_" + std::to_string(static_cast<int>(playTime)) + PREVIEW_FORMAT;
    filename = PREVIEW_DIR + filename;
    return filename;
}


void ExplorerItem::fitPreview(const std::string& filename)
{
    if (filename == "")
        return;

    const sf::Texture* tex = AssetManager::getTexture(filename);

    if (tex == nullptr)
        return;

    _spr.setTexture(*tex);

    sf::Vector2f img_size{ sf::Vector2f(_spr.getTextureRect().width, _spr.getTextureRect().height) };
    sf::Vector2f frame_size{ PREVIEW_WIDTH, PREVIEW_HEIGHT };

    float crop_factor = findCropFactor(img_size, frame_size);

    _spr.setScale(crop_factor, crop_factor);
    shiftImagePos(_spr, sf::FloatRect(_bounds.left + PREVIEW_POS_X, _bounds.top + PREVIEW_POS_Y, PREVIEW_WIDTH, PREVIEW_HEIGHT));
}

void ExplorerItem::setSelect(bool select)
{
    _selected = select;
}

void ExplorerItem::Draw(sf::RenderWindow& window) const const
{
    window.draw(_text);
    window.draw(_timeText);

    if (_spr.getTexture() != NULL)
        window.draw(_spr);
}

