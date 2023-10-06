#include "explorer.h"
#include "stdafx.h"
#include "settings.h"

void Explorer::Init()
{
	_bigRect.setFillColor(sf::Color::Red);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

	_topRect.setFillColor(sf::Color::White);
	_topRect.setSize(sf::Vector2f(WIDTH, EXPLORER_TOP_RECT));

	_exView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться
	_exView.setViewport(sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));	// так мы указываем, что отображаться должно в левой нижней четверти основного окна
}

Explorer::Explorer()
{
	Init();
}

void Explorer::Draw(sf::RenderWindow& window)
{
	window.setView(_exView);	// применяем View, иначе будет на весь экран
	window.draw(_bigRect);
	window.draw(_topRect);


	//for (auto& i : _exItems)
	//{
	//	window.draw(i.getText());
	//}
}

void Explorer::Update(float dt)
{
}