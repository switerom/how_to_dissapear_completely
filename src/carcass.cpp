#include "carcass.h"
#include "settings.h"
#include "keygen.h"
#include "assetmanager.h"
#include "collisiondetection.h"

Carcass::Carcass(const sfe::Movie* video, const std::string& vid_name)
{
	_video = video;

	_selectedNode = nullptr;

	sf::Time _timeline = _video->getDuration();

	float width = _timeline.asSeconds() * TIMELINE_WIDTH_FACTOR;

	_interface.background.setFillColor(CARCASS_COLOR);
	_interface.background.setSize(sf::Vector2f(width, CARCASS_HEIGHT));
	_interface.background.setOutlineThickness(CARCASS_OUTLINE_THICKNESS);
	_interface.background.setOutlineColor(CARCASS_COLOR_UNSELECT);

	float timeline_width = width - TIMELINE_LEFT_INDENTATION * 2;

	_interface.timeline.setFillColor(TIMELINE_COLOR);
	_interface.timeline.setSize(sf::Vector2f(timeline_width, TIMELINE_HEIGHT));
	_interface.timeline.setPosition(TIMELINE_LEFT_INDENTATION, TIMELINE_TOP_INDENTATION);

	_interface.delimiter.setFillColor(DELIMITER_COLOR);
	_interface.delimiter.setSize(sf::Vector2f(DELIMITER_WIDTH, DELIMITER_HEIGHT));

	_interface.delimiter_pos = sf::Vector2f(DELIMITER_LEFT_INDENTATION, DELIMITER_TOP_INDENTATION);
	_interface.delimiter.setPosition(_interface.delimiter_pos.x, _interface.delimiter_pos.y);
	_interface.delimiter_amt = static_cast<int>(_timeline.asSeconds()) / DELIMITER_FREQUENCY;

	_interface.vid_name.setString(vid_name);
	_interface.vid_name.setFont(AssetManager::getFont(CARCASS_VID_NAME_FONT));
	_interface.vid_name.setCharacterSize(CARCASS_VID_NAME_SIZE);
	_interface.vid_name.setFillColor(CARCASS_VID_NAME_COLOR);
	_interface.vid_name.setPosition(sf::Vector2f(_interface.delimiter_pos.x, _interface.delimiter_pos.y - CARCASS_VID_NAME_POS_Y));
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

	for (auto& i : _layers)
	{
		_nodes.at(i)->Draw(window);
	}

	window.draw(_interface.vid_name);
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

	for (auto& i : _nodes)
	{
		i.second->setPosition(pos);
	}

	_interface.vid_name.setPosition(sf::Vector2f(_interface.delimiter_pos.x, _interface.delimiter_pos.y - CARCASS_VID_NAME_POS_Y));
}

void Carcass::addScreenshot(const Screenshot& screenshot)
{
	Node* node = new Node(screenshot, _interface.delimiter_pos);

	int key = KeyGen::getKey();

	_nodes.emplace(key, node);

	_layers.push_back(key);
}

bool Carcass::selectNode(const sf::Vector2f& mousePos)
{	
	if (_nodes.empty())
		return false;

	auto it = _nodes.begin();  // reverse итератор потому, что мы в конце находится слой, который выше отображается

	while (it != _nodes.end())
	{
		sf::FloatRect bounds = it->second->getBounds();

		if (isColliding(mousePos, bounds))
		{
			if(_selectedNode)
				_selectedNode->select(false);

			_selectedNode = it->second;
			it->second->select(true);

			return true;
		}
		++it;
	}

	if (_selectedNode)
		_selectedNode->select(false);

	_selectedNode = NOT_SELECTED;

	return false;
}

void Carcass::select(bool s)
{
	if (s)
	{
		_interface.background.setOutlineColor(NODE_COLOR_SELECT);
	}
	else
	{
		_interface.background.setOutlineColor(NODE_COLOR_UNSELECT);

		if(_selectedNode)
			_selectedNode->select(false);
	}
}
