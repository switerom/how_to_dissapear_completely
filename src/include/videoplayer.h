#pragma once

#include "stdafx.h"
#include "area.h"

struct VideoPlayerInterface
{
	sf::RectangleShape _bar;
	sf::RectangleShape _seeker;
};


class VideoPlayer: public Area
{
public:
	VideoPlayer();
	void Init();
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Update(sf::RenderWindow& window, float dt) override;
	void toggleVideoPlayback(const std::string& filename);
	void toggleVideoPlayback();
	void changePlayTime(sf::RenderWindow& window);
	sf::FloatRect getBarBounds() const { return _interface._bar.getGlobalBounds(); };

private:

	sfe::Movie* _currentVideo;

	VideoPlayerInterface _interface;
};

