#pragma once

#include "stdafx.h"
#include "settings.h"
#include "fragment.h"

class Still: public Fragment
{
public:
	Still(const Screenshot& screenshot);
	~Still() {};

	void Draw(sf::RenderWindow& window) const override;
	void Update(float dt) override;

private:
	sf::Texture _tex;
	sf::Sprite _spr;
};
