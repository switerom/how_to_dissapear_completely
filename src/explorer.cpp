#include "explorer.h"
#include "stdafx.h"
#include "settings.h"
#include "exploreritem.h"

namespace fs = std::filesystem;

void Explorer::Init()
{
	// Фон окна
	_bigRect.setFillColor(sf::Color::Red);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

	// Верхняя рамка
	_topRect.setFillColor(sf::Color::Blue);
	_topRect.setSize(sf::Vector2f(WIDTH, EXPLORER_TOP_RECT));

	// Размер окна
	_exView.reset(sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT));	// так мы указываем, что вся область explorera будет отображаться
	_exView.setViewport(sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));	// так мы указываем, что отображаться должно в левой нижней четверти основного окна

	_isMaximized = false;

	loadFiles();
}

void Explorer::loadFiles()
{
	fs::path folderPath = VID_DIR;

	unsigned int id{};

	try {
		// Check if the folder exists
		if (fs::exists(folderPath) && fs::is_directory(folderPath)) {

			// Iterate through the directory and create items
			for (const auto& entry : fs::directory_iterator(folderPath)) {

				auto filename = entry.path().filename();

				_explorerItems.emplace_back( ExplorerItem(filename.string(), id));

				++id;
			}
		}
		else {
			std::cout << "Folder does not exist or is not a directory." << std::endl;
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Filesystem error: " << ex.what() << std::endl;
	}
}

Explorer::Explorer()
{
	Init();
}

void Explorer::Draw(sf::RenderWindow& window)
{
	window.setView(_exView);	// применяем View, иначе будет на весь экран
	window.draw(_bigRect);
	window.draw(_topRect);


	for (auto& i : _explorerItems)
	{
		window.draw(i.getText());
	}
}

void Explorer::Update(float dt)
{
}

void Explorer::toggleMaximize()
{
	if (_isMaximized)
	{
		_exView.setViewport(sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f));
		_isMaximized = false;
	}
	else
	{
		_exView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
		_isMaximized = true;
	}
}

sf::FloatRect Explorer::getTopBoxRect() const
{
	return _topRect.getGlobalBounds();
}

const sf::View& Explorer::getExplorerView() const
{
	return _exView;
}
