#pragma once

#include "stdafx.h"
#include "area.h"
#include "screenshot.h"

class VideoPlayer: public Area
{
public:
	struct Interface
	{
		sf::RectangleShape _bar;
		sf::RectangleShape _seeker;
	};

	VideoPlayer();
	~VideoPlayer();
	void Init();
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Update(sf::RenderWindow& window, float dt) override;
	void toggleVideoPlayback(const std::string& filename);
	void toggleVideoPlayback();
	void changePlayTime(sf::RenderWindow& window);
	sf::FloatRect getBarBounds() const { return _interface._bar.getGlobalBounds(); };
	const sfe::Movie* getCurrentVideo() const { return _currentVideo; };
	Screenshot* getScreenshot() { return _screenshot; };

private:

	sfe::Movie* _currentVideo;

	Screenshot* _screenshot;
	Interface _interface;
};

