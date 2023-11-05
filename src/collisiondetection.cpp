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

bool isColliding(const sf::RenderWindow& window, const Area& area, const sf::FloatRect& rect)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    auto areaView = area.getAreaView();

    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, areaView);

    // Check if the FloatRect contains the mouse position
    return rect.contains(mousePosView);
}

bool isColliding(const sf::RenderWindow& window, const Area& area, const std::vector<sf::FloatRect>& rects)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    auto areaView = area.getAreaView();

    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, areaView);

    // Check if the vector of FloatRects contains the mouse position
    for (auto& i : rects)
    {
        if (i.contains(mousePosView))
            return true;
    }

    return false;
}

bool isColliding(const sf::RenderWindow& window, const sf::View& itemsView, const ExplorerItem& item)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, itemsView);

    auto itemBounds= item.getItemBounds();

    return itemBounds.contains(mousePosView);;
}

bool isColliding(const sf::RenderWindow& window, const sf::View& view)
{
    sf::FloatRect viewport = view.getViewport();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    return  (mousePos.x >= window.getSize().x * viewport.left) &&
            (mousePos.x <= window.getSize().x * (viewport.left + viewport.width)) &&
            (mousePos.y >= window.getSize().y * viewport.top) &&
            (mousePos.y <= window.getSize().y * (viewport.top + viewport.height));
}

bool isColliding(const sf::Vector2f& worldPos, const  sf::FloatRect& rect)
{
    return  (worldPos.x >= rect.left) &&
            (worldPos.x <= (rect.left + rect.width)) &&
            (worldPos.y >= rect.top) &&
            (worldPos.y <= rect.top + rect.height);
}