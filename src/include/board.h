#pragma once

#include "stdafx.h"
#include "area.h"
#include "node.h"
#include "still.h"
#include "timecontroller.h"
#include "collisiondetection.h"
#include "videoplayer.h"

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

	void createStill(const Screenshot& screenshot);
	//void createNode(//для текста);
	//void createNode(//для заметок);

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