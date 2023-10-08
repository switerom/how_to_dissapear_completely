#include "areacontroller.h"

AreaController::AreaController(std::initializer_list<Area*> areas)
{
	Init(areas);
}

void AreaController::Init(std::initializer_list<Area*> areas)
{
	for (auto& area : areas)
	{
		_areas.push_back(area);
	}
}

void AreaController::Draw(sf::RenderWindow& window)
{
	for (auto& area : _areas)
	{
		area->Draw(window);
	}
}

void AreaController::Update(float dt)
{
	for (auto& area : _areas)
	{
		area->Update(dt);
	}
}