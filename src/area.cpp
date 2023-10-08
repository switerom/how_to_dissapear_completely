#include "area.h"
#include "settings.h"
#include "explorer.h"

Area::Area(const sf::FloatRect& minBounds)
{
	Init(minBounds);
}

void Area::Init(const sf::FloatRect& minBounds)
{
	_minBounds = minBounds;
	// Верхняя рамка
	_topRect.setFillColor(WINDOW_FRAME_COLOR);
	_topRect.setSize(sf::Vector2f(WIDTH, WINDOW_TOP_RECT));

	// Размер окна
	_areaView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться
	_areaView.setViewport(_minBounds);	// так мы указываем, что отображаться должно в левой нижней четверти основного окна

	_isMaximized = false;
}

void Area::toggleMaximize()
{
	if (_isMaximized)
	{
		_areaView.setViewport(_minBounds);

		_isMaximized = false;
	}
	else
	{
		_areaView.setViewport(WINDOW_MAX_BOUNDS);

		_isMaximized = true;
	}
}

void Area::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);
	window.draw(_topRect);
}
