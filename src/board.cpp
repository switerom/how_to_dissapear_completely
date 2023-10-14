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
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

}

void Board::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);
	window.draw(_bigRect);
}

void Board::Update(float dt)
{
}