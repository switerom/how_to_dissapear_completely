#include "carcass.h"
#include "settings.h"

Carcass::Carcass(sf::Time timeline)
{
	_timeline = timeline;

	float width = _timeline.asSeconds() * TIMELINE_WIDTH_FACTOR;

	_interface.background.setFillColor(CARCASS_COLOR);
	_interface.background.setSize(sf::Vector2f(width, CARCASS_HEIGHT));
	_interface.background.setOutlineThickness(CARCASS_OUTLINE_THICKNESS);
	_interface.background.setOutlineColor(CARCASS_OUTLINE_COLOR);

	float timeline_width = width - TIMELINE_LEFT_INDENTATION * 2;

	_interface.timeline.setFillColor(TIMELINE_COLOR);
	_interface.timeline.setSize(sf::Vector2f(timeline_width, TIMELINE_HEIGHT));
	_interface.timeline.setPosition(TIMELINE_LEFT_INDENTATION, TIMELINE_TOP_INDENTATION);

	_interface.delimiter.setFillColor(DELIMITER_COLOR);
	_interface.delimiter.setSize(sf::Vector2f(DELIMITER_WIDTH, DELIMITER_HEIGHT));

	_interface.delimiter_pos = sf::Vector2f(DELIMITER_LEFT_INDENTATION, DELIMITER_TOP_INDENTATION);
	_interface.delimiter.setPosition(_interface.delimiter_pos.x, _interface.delimiter_pos.y);
	_interface.delimiter_amt = static_cast<int>(_timeline.asSeconds()) / DELIMITER_FREQUENCY;
}

void Carcass::Draw(sf::RenderWindow& window)
{
	window.draw(_interface.background);
	window.draw(_interface.timeline);

	int next_delimiter_identation = 0;

	for (int i{ 0 }; i < _interface.delimiter_amt; ++i)
	{
		sf::Vector2f nextPos(	_interface.delimiter_pos.x + next_delimiter_identation,
								_interface.delimiter_pos.y);

		_interface.delimiter.setPosition(nextPos.x, nextPos.y);

		next_delimiter_identation += DELIMITER_FREQUENCY * TIMELINE_WIDTH_FACTOR;		// должно быть умножено на что-то

		window.draw(_interface.delimiter);
	}
}

void Carcass::Update(sf::RenderWindow& window, float dt)
{

}

void Carcass::setPosition(const sf::Vector2f& pos)
{
	_interface.background.setPosition(pos.x, pos.y);
	_interface.timeline.setPosition(pos.x + TIMELINE_LEFT_INDENTATION, 
									pos.y + TIMELINE_TOP_INDENTATION);

	_interface.delimiter_pos.x = pos.x + DELIMITER_LEFT_INDENTATION;
	_interface.delimiter_pos.y = pos.y + DELIMITER_TOP_INDENTATION;
}

 