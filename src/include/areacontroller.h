#pragma once

#include "stdafx.h"
#include "Area.h"
#include "videoplayer.h"
#include "explorer.h"
#include "timecontroller.h"
#include "board.h"

class AreaController
{
public:

	AreaController(Explorer& explorer, VideoPlayer& videoplayer, Board& board);

	void Draw(sf::RenderWindow& window);
	void Update(float dt);
	void setAreaID(Area::ID area);

	void EventControl(sf::Event& event, sf::RenderWindow& window, TimeController& timecontroller);
	void explorerEvents(sf::Event& event, sf::RenderWindow& window, TimeController& timecontroller);
	void videoplayerEvents(sf::Event& event, sf::RenderWindow& window, TimeController& timecontroller);

private:
	std::vector<Area*> _areas;
	Area::ID _maximized;
	Explorer& _explorer;
	Board& _board;
	VideoPlayer& _videoplayer;
};