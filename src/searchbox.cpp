#include "searchbox.h"

void SearchBox::startSearch() const
{

}

SearchBox::SearchBox()
{
	_textBox.setCharacterSize(SEARCHBOX_CHAR_SIZE);
	_textBox.setFillColor(SEARCHBOX_CHAR_COLOR);
	_textBox.setFont(AssetManager::getFont(SEARCHBOX_CHAR_FONT));
	_textBox.setPosition(SEARCHBOX_CHAR_POS);
	_isSelected = true;		// сделать "= false"
	_limit = SEARCHBOX_CHAR_LIMIT;

	// Верхняя рамка
	_searchRect.setFillColor(SEARCH_RECT_COLOR);
	_searchRect.setSize(sf::Vector2f(WIDTH, SEARCH_RECT_HEIGHT));
	_searchRect.setPosition(SEARCHBOX_RECT_POS);
};

void SearchBox::setSelected(bool isSelected)
{
	_isSelected = isSelected;

	if (!_isSelected)
	{
		std::wstring t = _text.str();
		std::wstring newT = L"";

		for (int i = 0; i < t.length() - 1; ++i)
		{
			newT += t[i];
		}

		_textBox.setString(newT);
	}
}

void SearchBox::typedOn(sf::Event& input)
{
	if (_isSelected)
	{
		int charTyped = input.text.unicode;

		//if (charTyped < 128)
		//{
		if (_text.str().length() <= _limit)
		{
			inputLogic(charTyped);
		}
		else if (_text.str().length() > _limit && charTyped == DELETE_KEY)
		{
			deleteLastChar();
		}
		//}
	}
}

void SearchBox::Draw(sf::RenderWindow& window) const
{
	window.draw(_searchRect);
	window.draw(_textBox);
}

void SearchBox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
	{
		_text << static_cast<wchar_t>(charTyped);
	}
	else if (charTyped == DELETE_KEY)
	{
		deleteLastChar();
	}

	_textBox.setString(_text.str() + L"_");
}

void SearchBox::deleteLastChar()
{
	std::wstring t = _text.str();

	if (t == L"")
		return;

	std::wstring newT = L"";

	for (int i = 0; i < t.length() - 1; ++i)
	{
		newT += t[i];
	}
	_text.str(L"");
	_text << newT;

	_textBox.setString(_text.str());
}

std::wstring SearchBox::getText() const
{ 
	std::wstring wstr = _textBox.getString();

	return wstr.substr(0, wstr.size() - 1);
};		