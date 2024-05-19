#include "line.h"

sf::Vector2f Line::calculateOffset(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
	// calculate the perpendicular vector to the line
	sf::Vector2f direction = point2 - point1;
	sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

	// calculate the offset needed to create a line with the given thickness
	float thickness = LINE_THICKNESS;
	sf::Vector2f offset = (thickness / 2.0f) * unitPerpendicular;

	return offset;
}

Line::Line()
{
	v[0].color = LINE_COLOR_A;
	v[1].color = LINE_COLOR_A;
	v[2].color = LINE_COLOR_A;
	v[3].color = LINE_COLOR_A;

	_isSelected = false;
	_isPartSelected = false;
}

void Line::moveLine(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
	auto offset = calculateOffset(point1, point2);

	v[0].position = sf::Vector2f(point1 + offset);
	v[1].position = sf::Vector2f(point2 + offset);
	v[2].position = sf::Vector2f(point2 - offset);
	v[3].position = sf::Vector2f(point1 - offset);

	v_collision[0].position = sf::Vector2f(point1 + LINE_COLLISION_THK * offset);
	v_collision[1].position = sf::Vector2f(point2 + LINE_COLLISION_THK * offset);
	v_collision[2].position = sf::Vector2f(point2 - LINE_COLLISION_THK * offset);
	v_collision[3].position = sf::Vector2f(point1 - LINE_COLLISION_THK * offset);
}

void Line::select(bool is_select)
{
	if (!is_select && !_isSelected
		|| is_select && _isSelected)
		return;

	if (is_select)
	{
		v[0].color = LINE_COLOR_B;
		v[1].color = LINE_COLOR_B;
		v[2].color = LINE_COLOR_B;
		v[3].color = LINE_COLOR_B;
	}
	else
	{
		v[0].color = LINE_COLOR_A;
		v[1].color = LINE_COLOR_A;
		v[2].color = LINE_COLOR_A;
		v[3].color = LINE_COLOR_A;
	}

	_isSelected = is_select;
}
/*
void Line::selectPart(bool is_select)
{
	if (!is_select && !_isPartSelected
		|| is_select && _isPartSelected)
		return;

	if (is_select)
	{
		v[0].color = LINE_COLOR_B;
		v[3].color = LINE_COLOR_B;
	}
	else
	{
		v[0].color = LINE_COLOR_A;
		v[3].color = LINE_COLOR_A;
	}

	_isPartSelected = is_select;
}
*/