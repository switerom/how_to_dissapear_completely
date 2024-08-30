#pragma once

#include "stdafx.h"
#include "settings.h"

struct Line
{
	bool _isSelectedSrc;
	bool _isSelectedDest;
	sf::Vertex v[4];
	sf::Vertex v_collision[4];

	Line();

	void moveLine(const sf::Vector2f& point1, const sf::Vector2f& point2);

	sf::Vector2f calculateOffset(const sf::Vector2f& point1, const sf::Vector2f& point2);

	void select(bool is_select);
	void selectPartSrc(bool is_select);
	void selectPartDest(bool is_select);
};