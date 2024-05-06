#include "sample.h"


Sample::Sample(const sf::Vector2f& pos, const Audio& audio)
{
	_pos = pos;
	_text.setString(audio.wstr);
	_text.setCharacterSize(SUBS_SIZE);
	_text.setFillColor(SUBS_COLOR);
	_text.setFont(AssetManager::getFont(SUBS_FONT));
	_text.setPosition(_pos);

	_select_frame.setPosition(_pos);
	_select_frame.setSize(sf::Vector2f(_text.getGlobalBounds().width, _text.getGlobalBounds().height*2.f));
}

void Sample::Draw(sf::RenderWindow& window) const
{
	window.draw(_select_frame);
	window.draw(_text);
}

void Sample::Update(float dt)
{

}

void Sample::setPosition(const sf::Vector2f& pos)
{
	_pos = pos;
	_text.setPosition(_pos);
	_select_frame.setPosition(_pos);
}