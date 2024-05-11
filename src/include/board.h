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
#include "line.h"

class Board: public Area
{
public:
	struct ViewCnotrol
	{
		sf::Vector2i prevMousePos;
		bool isMoving;
	};

	struct Control
	{
		bool isNodeMoving;
		sf::Vector2f selectShift;
		bool isLinePulled;
		bool isCutting;
		sf::Vector2f mousePos;
		sf::Vector2f pulledLineNodePos;
	};

	struct Edge
	{
		int src;
		int dest;

		// чтобы могло быть ключом во второй мапе(отвечающей за линии)
		bool operator<(const Edge& other) const
		{
			if (src < other.src) {
				return true;
			}
			else if (src == other.src) {
				return dest < other.dest;
			}
			else {
				return false;
			}
		}
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
	void setNodeMoving(bool isNodeMoving) { _control.isNodeMoving = isNodeMoving; };
	void moveNode(sf::RenderWindow& window);

	//void createLine(const sf::Vector2f& point1, const sf::Vector2f& point2);
	void pullLine(sf::RenderWindow& window);
	void releaseLine();

private:
	sf::View _boardView;
	sf::RectangleShape _bigRect;
	ViewCnotrol _viewControl;
	Control _control;

	std::map<int, std::unique_ptr<Node>> _nodes;
	std::list<int> _layers;
	std::vector<Edge> _edge;
	int _selectedNodeID;
	std::map<Edge, std::unique_ptr<Edge>> _lines;
	Line _pulledLine;
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
