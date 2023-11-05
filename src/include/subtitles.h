#pragma once

#include "stdafx.h"
#include "srtparser.h"

class Subtitles
{
	public:
		Subtitles();
		~Subtitles();
		void loadSubs(const std::string& sub_name);

		void Update(float dt);
		void Draw(sf::RenderWindow& window);
		void setText(long playtime);
		void changeCurrentSub(sf::Time playtime);
		std::vector<sf::FloatRect> getTextBounds() const;
		sf::Vector2i getSelectStart(sf::RenderWindow& window, const sf::View& areaView);

	private:
		std::wstring convertToWideString(const std::string& str) const;
		void createTextLine(const std::wstring& wstr);
		void clearText();
		void createLettersBounds();

		SubtitleParserFactory* _subParserFactory;
		SubtitleParser* _parser;
		std::vector<SubtitleItem*> _sub;
		std::vector<SubtitleItem*>::iterator _currentSub;
		std::vector<sf::Text*> _text;
		//std::vector<sf::FloatRect> _lettersBounds;	
		std::vector<std::vector<sf::FloatRect>> _lettersBounds;
		bool _subChanged;
};
