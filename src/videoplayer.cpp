#include "videoplayer.h"
#include "settings.h"
#include "assetmanager.h"

VideoPlayer::VideoPlayer()
{
	Init();
}

void VideoPlayer::Init()
{
	//_playerView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));
	//_playerView.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 0.5f));
	//_currentVideo = AssetManager::getVideo(filename);

	//_subSelection.setFillColor(SUB_SELECT_COLOR);

	//_interface._bar.setFillColor(sf::Color::White);
	//_interface._progress.setFillColor(sf::Color::Blue);

	//_interface._bar.setPosition(sf::Vector2f(0.f, HEIGHT - BAR_HEIGHT));
	//_interface._progress.setPosition(sf::Vector2f(0.f, HEIGHT - BAR_HEIGHT));

	//_interface._bar.setSize(sf::Vector2f(WIDTH, BAR_HEIGHT));
	//_interface._progress.setSize(sf::Vector2f(WIDTH, BAR_HEIGHT));

	////_startEndSubSelect.first = _subText.begin();
	////_startEndSubSelect.second = _subText.end();

	//_startEndSubSelect.first = 0.f;
	//_startEndSubSelect.second = 0.f;

	//// Для реализации выделения текста, у нас всегда будет 3 sf::Text объекта в векторе
	//for (int i{ 0 }; i < 3; ++i)
	//{
	//	_captions.setFont(AssetManager::getFont(FONT));
	//	_captions.setCharacterSize(SUB_SIZE);
	//	_captions.setFillColor(SUB_COLOR);
	//	_captions.setString("");
	//	sf::FloatRect textBounds = _captions.getLocalBounds();
	//	_captions.setOrigin(textBounds.left + textBounds.width * 0.5f, textBounds.top + textBounds.height * 0.5f);
	//	_captions.setPosition(SUB_POSITION);
	//}
}