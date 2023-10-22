#include "videoplayer.h"
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

	_interface.bar.setFillColor(VIDEOPLAYER_BAR_COLOR);
	_interface.seeker.setFillColor(VIDEOPLAYER_SEEKER_COLOR);

	_interface.bar.setPosition(sf::Vector2f(0.f, HEIGHT - VIDEOPLAYER_BAR_HEIGHT));
	_interface.seeker.setPosition(sf::Vector2f(0.f, HEIGHT - VIDEOPLAYER_BAR_HEIGHT));

	_interface.bar.setSize(sf::Vector2f(WIDTH, VIDEOPLAYER_BAR_HEIGHT));
	_interface.seeker.setSize(sf::Vector2f(WIDTH, VIDEOPLAYER_BAR_HEIGHT));

	_screenshot.rect.setFillColor(sf::Color::Transparent);
	_screenshot.rect.setOutlineColor(SCREENSHOT_RECT_COLOR_A);
	_screenshot.rect.setOutlineThickness(SCREENSHOT_RECT_THICKNESS);

	_screenshot.video = nullptr;
	_screenshot.inProcess = false;
}

void VideoPlayer::loadVideo(const std::string& filename)
{
	// AssetManager нужно убрать для видео
	_currentVideo = new sfe::Movie;

	std::string filepath = VID_DIR + filename;

	if (!_currentVideo->openFromFile(filepath))
		_currentVideo = nullptr;
}

void VideoPlayer::toggleVideoPlayback(const std::string& filename)
{

	if (_currentVideo)
	{
		_currentVideo->stop();
		delete _currentVideo;
	}

	_vid_name = filename;
	loadVideo(filename);

	_subs.loadSubs(getSubName(filename));

	if (!_currentVideo)
	{
		_interface.seeker.setSize(sf::Vector2f(0.f, VIDEOPLAYER_BAR_HEIGHT));
		_screenshot.video = nullptr;
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

std::string VideoPlayer::getSubName(const std::string& filename) const
{
	size_t last_dot = filename.find_last_of(".");

	if (last_dot == std::string::npos)
		return "";
	else
		return filename.substr(0, last_dot) + ".srt";
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

	_subs.Draw(window);
}

void VideoPlayer::Update(sf::RenderWindow& window, float dt)
{
	if (!_currentVideo)
		return;

	if (_currentVideo->getStatus() != sfe::Status::Playing)
		return;

	_currentVideo->update();	// dt не передается параметром потому, что sfeMovie сам внутри это контролирует

	_subs.setText(_currentVideo->getPlayingOffset().asMilliseconds());

	float progressWidth = WIDTH * _currentVideo->getPlayingOffset().asSeconds() / _currentVideo->getDuration().asSeconds();
	_interface.seeker.setSize(sf::Vector2f(progressWidth, VIDEOPLAYER_BAR_HEIGHT));
}

void VideoPlayer::changePlayTime(sf::RenderWindow& window)
{
	if (!_currentVideo)
	{
		return;
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, _areaView);

	_interface.seeker.setSize(sf::Vector2f(mousePosView.x, VIDEOPLAYER_BAR_HEIGHT));				// возможно заменить на setPosition()

	auto playTime = mousePosView.x * _currentVideo->getDuration().asSeconds() / WIDTH;
	_currentVideo->setPlayingOffset(sf::seconds(playTime));

	_subs.changeCurrentSub(sf::milliseconds(playTime));
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

	if (_currentVideo)
	{
		_screenshot.tex = _currentVideo->getCurrentImage();
		_screenshot.video = _currentVideo;
	}

	_screenshot.vid_name = _vid_name;
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


