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
		void changeSubPlayback(sf::Time playtime);
		std::vector<sf::FloatRect> getTextBounds() const;
		void startSelect(sf::RenderWindow& window, const sf::View& areaView);
		void setSelect(sf::RenderWindow& window, const sf::View& areaView);
		void endSelect();
		std::wstring getSelectedString();

	private:
		void createTextLine(const std::wstring& wstr);
		void clearText();
		void createLettersBounds();
		void changeSelectedLinesBounds();
		void swapSelection(const sf::Vector2i& select_first, const sf::Vector2i& select_second);

		SubtitleParserFactory* _subParserFactory;
		SubtitleParser* _parser;
		std::vector<SubtitleItem*> _sub;
		std::vector<SubtitleItem*>::iterator _currentSub;
		std::vector<sf::Text*> _text;
		std::vector<std::vector<sf::FloatRect>> _lettersBounds;

		// One Rectangle shape used to draw all select rects by changing it's position and size
		sf::RectangleShape _subsSelectRects;
		std::vector<sf::FloatRect> _subsSelectedLinesBounds;

		std::pair<sf::Vector2i, sf::Vector2i> _selectedTextRange;
		bool _subChanged;
		bool inSelectProcess;
};
