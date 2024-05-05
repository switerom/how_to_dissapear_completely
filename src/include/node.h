#pragma once

#include "stdafx.h"
#include "videoplayer.h"

class Node
{
public:
	Node();
	virtual ~Node() {};
	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) const = 0;
	void setPosition(const sf::Vector2f& pos);
	void select(bool s);
	const sf::FloatRect& getRect() const;

protected:
	sf::Vector2f _pos;
	sf::RectangleShape _select_frame;
};
