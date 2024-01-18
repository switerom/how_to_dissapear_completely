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
void shiftImagePos(sf::Sprite& spr, const sf::FloatRect& frame_size)
{
	sf::Vector2f img_size{ sf::Vector2f(spr.getGlobalBounds().width, spr.getGlobalBounds().height) };

	sf::Vector2f shift;

	// Calculate indentation (black bars)
	shift.x = (frame_size.width - img_size.x) * 0.5f;
	shift.y = (frame_size.height - img_size.y) * 0.5f;

	spr.setPosition(frame_size.left + shift.x, frame_size.top + shift.y);
}

float findCropFactor(const sf::Vector2f& img_size, const sf::Vector2f& frame_size)
{
	// Find crop factor to scale video
	float crop_factor1 = frame_size.x / img_size.x;
	float crop_factor2 = frame_size.y / img_size.y;

	return std::min(crop_factor1, crop_factor2);
}

std::string convertToTime(float number)
{
	// Convert the number to minutes and seconds
	int minutes = static_cast<int>(number) / 60;
	int seconds = static_cast<int>(number) % 60;

	// Create a stringstream to format the output
	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << minutes << ":"
		<< std::setw(2) << std::setfill('0') << seconds;

	// Return the formatted string
	return ss.str();
}