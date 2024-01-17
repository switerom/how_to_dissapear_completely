#include "utility.h"

// Uses Windows.h (specific to windows)
std::wstring convertToWideString(const std::string& str)
{
    std::wstring wstr{};

    int len = str.length();
    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, NULL, 0);
    wstr.resize(unicodeLen);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), len, &wstr[0], unicodeLen);

    return wstr;
}

// Fit image in frame
void fitImage(sf::Sprite& spr, const sf::FloatRect& frame_size)
{
	sf::Vector2f img_size{ sf::Vector2f(spr.getTextureRect().width, spr.getTextureRect().height) };

	float crop_factor = findCropFactor(img_size, sf::Vector2f(frame_size.width, frame_size.height)) ;

	sf::Vector2f shift;

	// Calculate indentation (black bars)
	shift.x = (frame_size.width - img_size.x * crop_factor) * 0.5f;
	shift.y = (frame_size.height - img_size.y * crop_factor) * 0.5f;

	spr.setPosition(frame_size.left + shift.x, frame_size.top + shift.y);
	spr.setScale(crop_factor, crop_factor);
}

float findCropFactor(const sf::Vector2f& img_size, const sf::Vector2f& frame_size)
{
	// Find crop factor to scale video
	float crop_factor1 = frame_size.x / img_size.x;
	float crop_factor2 = frame_size.y / img_size.y;

	return std::min(crop_factor1, crop_factor2);
}