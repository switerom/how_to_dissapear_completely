#pragma once

#include "stdafx.h"
#include "settings.h"

struct Line
{
	sf::Vertex v[4];

	Line();

	void moveLine(const sf::Vector2f& point1, const sf::Vector2f& point2);

	sf::Vector2f calculateOffset(const sf::Vector2f& point1, const sf::Vector2f& point2);
};