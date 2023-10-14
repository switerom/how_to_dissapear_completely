#include "area.h"
#include "settings.h"
#include "explorer.h"

Area::Area(const sf::FloatRect& minBounds, const sf::FloatRect& viewport)
{
	Init(minBounds, viewport);
}

void Area::Init(const sf::FloatRect& minBounds, const sf::FloatRect& viewport)
{
	_minBounds = minBounds;
	// Верхняя рамка
	_topRect.setFillColor(WINDOW_FRAME_COLOR);
	_topRect.setSize(sf::Vector2f(WIDTH, WINDOW_TOP_RECT));

	// Размер окна
	_areaView.reset(viewport);	// так мы указываем, что вся область explorera будет отображаться
	_areaView.setViewport(_minBounds);	// так мы указываем, что отображаться должно в левой нижней четверти основного окна

	_isMaximized = false;
	_id = ID::None;
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
