#include "node.h"
#include "settings.h"

Node::Node(const Screenshot& screenshot, const sf::Vector2f& pos)
{
	_timestamp = screenshot.video->getPlayingOffset();
	_pos.x = pos.x + _timestamp.asSeconds() * TIMELINE_WIDTH_FACTOR - CARCASS_OUTLINE_THICKNESS;
	_pos.y = pos.y - CARCASS_OUTLINE_THICKNESS;

	sf::Vector2f spr_pos;
	spr_pos.x = _pos.x;
	spr_pos.y = pos.y + SCREENSHOT_POS_Y - CARCASS_OUTLINE_THICKNESS;

	_tex = screenshot.tex;
	_spr.setTexture(_tex);
	_spr.setPosition(spr_pos);

	setTexture(screenshot);

	_select_frame.setOutlineColor(NODE_COLOR_SELECT);
	_select_frame.setOutlineThickness(NODE_OUTLINE_THK);
	_select_frame.setPosition(spr_pos);
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

	setSpriteScale(rect);
}

void Node::setSpriteScale(const sf::IntRect& rect)
{
	float crop_factor = std::sqrt(SCREENSHOT_SIZE / (rect.width * rect.height));

	float new_width = rect.width * crop_factor;
	float new_height = rect.height * crop_factor;

	float new_x_size = new_width / rect.width;
	float new_y_size = new_height / rect.height;

	_spr.setScale(sf::Vector2f(new_x_size, new_y_size));

	// дублируем размер для рамки
	_select_frame.setSize(sf::Vector2f(new_width, new_height));
}

void Node::Update(float dt)
{
}

void Node::Draw(sf::RenderWindow& window)
{
	window.draw(_select_frame);
	window.draw(_spr);
}

void Node::setPosition(const sf::Vector2f& pos)
{
	_pos.x = pos.x + _timestamp.asSeconds() * TIMELINE_WIDTH_FACTOR;
	_pos.y = pos.y + SCREENSHOT_POS_Y;

	_spr.setPosition(_pos);
	_select_frame.setPosition(_pos);
}

