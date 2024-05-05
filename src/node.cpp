#include "node.h"
#include "settings.h"

Node::Node()
{
	_pos = sf::Vector2f(0.f,0.f);

	_select_frame.setPosition(_pos);
	_select_frame.setSize(sf::Vector2f(0.f, 0.f));
	_select_frame.setOutlineColor(NODE_UNSELECT_COLOR);
	_select_frame.setOutlineThickness(NODE_OUTLINE_THK);
}

void Node::setPosition(const sf::Vector2f& pos)
{
	_pos = pos;
	_select_frame.setPosition(_pos);
}

void Node::select(bool s) 
{ 
	if(s)
		_select_frame.setOutlineColor(NODE_SELECT_COLOR);
	else
		_select_frame.setOutlineColor(NODE_UNSELECT_COLOR);
};

const sf::FloatRect& Node::getRect() const
{
	return _select_frame.getGlobalBounds();
}



