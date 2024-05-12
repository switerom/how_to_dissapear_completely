#include "board.h"

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
	_control.isNodeMoving = false;
	_control.selectShift = sf::Vector2f(0.f, 0.f);
	_control.isCutting = false;
	_control.isLinePulled = false;
	_control.mousePos = sf::Vector2f(0.f, 0.f);
}

void Board::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);

	window.draw(_bigRect);

	for (auto& i : _layers)
		_nodes.at(i)->Draw(window);

	for (auto& i : _lines)
		window.draw(i.second->v, 4, sf::Quads);

	if (_control.isLinePulled)
		window.draw(_pulledLine.v, 4, sf::Quads);
}

void Board::Update(sf::RenderWindow& window, float dt)
{
	//window.setView(_areaView);

	if (_viewControl.isMoving)
		moveView(window, dt);
	else if (_control.isNodeMoving)
	{
		moveNode(window);
	}
	else if (_control.isLinePulled)
	{
		sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
		_control.mousePos = window.mapPixelToCoords(currentMousePos, _areaView);

		_pulledLine.moveLine(_control.pulledLineNodePos, _control.mousePos);
	}
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

			// нужно для того, чтобы каркасс перемещался ровно из того места, где его взяли
			_control.selectShift.x = worldPos.x - rect.left;
			_control.selectShift.y = worldPos.y - rect.top;

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

void Board::moveNode(sf::RenderWindow& window)
{
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	if (_selectedNodeID != NOT_SELECTED)
	{
		sf::Vector2f pos;
		pos.x = worldPos.x -_control.selectShift.x + NODE_OUTLINE_THK;
		pos.y = worldPos.y -_control.selectShift.y + NODE_OUTLINE_THK;
		_nodes.at(_selectedNodeID)->setPosition(pos);
	}

	// Move all lines connected to moved node
	for (auto& line : _lines)
	{
		if (line.first.src == _selectedNodeID || line.first.dest == _selectedNodeID)
		{
			sf::Vector2f point1 = sf::Vector2f(_nodes.at(line.first.src)->getRect().left, _nodes.at(line.first.src)->getRect().top);
			sf::Vector2f point2 = sf::Vector2f(_nodes.at(line.first.dest)->getRect().left, _nodes.at(line.first.dest)->getRect().top);

			line.second->moveLine(point1, point2);
		}
	}
}

void Board::deleteNode()
{
	if (_selectedNodeID == NOT_SELECTED)
		return;

	_nodes.erase(_selectedNodeID);

	//Remove edges
	for (auto it = _lines.begin(); it != _lines.end();)
	{
		if (it->first.src == _selectedNodeID || it->first.dest == _selectedNodeID)
		{
			it = _lines.erase(it);
		}
		else
			++it;
	}

	// Remove from layers
	auto it = std::find(_layers.begin(), _layers.end(), _selectedNodeID);
	_layers.erase(it);

	_selectedNodeID = NOT_SELECTED;
}

void Board::pullLine(sf::RenderWindow& window)
{
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	auto it = std::make_reverse_iterator(_layers.end());  // get reverse iterator to last element in vector

	while (it != std::make_reverse_iterator(_layers.begin()))
	{
		auto rect = _nodes.at(*it)->getRect();

		if (isColliding(worldPos, rect))
		{
			_control.isLinePulled = true;

			_control.pulledLineNode = *it;
			
			_control.pulledLineNodePos.x = _nodes.at(_control.pulledLineNode)->getRect().left;
			_control.pulledLineNodePos.y = _nodes.at(_control.pulledLineNode)->getRect().top;

			//if (_selectedNodeID != 0 && _selectedNodeID != nodeToConnect)
			//	addConnection(_selectedNodeID, nodeToConnect);
			//_selectedNodeID = NOT_SELECTED;
			return;
		}

		++it;
	}
}

void Board::releaseLine(const sf::RenderWindow& window)
{
	if (!_control.isLinePulled)
		return;

	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	auto it = std::make_reverse_iterator(_layers.end());  // get reverse iterator to last element in vector

	while (it != std::make_reverse_iterator(_layers.begin()))
	{
		auto rect = _nodes.at(*it)->getRect();

		if (isColliding(worldPos, rect))
		{
			int nodeToConnect = *it;

			if (_control.pulledLineNode != nodeToConnect)
				addConnection(_control.pulledLineNode, nodeToConnect);
			//_selectedNodeID = NOT_SELECTED;
			break;
		}

		++it;
	}

	_control.isLinePulled = false;
}

void Board::addConnection(int src, int dest)
{
	Edge edge{ src, dest };

	auto it = _lines.find(edge);
	if (it != _lines.end())
		return;

	sf::Vector2f point1 = sf::Vector2f(_nodes.at(edge.src)->getRect().left, _nodes.at(edge.src)->getRect().top);
	sf::Vector2f point2 = sf::Vector2f(_nodes.at(edge.dest)->getRect().left, _nodes.at(edge.dest)->getRect().top);

	auto line = std::make_unique<Line>();
	line->moveLine(point1, point2);
	_lines.emplace(edge, std::move(line));
}