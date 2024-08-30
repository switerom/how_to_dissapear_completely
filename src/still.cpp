#include "still.h"

Still::Still(const sf::Vector2f& pos, const Screenshot& screenshot)
{
	_pos = pos;
	_tex = screenshot.tex;
	_spr.setTexture(_tex);
	_spr.setPosition(_pos);
	_spr.setTextureRect(screenshot.frame);

	float crop_factor = findCropFactor(sf::Vector2f(screenshot.frame.width, screenshot.frame.height), NODE_SIZE);
	_spr.setScale(crop_factor, crop_factor);
	_select_frame.setPosition(_pos);
	_select_frame.setSize(sf::Vector2f(_spr.getGlobalBounds().width, _spr.getGlobalBounds().height));
}

// Второй конструктор (используется при загрузке доски)
Still::Still(int id, const sf::Vector2f& pos, const sf::IntRect rect)
{
	_pos = pos;

	std::string tex_save_dir = getAbsolutePath(TEX_SAVE_DIR);

	sf::Texture tex;
	if (!tex.loadFromFile(tex_save_dir + "textureSave" + std::to_string(id) + ".jpg"))
		std::cout << "Image not loaded!\n";

	_tex = tex;
	_spr.setTexture(_tex);
	_spr.setPosition(_pos);
	_spr.setTextureRect(rect);

	float crop_factor = findCropFactor(sf::Vector2f(rect.width, rect.height), NODE_SIZE);
	_spr.setScale(crop_factor, crop_factor);
	_select_frame.setPosition(_pos);
	_select_frame.setSize(sf::Vector2f(_spr.getGlobalBounds().width, _spr.getGlobalBounds().height));
}

void Still::Draw(sf::RenderWindow& window) const
{
	window.draw(_select_frame);
	window.draw(_spr);
}

void Still::Update(float dt)
{

}

void Still::movePosition(const sf::Vector2f& vec)
{
	_pos += vec;
	_spr.setPosition(_pos);
	_select_frame.setPosition(_pos);
}

void Still::saveNode(int id, std::ofstream& save_file)
{
	std::string tex_save_dir = getAbsolutePath(TEX_SAVE_DIR);

	sf::Texture::bind(&_tex);
	sf::Image img = _tex.copyToImage();

	img.saveToFile(tex_save_dir + "textureSave" + std::to_string(id) + ".jpg");			// текстуру в .jpg

	int node_type = STILL;
	save_file.write(reinterpret_cast<char*>(&node_type), sizeof(node_type));

	save_file.write(reinterpret_cast<char*>(&id), sizeof(id));							// ID ноды в .bin

	sf::Vector2f pos = _spr.getPosition();
	save_file.write(reinterpret_cast<char*>(&pos), sizeof(pos));						// Vector2f объект в .bin

	sf::IntRect texRect = _spr.getTextureRect();
	save_file.write(reinterpret_cast<char*>(&texRect), sizeof(texRect));				// IntRect изображения в .bin
}
