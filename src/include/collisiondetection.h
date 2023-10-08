#include "stdafx.h"
#include "explorer.h"
#include "area.h"

bool isColliding(const sf::RenderWindow& window, const Area& area);

bool isColliding(const sf::RenderWindow& window, const Area& area, const sf::FloatRect& rect);

bool isColliding(const sf::RenderWindow& window, sf::View itemsView, const ExplorerItem& item);
