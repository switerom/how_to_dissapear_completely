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

	_maximized = AreaID::None;
}

void AreaController::Draw(sf::RenderWindow& window)
{
	for (auto& area : _areas)
	{
		if (area->isMaximized())
		{
			_maximized = area->getAreaID();
			area->Draw(window);
		}
	}

	if (_maximized == AreaID::None)
	{
		for (auto& area : _areas)
		{
			area->Draw(window);
		}
	}
}

void AreaController::Update(float dt)
{
	for (auto& area : _areas)
	{
		if (area->isMaximized())
		{
			_maximized = area->getAreaID();
			area->Update(dt);
		}
	}

	if (_maximized == AreaID::None)
	{
		for (auto& area : _areas)
		{
			area->Update(dt);
		}
	}
}

void AreaController::setAreaID(AreaID area)
{
	_maximized = area;
}
