#include "board.h"
#include "settings.h"
#include "keygen.h"
#include "collisiondetection.h"
#include "assetmanager.h"

Board::Board(): Area ( BOARD_MIN_BOUNDS, BOARD_VIEWPORT)
{
	Init();
}

Board::~Board()
{
}

void Board::Init()
{
	// Фон окна
	_bigRect.setFillColor(BOARD_BACK_COLOR);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

	_viewControl.isMoving = false;
	_selectedNodeID = NOT_SELECTED;
	_isNodeMoving = false;
}

void Board::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);

	window.draw(_bigRect);

	for (auto& i : _layers)
		_nodes.at(i)->Draw(window);
}

void Board::Update(sf::RenderWindow& window, float dt)
{
	//window.setView(_areaView);

	if (_viewControl.isMoving)
		moveView(window, dt);
	else if (_isNodeMoving)
		moveNode(window);
}

void Board::moveView(sf::RenderWindow& window, float dt)
{
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f delta = window.mapPixelToCoords(currentMousePos) - window.mapPixelToCoords(_viewControl.prevMousePos);

	_viewControl.prevMousePos = currentMousePos;
	_areaView.move(-delta * dt * BOARD_MOVE_SPEED);
}

void Board::setViewMoving(sf::RenderWindow& window, bool isMoving)
{ 
	_viewControl.isMoving = isMoving; 

	if (isMoving)
		_viewControl.prevMousePos = sf::Mouse::getPosition(window);
};

void Board::zoomView(sf::RenderWindow& window, float dt_zoom, float dt)
{
	float zoom_factor;

	if (dt_zoom > 0)
		zoom_factor = 1.f - dt * BOARD_ZOOM_SPEED;
	else// if (dt_zoom < 0)
		zoom_factor = 1.f + dt * BOARD_ZOOM_SPEED;

	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f zoom_center = window.mapPixelToCoords(currentMousePos, _areaView);

	sf::Vector2f view_center = _areaView.getCenter();
	view_center += (zoom_center - view_center) * (1 - zoom_factor);

	_areaView.setCenter(view_center);
	_areaView.zoom(zoom_factor);
}

void Board::selectNode(sf::RenderWindow& window)
{
	if (_nodes.empty())
		return;

	if(_selectedNodeID != NOT_SELECTED)
		_nodes.at(_selectedNodeID)->select(false);

	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	auto it = std::make_reverse_iterator(_layers.end());  // get reverse iterator to last element in vector

	while (it != std::make_reverse_iterator(_layers.begin()))
	{
		auto rect = _nodes.at(*it)->getRect();

		if (isColliding(worldPos, rect))
		{
			_nodes.at(*it)->select(true);

			_selectedNodeID = *it;
			// Change layers order
			auto it = std::find(_layers.begin(), _layers.end(), _selectedNodeID);
			_layers.erase(it);
			_layers.push_back(_selectedNodeID);

			return;
		}
		++it;
	}

	_selectedNodeID = NOT_SELECTED;
}

void Board::createStill(const Screenshot& screenshot)
{
	std::unique_ptr<Node> node = std::make_unique<Still>(screenshot);

	int id{ KeyGen::getKey() };

	while (_nodes.find(id) != _nodes.end())
		id = KeyGen::getKey();

	_nodes.emplace(id, std::move(node));
	_layers.push_back(id);
}

void Board::moveNode(sf::RenderWindow& window)
{
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	if (_selectedNodeID != NOT_SELECTED)
	{
		sf::Vector2f pos;
		pos.x = worldPos.x;// - _movecontrol.selectPosShift.x + CARCASS_OUTLINE_THICKNESS;
		pos.y = worldPos.y;// -_movecontrol.selectPosShift.y + CARCASS_OUTLINE_THICKNESS;
		_nodes.at(_selectedNodeID)->setPosition(pos);
	}
}