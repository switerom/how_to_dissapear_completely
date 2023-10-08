#include "collisiondetection.h"
#include "explorer.h"
#include "settings.h"

bool isColliding(const sf::RenderWindow& window, const Area& area)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    auto exView = area.getAreaView();

    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, exView);

    auto areaRect = sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT);

    // Check if the FloatRect contains the mouse position
    return areaRect.contains(mousePosView);
}

bool isColliding(const sf::RenderWindow& window, const Area& area, const sf::FloatRect& topBoxRect)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    auto areaView = area.getAreaView();

    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, areaView);

    // Check if the FloatRect contains the mouse position
    return topBoxRect.contains(mousePosView);
}

bool isColliding(const sf::RenderWindow& window, sf::View itemsView, const ExplorerItem& item)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, itemsView);

    auto itemBounds= item.getItemBounds();

    return itemBounds.contains(mousePosView);;
}