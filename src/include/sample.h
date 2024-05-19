#pragma once

#include "stdafx.h"
#include "settings.h"
#include "fragment.h"
#include "assetmanager.h"

class Sample : public Fragment
{
public:
	Sample(const sf::Vector2f& pos, const Audio& audio);
	~Sample() {};

	void Draw(sf::RenderWindow& window) const override;
	void Update(float dt) override;
	void movePosition(const sf::Vector2f& vec) override;
	void saveNode(int id, std::ofstream& save_file) override;

private:
	sf::Texture _tex;
	sf::Sprite _spr;
	sf::Text _text;
};