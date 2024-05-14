#pragma once

#include "stdafx.h"

// Uses Windows.h (specific to windows)
std::wstring convertToWideString(const std::string& str);

// Fit image in frame
void shiftImagePos(sf::Sprite& spr, const sf::FloatRect& frame_size);

float findCropFactor(const sf::Vector2f& img_size, const sf::Vector2f& frame_size);

std::string convertToTime(float number);

std::string getAbsolutePath(const std::string& path);
