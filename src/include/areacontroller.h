#pragma once

#include "stdafx.h"
#include "Area.h"

class AreaController
{
public:
	AreaController(std::initializer_list<Area*> areas);

	void Init(std::initializer_list<Area*> areas);

	void Draw(sf::RenderWindow& window);
	void Update(float dt);

private:
	std::vector<Area*> _areas;
};