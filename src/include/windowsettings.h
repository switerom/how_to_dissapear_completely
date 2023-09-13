#pragma once

#include "stdafx.h"
#include "settings.h"

class WindowSettings
{
private:
	sf::ContextSettings _settings;
	sf::Image icon;

public:
	WindowSettings();
	void Init();

	void initWindow(sf::RenderWindow& window);
};