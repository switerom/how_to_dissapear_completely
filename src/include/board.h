#pragma once

#include "stdafx.h"
#include "area.h"
#include "node.h"
#include "still.h"
#include "timecontroller.h"
#include "collisiondetection.h"
#include "videoplayer.h"
#include "settings.h"
#include "keygen.h"
#include "assetmanager.h"

class Board: public Area
{
public:
	struct ViewCnotrol
	{
		sf::Vector2i prevMousePos;
		bool isMoving;
	};

	struct MoveControl
	{
		bool isNodeMoving;
		sf::Vector2f selectShift;
	};

	Board();
	~Board();
	void Init();
	virtual void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);

	void moveView(sf::RenderWindow& window, float dt);
	void setViewMoving(sf::RenderWindow& window, bool isMoving);
	void zoomView(sf::RenderWindow& window, float dt_zoom, float dt);

	template <typename T, typename... Args>
	void createNode(Args&&... args);

	void selectNode(sf::RenderWindow& window);
	void moveNode(bool is_move, sf::RenderWindow& window);
	void deleteNode(); 
	void setNodeMoving(bool isNodeMoving) { _movecontrol.isNodeMoving = isNodeMoving; };
	void moveNode(sf::RenderWindow& window);


private:

	sf::View _boardView;
	sf::RectangleShape _bigRect;
	ViewCnotrol _viewControl;
	MoveControl _movecontrol;

	std::map<int, std::unique_ptr<Node>> _nodes;
	std::list<int> _layers;
	//std::map<Edge, Line*> _lines;
	int _selectedNodeID;
};

template <typename T, typename... Args>
void Board::createNode(Args&&... args)
{
	std::unique_ptr<Node> node = std::make_unique<T>(_areaView.getCenter(), std::forward<Args>(args)...);
	int id{ KeyGen::getKey() };

	while (_nodes.find(id) != _nodes.end())
		id = KeyGen::getKey();

	_nodes.emplace(id, std::move(node));
	_layers.push_back(id);

	// Just created node will be selected
	if (_selectedNodeID != NOT_SELECTED)
		_nodes.at(_selectedNodeID)->select(false);

	_selectedNodeID = id;
	_nodes.at(id)->select(true);
}
