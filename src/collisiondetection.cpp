#include "collisiondetection.h"

bool isColliding(sf::Vector2i mousePos, sf::FloatRect boxRect) 
{
    // Convert mouse position to sf::Vector2f
    sf::Vector2f mousePosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Check if the FloatRect contains the mouse position
    return boxRect.contains(mousePosition);
}