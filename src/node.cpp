#include "node.h"
#include "settings.h"

Node::Node(const Screenshot& screenshot, const sf::Vector2f& pos)
{
	_timestamp = screenshot.video->getPlayingOffset();
	_pos.x = pos.x + _timestamp.asSeconds() * TIMELINE_WIDTH_FACTOR - CARCASS_OUTLINE_THICKNESS;
	_pos.y = pos.y - CARCASS_OUTLINE_THICKNESS;

	_tex = screenshot.tex;
	_spr.setTexture(_tex);
	_spr.setPosition(_pos.x, _pos.y);

	setTexture(screenshot);
}

void Node::setTexture(const Screenshot& screenshot)
{
	auto rect = screenshot.frame;
	int temp;

	if (rect.width < 0)
	{
		temp = rect.width;
		rect.width = -rect.width;
		rect.left = temp + rect.left;;
	}
	if (rect.height < 0)
	{
		temp = rect.height;
		rect.height = -rect.height;
		rect.top = temp + rect.top;
	}

	_spr.setTextureRect(rect);
}

void Node::Update(float dt)
{
}

void Node::Draw(sf::RenderWindow& window)
{
	window.draw(_spr);
}

void Node::setPosition(const sf::Vector2f& pos)
{
	// добавить, чтобы позиция менялась в зависимости от позиции доски
	_pos.x = pos.x + _timestamp.asSeconds() * TIMELINE_WIDTH_FACTOR;
	_pos.y = pos.y;

	_spr.setPosition(_pos);
}

