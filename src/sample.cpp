#include "sample.h"


Sample::Sample(const sf::Vector2f& pos, const Audio& audio)
{
	_pos = pos;
	_text.setString(audio.wstr);
	_text.setCharacterSize(SUBS_SIZE);
	_text.setFillColor(SUBS_COLOR);
	_text.setFont(AssetManager::getFont(SUBS_FONT));
	_text.setPosition(_pos);

	_select_frame.setPosition(_pos);
	_select_frame.setSize(sf::Vector2f(_text.getGlobalBounds().width, _text.getGlobalBounds().height*2.f));
}

void Sample::Draw(sf::RenderWindow& window) const
{
	window.draw(_select_frame);
	window.draw(_text);
}

void Sample::Update(float dt)
{

}

void Sample::setPosition(const sf::Vector2f& pos)
{
	_pos = pos;
	_text.setPosition(_pos);
	_select_frame.setPosition(_pos);
}

void Sample::saveNode(int id, std::ofstream& save_file)
{
	std::string save_file_path = getAbsolutePath(SAVE_FILE);

	int node_type = SAMPLE;
	save_file.write(reinterpret_cast<char*>(&node_type), sizeof(node_type));

	save_file.write(reinterpret_cast<char*>(&id), sizeof(id));							// ID ноды в .bin

	sf::Vector2f pos = _text.getPosition();
	save_file.write(reinterpret_cast<char*>(&pos), sizeof(pos));						// Vector2f объект в .bin

	std::wstring wstr = _text.getString();												// написанный текст
	size_t wstr_size = wstr.size();
	save_file.write(reinterpret_cast<char*>(&wstr_size), sizeof(wstr_size));
	save_file.write(reinterpret_cast<char*>(wstr.data()), wstr_size * sizeof(wchar_t));	
}