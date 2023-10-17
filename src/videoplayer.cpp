﻿#include "videoplayer.h"
#include "settings.h"
#include "assetmanager.h"

VideoPlayer::VideoPlayer(): Area( VIDEOPLAYER_MIN_BOUNDS, VIDEOPLAYER_VIEWPORT)
{
	Init();
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::Init()
{
	_currentVideo = nullptr;
	_id = ID::Videoplayer;

	_interface.bar.setFillColor(VIDEOPLAYERbar_COLOR);
	_interface.seeker.setFillColor(VIDEOPLAYERseeker_COLOR);

	_interface.bar.setPosition(sf::Vector2f(0.f, HEIGHT - VIDEOPLAYERbar_HEIGHT));
	_interface.seeker.setPosition(sf::Vector2f(0.f, HEIGHT - VIDEOPLAYERbar_HEIGHT));

	_interface.bar.setSize(sf::Vector2f(WIDTH, VIDEOPLAYERbar_HEIGHT));
	_interface.seeker.setSize(sf::Vector2f(WIDTH, VIDEOPLAYERbar_HEIGHT));

	_screenshot.rect.setFillColor(sf::Color::Transparent);
	_screenshot.rect.setOutlineColor(SCREENSHOT_RECT_COLOR_A);
	_screenshot.rect.setOutlineThickness(SCREENSHOT_RECT_THICKNESS);
}

void VideoPlayer::toggleVideoPlayback(const std::string& filename)
{
	_currentVideo = AssetManager::getVideo(filename);

	if (!_currentVideo)
	{
		_interface.seeker.setSize(sf::Vector2f(0.f, VIDEOPLAYERbar_HEIGHT));
		return;
	}

	if (_currentVideo->getStatus() == sfe::Status::Playing)
		_currentVideo->pause();
	else
	{
		//toggleMaximize();
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

	window.draw(_interface.bar);
	window.draw(_interface.seeker);

	if(_screenshot.inProcess)
		window.draw(_screenshot.rect);
}

void VideoPlayer::Update(sf::RenderWindow& window, float dt)
{
	if (!_currentVideo)
		return;

	if (_currentVideo->getStatus() != sfe::Status::Playing)
		return;

	_currentVideo->update();	// dt не передается параметром потому, что sfeMovie сам внутри это контролирует

	float progressWidth = WIDTH * _currentVideo->getPlayingOffset().asSeconds() / _currentVideo->getDuration().asSeconds();
	_interface.seeker.setSize(sf::Vector2f(progressWidth, VIDEOPLAYERbar_HEIGHT));
}

void VideoPlayer::changePlayTime(sf::RenderWindow& window)
{
	if (!_currentVideo)
	{
		return;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, _areaView);

	_interface.seeker.setSize(sf::Vector2f(mousePosView.x, VIDEOPLAYERbar_HEIGHT));				// возможно заменить на setPosition()

	auto playTime = mousePosView.x * _currentVideo->getDuration().asSeconds() / WIDTH;
	_currentVideo->setPlayingOffset(sf::seconds(playTime));
}

void VideoPlayer::startScreenshot(sf::RenderWindow& window)
{ 
	_screenshot.inProcess = true; 

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, _areaView);

	_screenshot.frame.left = mousePosView.x;
	_screenshot.frame.top = mousePosView.y;
	_screenshot.frame.width = 0;
	_screenshot.frame.height = 0;

	_screenshot.rect.setPosition(mousePosView.x, mousePosView.y);
	_screenshot.rect.setSize(sf::Vector2f(_screenshot.frame.width, _screenshot.frame.height));
};

void VideoPlayer::endScreenshot()
{
	_screenshot.inProcess = false;

	_screenshot.tex = _currentVideo->getCurrentImage();

	_screenshot.spr.setTexture(_screenshot.tex);
	_screenshot.spr.setTextureRect(_screenshot.frame);
}

void VideoPlayer::setScreenshotRect(sf::RenderWindow& window)
{
	if (!_screenshot.inProcess)
		return;

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, _areaView);

	_screenshot.frame.width = mousePosView.x - _screenshot.frame.left;
	_screenshot.frame.height = mousePosView.y - _screenshot.frame.top;

	_screenshot.rect.setSize(sf::Vector2f(_screenshot.frame.width, _screenshot.frame.height));
}


