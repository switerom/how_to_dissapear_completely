#pragma once

#include "stdafx.h"
#include "settings.h"
#include "fragment.h"

class Still: public Fragment
{
public:
	Still(const sf::Vector2f& pos, const Screenshot& screenshot);
	Still(int id, const sf::Vector2f& pos, const sf::IntRect rect);

	~Still() {};

	void Draw(sf::RenderWindow& window) const override;
	void Update(float dt) override;
	void setPosition(const sf::Vector2f& pos) override;
	void saveNode(int id, std::ofstream& save_file) override;

private:
	sf::Texture _tex;
	sf::Sprite _spr;
};
