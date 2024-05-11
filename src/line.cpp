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
	v[0].color = LINE_COLOR;
	v[1].color = LINE_COLOR;
	v[2].color = LINE_COLOR;
	v[3].color = LINE_COLOR;
}

void Line::moveLine(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
	auto offset = calculateOffset(point1, point2);

	v[0].position = sf::Vector2f(point1 + offset);
	v[1].position = sf::Vector2f(point2 + offset);
	v[2].position = sf::Vector2f(point2 - offset);
	v[3].position = sf::Vector2f(point1 - offset);
}
