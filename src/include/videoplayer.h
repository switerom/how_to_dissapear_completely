#pragma once

#include "stdafx.h"
#include "area.h"

class VideoPlayer: public Area
{
public:
	struct Interface
	{
		sf::RectangleShape bar;
		sf::RectangleShape seeker;
	};

	struct Screenshot
	{
		//MetaData _metaData;
		bool inProcess;
		sf::Texture tex;
		sf::Sprite spr;			// исправить это
		sf::IntRect frame;
		sf::RectangleShape rect;
	};

	VideoPlayer();
	~VideoPlayer();
	void Init();
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Update(sf::RenderWindow& window, float dt) override;
	void toggleVideoPlayback(const std::string& filename);
	void toggleVideoPlayback();
	void changePlayTime(sf::RenderWindow& window);
	sf::FloatRect getBarBounds() const { return _interface.bar.getGlobalBounds(); };
	const sfe::Movie* getCurrentVideo() const { return _currentVideo; };

	void startScreenshot(sf::RenderWindow& window);
	void endScreenshot();
	void setScreenshotRect(sf::RenderWindow& window);
	sf::Sprite getScreenshot() { return _screenshot.spr; };


private:

	sfe::Movie* _currentVideo;

	Screenshot _screenshot;
	Interface _interface;
};

