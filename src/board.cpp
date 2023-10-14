#include "board.h"
#include "settings.h"

Board::Board(): Area ( BOARD_MIN_BOUNDS, BOARD_VIEWPORT)
{
	Init();
}

void Board::Init()
{
	// Фон окна
	_bigRect.setFillColor(BOARD_BACK_COLOR);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT * 0.25));

	_viewControl.isMoving = false;
}

void Board::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);

	window.draw(_bigRect);
}

void Board::Update(sf::RenderWindow& window, float dt)
{
	//window.setView(_areaView);

	moveView(window, dt);
}

void Board::moveView(sf::RenderWindow& window, float dt)
{
	if (_viewControl.isMoving)
	{
		sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
		sf::Vector2f delta = window.mapPixelToCoords(currentMousePos) - window.mapPixelToCoords(_viewControl.prevMousePos);
						

		_viewControl.prevMousePos = currentMousePos;
		_areaView.move(-delta * dt * BOARD_MOVE_SPEED);
	}
}

void Board::setViewMoving(sf::RenderWindow& window, bool isMoving)
{ 
	_viewControl.isMoving = isMoving; 

	if (isMoving)
		_viewControl.prevMousePos = sf::Mouse::getPosition(window);
};