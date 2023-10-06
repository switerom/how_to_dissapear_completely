#pragma once

#define GAME_NAME "How to dissapear completely"

#define WIDTH				1280
#define HEIGHT				720
#define TOTAL_VIDS			6

#define EXPLORER_TOP_RECT	WIDTH*0.02f

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