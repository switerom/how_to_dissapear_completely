#pragma once

#include "stdafx.h"
#include "area.h"
#include "timecontroller.h"
#include "carcass.h"

struct ViewCnotrol
{
	bool isMoving;
	sf::Vector2i prevMousePos;

	bool isZooming;
};

//struct VideoPreset
//{
//	const sfe::Movie* video;
//};

struct MoveControl
{
	bool isCarcassMoving;
	int selectedCarcass;
};

class Board: public Area
{
public:
	Board();
	~Board();
	void Init();
	virtual void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window, float dt);

	void moveView(sf::RenderWindow& window, float dt);
	void setViewMoving(sf::RenderWindow& window, bool isMoving);
	void zoomView(sf::RenderWindow& window, float dt_zoom, float dt);

	void createCarcass(const sfe::Movie* video);

	void moveCarcass(bool is_move, sf::RenderWindow& window);
	void selectCarcass(sf::RenderWindow& window);

private:
	sf::View _boardView;
	sf::RectangleShape _bigRect;
	ViewCnotrol _viewControl;
	//VideoPreset _videoPreset;

	std::map<int, Carcass*> _carcasses;
	std::list<int> _layers;
	//std::vector<Carcass*> _carcasses;

	MoveControl _movecontrol;
};