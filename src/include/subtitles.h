#pragma once

#include "stdafx.h"
#include "srtparser.h"

class Subtitles
{
	public:
		Subtitles();
		void loadSubs(const std::string& sub_name);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);

	private:
		void setText(float playtime);

		SubtitleParserFactory* _subParserFactory;
		SubtitleParser* _parser;
		std::vector<SubtitleItem*> _sub;

		sf::Text _text;
};
