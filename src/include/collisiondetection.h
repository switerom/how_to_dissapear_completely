#pragma once

#include "stdafx.h"
#include "explorer.h"
#include "area.h"

bool isColliding(const sf::RenderWindow& window, const Area& area);

bool isColliding(const sf::RenderWindow& window, const Area& area, const sf::FloatRect& rect);

bool isColliding(const sf::RenderWindow& window, const sf::View& itemsView, const ExplorerItem& item);

bool isColliding(const sf::RenderWindow& window, const sf::View& view);

bool isColliding(const sf::Vector2f& worldPos, const  sf::FloatRect& rect);
