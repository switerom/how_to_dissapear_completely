#pragma once

#include "stdafx.h"
#include "area.h"
#include "subtitles.h"

struct Screenshot
{
	//MetaData _metaData;
	const sfe::Movie* video;
	bool inProcess;
	sf::Texture tex;
	//sf::Sprite spr;			// исправить это
	sf::IntRect frame;
	sf::RectangleShape rect;
	std::string vid_name{};
};

class VideoPlayer: public Area
{
public:
	struct Interface
	{
		sf::RectangleShape bar;
		sf::RectangleShape seeker;

		sf::Text captions;
		std::string subText;
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
	const std::string& getVideoName() const { return _vid_name; }

	void startScreenshot(sf::RenderWindow& window);
	void endScreenshot();
	void setScreenshotRect(sf::RenderWindow& window);
	const Screenshot& getScreenshot() const { return _screenshot; };

private:
	std::string getSubName(const std::string& filename) const;
	void loadVideo(const std::string& filename);
	void fitVideo();

	sf::View _videoView;
	sfe::Movie* _currentVideo;
	std::string _vid_name;
	Screenshot _screenshot;
	Interface _interface;
	Subtitles _subs;
};

