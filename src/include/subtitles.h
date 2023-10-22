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
		void setText(long playtime);
		void changeCurrentSub(sf::Time playtime);

	private:
		std::wstring convertToWideString(const std::string& str) const;

		SubtitleParserFactory* _subParserFactory;
		SubtitleParser* _parser;
		std::vector<SubtitleItem*> _sub;
		std::vector<SubtitleItem*>::iterator _currentSub;

		sf::Text _text;
};
