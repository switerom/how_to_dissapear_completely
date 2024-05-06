#include "still.h"

Still::Still(const sf::Vector2f& pos, const Screenshot& screenshot)
{
	_pos = pos;
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

}
void Still::setPosition(const sf::Vector2f& pos)
{
	_pos = pos;
	_spr.setPosition(_pos);
	_select_frame.setPosition(_pos);
}
