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

void Still::Draw(sf::RenderWindow& window) const
{
	window.draw(_select_frame);
	window.draw(_spr);
}

void Still::Update(float dt)
{

}
void Still::setPosition(const sf::Vector2f& pos)
{
	_pos = pos;
	_spr.setPosition(_pos);
	_select_frame.setPosition(_pos);
}

void Still::saveNode(int id)
{
	std::string save_file_path = getAbsolutePath(SAVE_FILE);
	std::string tex_save_dir = getAbsolutePath(TEX_SAVE_DIR);

	// Append file, not overwrite
	std::ofstream save_file(save_file_path, std::ios::binary | std::ios::app);

	sf::Texture::bind(&_tex);
	sf::Image img = _tex.copyToImage();

	img.saveToFile(tex_save_dir + "textureSave" + std::to_string(id) + ".jpg");			// текстуру в .jpg

	save_file.write(reinterpret_cast<char*>(&id), sizeof(id));							// ID ноды в .bin

	sf::Vector2f pos = _spr.getPosition();
	save_file.write(reinterpret_cast<char*>(&pos), sizeof(pos));						// Vector2f объект в .bin

	sf::IntRect texRect = _spr.getTextureRect();
	save_file.write(reinterpret_cast<char*>(&texRect), sizeof(texRect));				// IntRect изображения в .bin

	save_file.close();
}