#include <windowsettings.h>

WindowSettings::WindowSettings()
{
	Init();
}

// здесь настройки должны загружаться из сохранений
void WindowSettings::Init()
{
	_settings.antialiasingLevel = 8;
}

// здесь настройки должны загружаться из сохранений
void WindowSettings::initWindow(sf::RenderWindow& window)
{
	window.create(sf::VideoMode(WIDTH, HEIGHT), GAME_NAME, sf::Style::Default, _settings);	// заменить макросы на сохраненные настройки
	window.setVerticalSyncEnabled(true);
	//_window.setPosition(sf::Vector2i(10, 50));
	//_window.setSize(sf::Vector2u(WIDTH, HEIGHT));

	// Добавление иконки игры	
	//if (!icon.loadFromFile("C:/_FILES/how_to_dissapear_comletely/rsc/img/fingerprint.ico")) {
	//	// handle error
	//}
	//window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

