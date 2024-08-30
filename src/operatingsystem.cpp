#include "operatingsystem.h"

OperatingSystem::OperatingSystem()
{
	_dragDropNode = nullptr;
}

void OperatingSystem::DrawOverlay(sf::RenderWindow& window)
{
	//_dragDropNode->Draw(window);
}

void OperatingSystem::Draw(sf::RenderWindow& window)
{

}

void OperatingSystem::Update(sf::RenderWindow& window, float dt)
{

}

void OperatingSystem::startDrag(bool is_drag)
{

}

const std::unique_ptr<Node>& OperatingSystem::drop()
{
	return _dragDropNode;
}