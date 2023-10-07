#include "collisiondetection.h"
#include "explorer.h"

bool isColliding(const sf::RenderWindow& window, const Explorer& explorer)
{

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    auto exView = explorer.getExplorerView();

    sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, exView);

    auto topBoxRect = explorer.getTopBoxRect();

    // Check if the FloatRect contains the mouse position
    return topBoxRect.contains(mousePosView);
}