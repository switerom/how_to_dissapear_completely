#pragma once

#include "stdafx.h"
#include "settings.h"

struct Line
{
	bool _isSelected;
	bool _isPartSelected;
	sf::Vertex v[4];
	sf::Vertex v_collision[4];

	Line();

	void moveLine(const sf::Vector2f& point1, const sf::Vector2f& point2);

	sf::Vector2f calculateOffset(const sf::Vector2f& point1, const sf::Vector2f& point2);

	void select(bool is_select);
	//void selectPart(bool is_select, const sf::Vertex2f& node_pos);
};