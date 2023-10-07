#pragma once

#define GAME_NAME "How to dissapear completely"

#define WIDTH				1280
#define HEIGHT				720
#define TOTAL_VIDS			6

#define EXITEM_X_POS		WIDTH*0.1f
#define EXITEM_Y_POS		WIDTH*0.1f
#define EXITEM_Y_DIST		WIDTH*0.05f
#define LINE_THK			3.f

#define BOARD_MOVE_SPEED	50.f


#define MIN_VIEW_SIZE 		700.f
#define MAX_VIEW_SIZE		4000.f

#define ZOOM_FACTOR(delta_zoom) (1.f - (delta_zoom) / 10.f)

#define NOT_SELECTED		0

#define LINE_THICKNESS		7.f
#define EPSILON				0.0001f

#define BAR_HEIGHT			15.f

#define FONT				"rsc/fonts/CascadiaCode.ttf"
#define SUB_SIZE			35
#define SUB_COLOR			sf::Color::White
#define SUB_POSITION		sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.9f)

#define SUB_SELECT_COLOR	sf::Color::Blue
#define SUB_SELECT_SIZE_Y	SUB_SIZE
#define SUB_SELECT_POS_Y	HEIGHT * 0.875f	

#define TEXT_NOTE_SIZE		75

#define SAVES_DIR			"C:/_FILES/CATEGORIES/MY_FILM-GAME/code/detective_film_game/game/saves"

// Настройки всего окна файл-менеджера
#define EXPLORER_TOP_RECT			HEIGHT*0.025f
#define VID_DIR						"rsc/vid"
#define EXPLORER_ITEM_FONT			"rsc/fonts/JetBrainsMonoNL-Medium.ttf"
#define EXPLORER_ITEM_TEXT_SIZE		24
#define EXPLORER_ITEM_TEXT_COLOR	sf::Color::White
#define EXPLORER_SELECT_COLOR		sf::Color::Green
#define EXPLORER_BACK_COLOR			sf::Color::Red
#define EXPLORER_FRAME_COLOR		sf::Color::Blue
#define EXPLORER_ITEM_SIZE_Y		HEIGHT*0.1f
#define EXPLORER_SCROLL_SPEED		50.f
#define EXPLORER_MIN_BOUNDS			sf::FloatRect(0.f, 0.5f, 0.5f, 0.5f)
#define EXPLORER_MAX_BOUNDS			sf::FloatRect(0.f, 0.f, 1.f, 1.f)