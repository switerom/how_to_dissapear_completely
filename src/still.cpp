#include "still.h"

Still::Still(const Screenshot& screenshot)
{
	_tex = screenshot.tex;
	_spr.setTexture(_tex);
	_spr.setPosition(_pos);
	_spr.setTextureRect(screenshot.frame);

	float crop_factor = findCropFactor(sf::Vector2f(screenshot.frame.width, screenshot.frame.height), NODE_SIZE);
	_spr.setScale(crop_factor, crop_factor);
	_select_frame.setPosition(_pos);
	_select_frame.setSize(sf::Vector2f(_spr.getGlobalBounds().width, _spr.getGlobalBounds().height));
}

void Still::Draw(sf::RenderWindow& window) const
{
	window.draw(_select_frame);
	window.draw(_spr);
}

void Still::Update(float dt)
{
	//_spr.setPosition(_pos);
}

/*
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

	setSpriteScale(rect);
}
*/