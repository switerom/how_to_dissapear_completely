﻿#pragma once

#define GAME_NAME "How to dissapear completely"

#define WIDTH				1920
#define HEIGHT				1080
#define TOTAL_VIDS			6

#define PREVIEW_FORMAT		".jpg"
#define PREVIEW_DIR			"rsc/img/prev/"

#define EXITEM_X_POS		WIDTH*0.1f
#define EXITEM_Y_POS		WIDTH*0.1f
#define EXITEM_Y_DIST		WIDTH*0.05f

#define MIN_VIEW_SIZE 		700.f
#define MAX_VIEW_SIZE		4000.f

#define NOT_SELECTED		0

#define LINE_THICKNESS		7.f
#define EPSILON				0.0001f

#define FONT				"rsc/fonts/CascadiaCode.ttf"
#define SUB_SIZE			35
#define SUB_COLOR			sf::Color::White
#define SUB_POSITION		sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.9f)

#define SUB_SELECT_COLOR	sf::Color::Blue
#define SUB_SELECT_SIZE_Y	SUB_SIZE
#define SUB_SELECT_POS_Y	HEIGHT * 0.875f	

#define TEXT_NOTE_SIZE		75
#define DOUBLE_CLICK_RANGE	5

#define SAVES_DIR			"C:/_FILES/CATEGORIES/MY_FILM-GAME/code/detective_film_game/game/saves"

// Настройки всех окон
#define WINDOW_TOP_RECT				HEIGHT*0.025f
#define WINDOW_FRAME_COLOR			sf::Color::Blue
#define WINDOW_MAX_BOUNDS			sf::FloatRect(0.f, 0.f, 1.f, 1.f)

// Настройки всего окна файл-менеджера
#define VID_DIR						"rsc/vid/"
#define EXPLORER_ITEM_FONT			"rsc/fonts/JetBrainsMonoNL-Medium.ttf"
#define EXPLORER_ITEM_TEXT_SIZE		24
#define EXPLORER_ITEM_TEXT_POS_X	PREVIEW_POS_X
#define EXPLORER_ITEM_TEXT_POS_Y	EXPLORER_ITEM_HEIGHT * 0.9f
#define EXPLORER_ITEM_TIME_POS_X	PREVIEW_POS_X
#define EXPLORER_ITEM_TIME_POS_Y	EXPLORER_ITEM_HEIGHT * 0.7f
#define EXPLORER_ITEM_TEXT_COLOR	sf::Color::White
#define EXPLORER_SELECT_COLOR		sf::Color::Green
#define EXPLORER_BACK_COLOR			sf::Color::Red
#define EXPLORER_ITEM_RAWS			5
#define EXPLORER_ITEM_WIDTH			WIDTH/EXPLORER_ITEM_RAWS
#define EXPLORER_ITEM_HEIGHT		WIDTH/EXPLORER_ITEM_RAWS
#define EXPLORER_SCROLL_SPEED		2500.f
#define EXPLORER_MIN_BOUNDS			sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f)
#define EXPLORER_VIEWPORT			sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT)
#define PREVIEW_WIDTH				EXPLORER_ITEM_WIDTH*0.9f
#define PREVIEW_HEIGHT				PREVIEW_WIDTH / 16 * 9
#define PREVIEW_POS_X				(EXPLORER_ITEM_WIDTH-PREVIEW_WIDTH)*0.5f
#define PREVIEW_POS_Y				PREVIEW_POS_X

// Настройки всего окна видеоплеера
#define VIDEOPLAYER_MIN_BOUNDS		sf::FloatRect(0.f, 0.f, 0.5f, 0.5f)
#define VIDEOPLAYER_SEEKER_COLOR	sf::Color::Magenta
#define VIDEOPLAYER_BAR_COLOR		sf::Color::Yellow
#define VIDEOPLAYER_BAR_HEIGHT		HEIGHT*0.025f
#define VIDEOPLAYER_VIEWPORT		sf::FloatRect(0.f, 0.f, WIDTH, HEIGHT)

// Настройки всего окна доски
#define BOARD_BACK_COLOR			sf::Color::Black
#define BOARD_MIN_BOUNDS			sf::FloatRect(0.5f, 0.f, 0.5f, 1.f)
#define BOARD_VIEWPORT				sf::FloatRect(0.f, 0.f, WIDTH*0.5f, HEIGHT)
#define BOARD_MOVE_SPEED			50.f
#define BOARD_ZOOM_SPEED			6.f

// Настройки каркаса
#define CARCASS_COLOR				sf::Color::Blue
#define CARCASS_HEIGHT				100.f
#define CARCASS_OUTLINE_THICKNESS	10.f
#define CARCASS_COLOR_SELECT		sf::Color::Yellow
#define CARCASS_COLOR_UNSELECT		sf::Color::Transparent
#define TIMELINE_WIDTH_FACTOR		5
#define TIMELINE_HEIGHT				5.f
#define TIMELINE_COLOR				sf::Color::White
#define TIMELINE_LEFT_INDENTATION	10.f
#define TIMELINE_TOP_INDENTATION	10.f

#define DELIMITER_COLOR				sf::Color::White
#define DELIMITER_WIDTH				5.f
#define DELIMITER_HEIGHT			10.f
#define DELIMITER_FREQUENCY			5
#define DELIMITER_LEFT_INDENTATION	TIMELINE_LEFT_INDENTATION
#define DELIMITER_TOP_INDENTATION	TIMELINE_TOP_INDENTATION
#define CARCASS_VID_NAME_FONT		"No Limits.ttf"
#define CARCASS_VID_NAME_COLOR		sf::Color::White
#define CARCASS_VID_NAME_SIZE		25
#define CARCASS_VID_NAME_POS_Y		50.f

// Настройки скриншота
#define SCREENSHOT_RECT_COLOR_A		sf::Color::White
#define SCREENSHOT_RECT_COLOR_B		sf::Color::Green
#define SCREENSHOT_RECT_COLOR_C		sf::Color::Yellow
#define SCREENSHOT_RECT_THICKNESS	3.f
#define SCREENSHOT_SIZE				1000.f
#define SCREENSHOT_POS_Y			CARCASS_HEIGHT * 0.15f

// Настройки ассет менеджера
#define FONTS_DIR					"rsc/fonts/"

// Настройки нод
#define NODE_COLOR_SELECT			sf::Color::Yellow
#define NODE_COLOR_UNSELECT			sf::Color::Transparent
#define NODE_OUTLINE_THK			2.f

// Настроки субтитров
#define SUBS_DIR					"rsc/subs/"
#define SUBS_FONT					"No Limits.ttf"
#define SUBS_COLOR					sf::Color::White
#define SUBS_SIZE					50
#define SUBS_POS_Y_FACTOR			0.25f	// 0.25f puts selection in Y middle of selected text
#define SUBS_POS					sf::Vector2f(WIDTH*0.5f,HEIGHT*0.92f)
#define SUBS_LINES_INDENTATION		50
#define SUBS_SELECT_COLOR			sf::Color::Blue
#define SUBS_SELECT_SHIFT_Y			0.4f

#define TIME_FONT					"No Limits.ttf"
#define TIME_COLOR					sf::Color::White
#define TIME_SIZE					30
#define TIME_POS					sf::Vector2f(WIDTH*0.99f,HEIGHT*0.96f)

#define SEARCH_DIR					"rsc/search/search_data.json"
#define START_SEARCH_WORD			L"alexandr"

#define SEARCHBOX_CHAR_SIZE			50
#define SEARCHBOX_CHAR_LIMIT		40
#define SEARCHBOX_CHAR_COLOR		sf::Color::White
#define SEARCHBOX_CHAR_FONT			"No Limits.ttf"
#define SEARCH_RECT_COLOR			sf::Color::Black
#define SEARCH_RECT_HEIGHT			SEARCHBOX_CHAR_SIZE * 1.5f
#define SEARCHBOX_RECT_POS			sf::Vector2f(0.f, WINDOW_TOP_RECT)
#define SEARCHBOX_CHAR_POS			sf::Vector2f(SEARCHBOX_CHAR_SIZE, WINDOW_TOP_RECT) //  + SEARCH_RECT_HEIGHT * 0.25f