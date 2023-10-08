#include "videoplayer.h"
#include "settings.h"
#include "assetmanager.h"

VideoPlayer::VideoPlayer(): Area{ VIDEOPLAYER_MIN_BOUNDS }
{
	Init();
}

void VideoPlayer::Init()
{
	_currentVideo = nullptr;
}

void VideoPlayer::toggleVideoPlayback(const std::string& filename)
{
	//sfe::Movie* _prevvideo = _currentVideo;
	_currentVideo = AssetManager::getVideo(filename);

	if (!_currentVideo)
		return;

	if (_currentVideo->getStatus() == sfe::Status::Playing)
		_currentVideo->pause();
	else
		_currentVideo->play();
}

// Override для того, чтобы можно было просто мышью щелкать по видео для play/pause
void VideoPlayer::toggleVideoPlayback()
{
	if (!_currentVideo)
		return;

	if (_currentVideo->getStatus() == sfe::Status::Playing)
		_currentVideo->pause();
	else
		_currentVideo->play();
}


void VideoPlayer::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);

	if (_currentVideo)
		window.draw(*_currentVideo);
}

void VideoPlayer::Update(float dt)
{
	if (_currentVideo)
		_currentVideo->update();	// dt не передается параметром потому, что sfeMovie сам внутри это контролирует
}
