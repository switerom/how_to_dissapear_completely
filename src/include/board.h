#pragma once

#include "stdafx.h"
#include "area.h"
#include "node.h"
#include "still.h"
#include "sample.h"
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
		bool isMulptipleSelect;
		bool isNodeMoving;
		bool isLinePulled;
		bool isCutting;
		bool selectInProcess;
		sf::Vector2f mousePos;
		sf::Vector2f prevMousePos;
		sf::Vector2f pulledLineNodePos;
		int pulledLineNode;
	};

	struct Edge
	{
		int src;
		int dest;

		// чтобы могло быть ключом во второй мапе(отвечающей за линии)
		bool operator<(const Edge& other) const
		{
			// Check if the edges are equivalent regardless of order
			if ((src == other.src && dest == other.dest) || (src == other.dest && dest == other.src))
			{
				return false; // Equivalent, so not less than
			}

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

		// Overload the == operator
		bool operator==(const Edge& other) const
		{
			// Check if the edges are equivalent regardless of order
			return (src == other.src && dest == other.dest) || (src == other.dest && dest == other.src);
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

	bool selectLine(sf::RenderWindow& window);
	void selectLinePart(int nodeID);
	void unselectRectLinePart(int nodeID);

	void unselectLinePart(int nodeID);
	bool selectNode(sf::RenderWindow& window);
	bool selectRectNode();
	bool unselectNode(int nodeID);
	bool unselectLine(Edge edge);
	void unselectEverything();

	void multipleSelect(bool is_select) { _control.isMulptipleSelect = is_select; };

	void moveNode(bool is_move, sf::RenderWindow& window);
	void deleteNode(); 
	void deleteLine();
	
	void setNodeMoving(bool isNodeMoving, const sf::RenderWindow& window);
	void moveNode(sf::RenderWindow& window);

	void pullLine(sf::RenderWindow& window);
	void releaseLine(const sf::RenderWindow& window);
	void addConnection(int src, int dest);

	void saveBoard();
	void loadBoard();

	void resetAction() override;

	void startSelectRect(bool is_select, const sf::RenderWindow& window);
	void setSelectRect(const sf::RenderWindow& window);

private:
	sf::RectangleShape _selectRect;
	sf::View _boardView;
	sf::RectangleShape _bigRect;
	ViewCnotrol _viewControl;
	Control _control;

	std::map<int, std::unique_ptr<Node>> _nodes;
	std::list<int> _layers;
	std::list<int> _selectedNodes;
	std::list<Edge> _selectedLines;
	std::list<Edge> _partiallySelectedLines;
	std::map<Edge, std::unique_ptr<Line>> _lines;
	Line _pulledLine;
};

template <typename T, typename... Args>
void Board::createNode(Args&&... args)
{
	unselectEverything();

	std::unique_ptr<Node> node = std::make_unique<T>(_areaView.getCenter(), std::forward<Args>(args)...);
	int id{ KeyGen::getKey() };

	while (_nodes.find(id) != _nodes.end())
		id = KeyGen::getKey();

	_nodes.emplace(id, std::move(node));
	_layers.push_back(id);

	if(!_selectedNodes.empty())
	{
		for (auto& i : _selectedNodes)
			_nodes.at(i)->select(false);

		_selectedNodes.clear();
	}

	_selectedNodes.push_back(id);
	_nodes.at(id)->select(true);
}