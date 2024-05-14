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

	_interface.timing.setFont(AssetManager::getFont(TIME_FONT));
	_interface.timing.setCharacterSize(TIME_SIZE);
	_interface.timing.setFillColor(TIME_COLOR);
	_interface.timing.setString("00:00 / 00:00");
	sf::FloatRect textBounds = _interface.timing.getLocalBounds();
	_interface.timing.setOrigin(textBounds.left + textBounds.width, textBounds.top + textBounds.height);
	_interface.timing.setPosition(TIME_POS);

	_screenshot.rect.setFillColor(sf::Color::Transparent);
	_screenshot.rect.setOutlineColor(SCREENSHOT_RECT_COLOR_A);
	_screenshot.rect.setOutlineThickness(SCREENSHOT_RECT_THICKNESS);

	_screenshot.video = nullptr;
	_screenshot.inProcess = false;
	_interface.nextTimeSec = 0;
}

void VideoPlayer::loadVideo(const std::string& filename)
{
	// AssetManager нужно убрать для видео
	_currentVideo = new sfe::Movie;

	std::string filepath = VID_DIR + filename;
	_interface.nextTimeSec = 0;

	if (!_currentVideo->openFromFile(filepath))
	{
		_currentVideo = nullptr;
		return;
	}

	fitVideo();
}

// Set viewport for the video to be placed in videoplayer area bounds
void VideoPlayer::fitVideo()
{
	sf::Vector2f old_size(_currentVideo->getSize().x, _currentVideo->getSize().y);

	float crop_factor = findCropFactor(sf::Vector2f(old_size.x, old_size.y), sf::Vector2f(WIDTH, HEIGHT));

	// (Fix)(Thickness shouldn't change)(Rect should be drawn in area view, not video view)
	_screenshot.rect_thk = SCREENSHOT_RECT_THICKNESS / crop_factor;
	_screenshot.rect.setOutlineThickness(_screenshot.rect_thk);

	sf::Vector2f shift;
	sf::FloatRect rect;

	// Calculate indentation (black bars)
	shift.x = (WIDTH - old_size.x * crop_factor) * 0.5f;
	shift.y = (HEIGHT - old_size.y * crop_factor) * 0.5f;

	// Calculate rectangle factors
	rect.left = shift.x / WIDTH * 0.5f;
	rect.top = shift.y / HEIGHT * 0.5f;
	rect.width = old_size.x * crop_factor / WIDTH * 0.5f;
	rect.height = old_size.y * crop_factor / HEIGHT * 0.5f;

	// Set viewport for the video
	_videoView.reset(sf::FloatRect(0.f, 0.f, old_size.x, old_size.y));
	_videoView.setViewport(sf::FloatRect(rect.left, rect.top, rect.width, rect.height));
}

void VideoPlayer::toggleVideoPlayback(const std::string& filename, const sf::Time& playTime)
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
		_currentVideo->setPlayingOffset(playTime);
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

std::vector<sf::FloatRect> VideoPlayer::getSubsBounds() const
{
	return _subs.getTextBounds();
}

void VideoPlayer::Draw(sf::RenderWindow& window)
{
	window.setView(_videoView);
	//window.setView(_areaView);

	if (_currentVideo)
		window.draw(*_currentVideo);

	if (_screenshot.inProcess)
		window.draw(_screenshot.rect);

	window.setView(_areaView);

	window.draw(_interface.bar);
	window.draw(_interface.seeker);

	window.draw(_interface.timing);

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

changeTiming();

float progressWidth = WIDTH * _currentVideo->getPlayingOffset().asSeconds() / _currentVideo->getDuration().asSeconds();
_interface.seeker.setSize(sf::Vector2f(progressWidth, VIDEOPLAYER_BAR_HEIGHT));
}

void VideoPlayer::changeTiming()
{
	float playTimeNum = _currentVideo->getPlayingOffset().asSeconds();

	if (static_cast<int>(playTimeNum) < _interface.nextTimeSec)
		return;

	_interface.nextTimeSec = static_cast<int>(playTimeNum) + 1;

	float durationNum = _currentVideo->getDuration().asSeconds();

	std::string durationStr{ convertToTime(durationNum) };
	std::string playTimeStr{ convertToTime(playTimeNum) };

	_interface.timing.setString(playTimeStr + " / " + durationStr);
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

	auto duration = _currentVideo->getDuration().asSeconds();
	auto playTime = mousePosView.x * duration / WIDTH;
	_currentVideo->setPlayingOffset(sf::seconds(playTime));
	_interface.nextTimeSec = static_cast<int>(playTime) + 1;

	_interface.nextTimeSec = static_cast<int>(_currentVideo->getPlayingOffset().asSeconds());
	changeTiming();

	_subs.changeSubPlayback(sf::seconds(playTime));
}

void VideoPlayer::startScreenshot(sf::RenderWindow& window)
{
	if (!_currentVideo)
		return;

	_screenshot.inProcess = true;

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, _videoView);

	_screenshot.frame.left = mousePosView.x;
	_screenshot.frame.top = mousePosView.y;
	_screenshot.frame.width = 0;
	_screenshot.frame.height = 0;

	//	Restrict screenshot frame from black bars (on start)
	if (_screenshot.frame.left < 0)
	{
		_screenshot.frame.left = 0;
	}
	else if (_screenshot.frame.top < 0)
	{
		_screenshot.frame.top = 0;
	}
	else if (_screenshot.frame.left > _currentVideo->getSize().x)
	{
		_screenshot.frame.left = _currentVideo->getSize().x;
	}
	else if (_screenshot.frame.top > _currentVideo->getSize().y)
	{
		_screenshot.frame.top = _currentVideo->getSize().y;
	}

	// Set drawable rectangle
	_screenshot.rect.setPosition(_screenshot.frame.left, _screenshot.frame.top);
	_screenshot.rect.setSize(sf::Vector2f(0.f, 0.f));
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

	// Swap values if scrennshot reversed
	auto& rect = _screenshot.frame;

	if (rect.width < 0)
	{
		rect.left += rect.width;
		rect.width = -rect.width;
	}
	if (rect.height < 0)
	{
		rect.top += rect.height;
		rect.height = -rect.height;
	}
}

void VideoPlayer::setScreenshotRect(sf::RenderWindow& window)
{
	if (!_screenshot.inProcess)
		return;

	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosView = window.mapPixelToCoords(mousePos, _videoView);

	// Set frame for texture
	_screenshot.frame.width = mousePosView.x - _screenshot.frame.left;
	_screenshot.frame.height = mousePosView.y - _screenshot.frame.top;

	sf::Vector2i newSize = sf::Vector2i(_screenshot.frame.width, _screenshot.frame.height);
	
	//	Restrict screenshot frame from black bars (in process)
	if (mousePosView.x > _currentVideo->getSize().x)
	{
		_screenshot.frame.width = _currentVideo->getSize().x - _screenshot.frame.left;
		newSize.x = _screenshot.frame.width - _screenshot.rect_thk;
	}
	else if (mousePosView.y > _currentVideo->getSize().y)
	{
		_screenshot.frame.height = _currentVideo->getSize().y - _screenshot.frame.top;
		newSize.y = _screenshot.frame.height - _screenshot.rect_thk;
	}
	else if (mousePosView.x < 0.f)
	{
		_screenshot.frame.width = -_screenshot.frame.left;
		newSize.x = _screenshot.frame.width + _screenshot.rect_thk;
	}
	else if (mousePosView.y < 0.f)
	{
		_screenshot.frame.height = -_screenshot.frame.top;
		newSize.y = _screenshot.frame.height + _screenshot.rect_thk;
	}

	// Set drawable rectangle
	_screenshot.rect.setSize(sf::Vector2f(newSize.x, newSize.y));
}

void VideoPlayer::startSelectSubs(sf::RenderWindow& window)
{
	_subs.startSelect(window, _areaView);
}

void VideoPlayer::setSelectSubs(sf::RenderWindow& window)
{
	_subs.setSelect(window, _areaView);
}

void VideoPlayer::endSelectSubs()
{
	_subs.endSelect();
	_audio.wstr = _subs.getSelectedString();
}

void VideoPlayer::resetAction()
{
	_screenshot.inProcess = false;
}
