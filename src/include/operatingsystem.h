#pragma once 

#include "stdafx.h"
#include "node.h"

class OperatingSystem
{
public:
	OperatingSystem();
	void DrawOverlay(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);
	void startDrag(bool is_draggging);
	const std::unique_ptr<Node>& drop();

private:
	std::unique_ptr<Node> _dragDropNode;
};