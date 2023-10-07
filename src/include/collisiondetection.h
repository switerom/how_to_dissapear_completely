#include "stdafx.h"
#include "explorer.h"

bool isColliding(const sf::RenderWindow& window, const Explorer& explorer);

bool isColliding(const sf::RenderWindow& window, const Explorer& explorer, const sf::FloatRect& topBoxRect);

bool isColliding(const sf::RenderWindow& window, sf::View itemsView, const ExplorerItem& item);