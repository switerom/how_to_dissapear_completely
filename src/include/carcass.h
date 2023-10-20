#pragma once

#include "stdafx.h"


class Carcass
{
public:
	struct Interface
	{
		sf::RectangleShape background;
		sf::RectangleShape timeline;
		sf::RectangleShape delimiter;
		int delimiter_amt{};
		sf::Vector2f delimiter_pos;
	};

	Carcass(const sfe::Movie* video);

	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);

	sf::FloatRect getBounds() const { return _interface.background.getGlobalBounds(); };
	void setPosition(const sf::Vector2f& pos);

	const sfe::Movie* getVideo() const { return _video; };

private:

	Interface _interface;
	const sfe::Movie* _video;

	//std::map<int, sf::Sprite*> _nodes;
	//std::list<int> _layers;
};