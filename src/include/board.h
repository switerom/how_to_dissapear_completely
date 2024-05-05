﻿#pragma once

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
	//void setNodeMoving(bool isMoving);

	void moveNode(bool is_move, sf::RenderWindow& window);
	void deleteNode();

private:
	sf::View _boardView;
	sf::RectangleShape _bigRect;
	ViewCnotrol _viewControl;

	std::map<int, std::unique_ptr<Node>> _nodes;
	std::list<int> _layers;
	//std::map<Edge, Line*> _lines;
	int _selectedNodeID;
};