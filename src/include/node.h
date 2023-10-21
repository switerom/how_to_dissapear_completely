#pragma once

#include "stdafx.h"
#include "videoplayer.h"

class Node
{
public:
	Node(const Screenshot& screenshot, const sf::Vector2f& pos);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f& pos);
	void setTexture(const Screenshot& screenshot);
	void setSpriteScale();
	void setSpriteScale(const sf::IntRect& rect);

private:
	sf::Texture _tex;
	sf::Sprite _spr;
	sf::Text _text;
	sf::Vector2f _pos;
	sf::Time _timestamp;
};
