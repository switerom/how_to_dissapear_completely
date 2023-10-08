#pragma once

#include "stdafx.h"
#include "area.h"

class VideoPlayer: public Area
{
public:
	VideoPlayer();
	void Init();
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Update(float dt) override;
	void toggleVideoPlayback(const std::string& filename);
	void toggleVideoPlayback();

private:
	sf::View _playerView;

	sfe::Movie* _currentVideo;
};

