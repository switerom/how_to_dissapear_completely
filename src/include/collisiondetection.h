#pragma once

#include "stdafx.h"
#include "explorer.h"
#include "area.h"

bool isColliding(const sf::RenderWindow& window, const Area& area);

bool isColliding(const sf::RenderWindow& window, const Area& area, const sf::FloatRect& rect);

bool isColliding(const sf::RenderWindow& window, const Area& area, const std::vector<sf::FloatRect>& rects);

bool isColliding(const sf::RenderWindow& window, const sf::View& itemsView, const ExplorerItem& item);

bool isColliding(const sf::RenderWindow& window, const sf::View& view);

bool isColliding(const sf::Vector2f& worldPos, const  sf::FloatRect& rect);

bool isColliding(const sf::Vector2f& mouse_pos, const sf::Vertex v[4]);

bool isColliding(const  sf::FloatRect& rect1, const  sf::FloatRect& rect2);