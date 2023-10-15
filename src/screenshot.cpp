#include "Screenshot.h"
#include "settings.h"
#include "AssetManager.h"

Screenshot::Screenshot()
{
	Init();
}

void Screenshot::Init()
{
	_lines.lineX1.setSize(sf::Vector2f(SCREENSHOT_LINE_THK, HEIGHT));
	_lines.lineX1.setFillColor(SCREENSHOT_LINES_COLOR_A);
	_lines.lineY1.setSize(sf::Vector2f(WIDTH, SCREENSHOT_LINE_THK));
	_lines.lineY1.setFillColor(SCREENSHOT_LINES_COLOR_A);

	_lines.lineX2.setSize(sf::Vector2f(SCREENSHOT_LINE_THK, HEIGHT));
	_lines.lineX2.setFillColor(SCREENSHOT_LINES_COLOR_A);
	_lines.lineY2.setSize(sf::Vector2f(WIDTH, SCREENSHOT_LINE_THK));
	_lines.lineY2.setFillColor(SCREENSHOT_LINES_COLOR_A);

	_inProcess = false;
}

void Screenshot::moveLines(sf::RenderWindow& window, const sf::View& areaView)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(mouse_pos, areaView);

	_lines.lineX1.setPosition(worldPos.x, 0.f);
	_lines.lineY1.setPosition(0.f, worldPos.y);
}

void Screenshot::Draw(sf::RenderWindow& window)
{
	//window.draw(_spr);
	window.draw(_lines.lineX1);
	window.draw(_lines.lineY1);

	if (_inProcess)
	{
		_lines.lineX2.setPosition(static_cast<float>(_frame.left), 0.f);
		_lines.lineY2.setPosition(0.f, static_cast<float>(_frame.top));

		window.draw(_lines.lineX2);
		window.draw(_lines.lineY2);
	}
}

void Screenshot::Update(float dt)
{

}

void Screenshot::takeScreenshot(sf::RenderWindow& window, const sfe::Movie* vid, const sf::View& areaView)
{
	_lines.lineX1.setFillColor(SCREENSHOT_LINES_COLOR_B);
	_lines.lineY1.setFillColor(SCREENSHOT_LINES_COLOR_B);

	_lines.lineX2.setFillColor(SCREENSHOT_LINES_COLOR_B);
	_lines.lineY2.setFillColor(SCREENSHOT_LINES_COLOR_B);

	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(mouse_pos, areaView);

	if (!_inProcess)
	{
		_frame.left = static_cast<int>(worldPos.x);
		_frame.top = static_cast<int>(worldPos.y);
		_inProcess = true;
	}
	else
	{
		_frame.width = static_cast<int>(worldPos.x) - _frame.left;
		_frame.height = static_cast<int>(worldPos.y) - _frame.top;

		if (_frame.width < 0)
		{
			_frame.left = static_cast<int>(worldPos.x);
			_frame.width = -_frame.width;
		}
		if (_frame.height < 0)
		{
			_frame.top = static_cast<int>(worldPos.y);
			_frame.height = -_frame.height;
		}

		resetScreenshot();

		if(vid)
			_screenshot = vid->getCurrentImage();

		_spr.setTexture(_screenshot);
		_spr.setTextureRect(_frame);
	}
}

void Screenshot::resetScreenshot()
{
	_inProcess = false;
	_lines.lineX1.setFillColor(SCREENSHOT_LINES_COLOR_A);
	_lines.lineY1.setFillColor(SCREENSHOT_LINES_COLOR_A);

	_lines.lineX2.setFillColor(SCREENSHOT_LINES_COLOR_A);
	_lines.lineY2.setFillColor(SCREENSHOT_LINES_COLOR_A);
}



