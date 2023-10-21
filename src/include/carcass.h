#pragma once

#include "stdafx.h"
#include "node.h"

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
		sf::Text vid_name;
	};

	Carcass(const sfe::Movie* video, const std::string& vid_name);

	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);

	sf::FloatRect getBounds() const { return _interface.background.getGlobalBounds(); };
	void setPosition(const sf::Vector2f& pos);

	const sfe::Movie* getVideo() const { return _video; };

	void addScreenshot(const Screenshot& screenshot);

	bool selectNode(const sf::Vector2f& mousePos);

	void select(bool s);

private:
	Interface _interface;
	const sfe::Movie* _video;

	std::map<int, Node*> _nodes;
	std::list<int> _layers;

	Node* _selectedNode;
};