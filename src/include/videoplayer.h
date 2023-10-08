#pragma once

#include "stdafx.h"

class VideoPlayer
{
public:
	VideoPlayer();
	void Init();
	//void Draw(sf::RenderWindow& window);
	//void Update(float dt, sf::RenderWindow& window);
	//void play(const std::string& filename);
	//void pause();
	//void stop();

private:
	sf::View _playerView;

	sfe::Movie* _currentVideo;
};

