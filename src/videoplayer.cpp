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

	_interface._bar.setFillColor(VIDEOPLAYER_BAR_COLOR);
	_interface._seeker.setFillColor(VIDEOPLAYER_SEEKER_COLOR);

	_interface._bar.setPosition(sf::Vector2f(0.f, HEIGHT - VIDEOPLAYER_BAR_HEIGHT));
	_interface._seeker.setPosition(sf::Vector2f(0.f, HEIGHT - VIDEOPLAYER_BAR_HEIGHT));

	_interface._bar.setSize(sf::Vector2f(WIDTH, VIDEOPLAYER_BAR_HEIGHT));
	_interface._seeker.setSize(sf::Vector2f(WIDTH, VIDEOPLAYER_BAR_HEIGHT));
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
	{
		toggleMaximize();
		_currentVideo->play();
	}
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

	window.draw(_interface._bar);
	window.draw(_interface._seeker);
}

void VideoPlayer::Update(float dt)
{
	if (!_currentVideo)
		return;

	if (_currentVideo->getStatus() != sfe::Status::Playing)
		return;

	_currentVideo->update();	// dt не передается параметром потому, что sfeMovie сам внутри это контролирует

	float progressWidth = WIDTH * _currentVideo->getPlayingOffset().asSeconds() / _currentVideo->getDuration().asSeconds();
	_interface._seeker.setSize(sf::Vector2f(progressWidth, VIDEOPLAYER_BAR_HEIGHT));
}

void VideoPlayer::changePlayTime(sf::RenderWindow& window)
{
	if (!_currentVideo)
		return;

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, _areaView);

	_interface._seeker.setSize(sf::Vector2f(mousePosView.x, VIDEOPLAYER_BAR_HEIGHT));				// возможно заменить на setPosition()

	auto playTime = mousePosView.x * _currentVideo->getDuration().asSeconds() / WIDTH;
	_currentVideo->setPlayingOffset(sf::seconds(playTime));

}
