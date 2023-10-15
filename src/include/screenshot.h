#pragma once
#include "stdafx.h"

class Screenshot
{
public:
	//struct MetaData		// когда делается скриншот, сохраняются данные из файла(созданного через After Effects)
	//{
	//	std::string _vidName;
	//	int _vidFrame;
	//	sf::IntRect _rect;
	//};

	struct Lines
	{
		sf::RectangleShape lineX1;
		sf::RectangleShape lineY1;

		sf::RectangleShape lineX2;
		sf::RectangleShape lineY2;
	};

	Screenshot();
	void Init();
	void Draw(sf::RenderWindow& window);
	void Update(float dt);
	void moveLines(sf::RenderWindow& window, const sf::View& areaView);
	void takeScreenshot(sf::RenderWindow& window, const sfe::Movie* vid, const sf::View& areaView);
	void resetScreenshot();
	const sf::Texture& getTexture() const { return _screenshot; };
	const sf::IntRect& getRect() const { return _frame; };

private:
	//MetaData _metaData;
	bool _inProcess;
	sf::IntRect _frame;
	sf::Texture _screenshot;
	sf::Sprite _spr;			// исправить это
	Lines _lines;
};

