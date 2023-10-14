#include "board.h"
#include "settings.h"

Board::Board(): Area ( BOARD_MIN_BOUNDS, BOARD_VIEWPORT)
{
	Init();
}

Board::~Board()
{
	for (auto& i : _carcasses)
		delete i;
}

void Board::Init()
{
	// Фон окна
	_bigRect.setFillColor(BOARD_BACK_COLOR);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

	_viewControl.isMoving = false;
	//_videoPreset.video = nullptr;
}

void Board::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);

	window.draw(_bigRect);

	for (auto& i : _carcasses)
		i->Draw(window);
}

void Board::Update(sf::RenderWindow& window, float dt)
{
	//window.setView(_areaView);

	if (_viewControl.isMoving)
		moveView(window, dt);
	//else if (_viewControl.isZooming)
	//	zoomView(window, dt);
}

void Board::moveView(sf::RenderWindow& window, float dt)
{
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f delta = window.mapPixelToCoords(currentMousePos) - window.mapPixelToCoords(_viewControl.prevMousePos);

	_viewControl.prevMousePos = currentMousePos;
	_areaView.move(-delta * dt * BOARD_MOVE_SPEED);
}

void Board::setViewMoving(sf::RenderWindow& window, bool isMoving)
{ 
	_viewControl.isMoving = isMoving; 

	if (isMoving)
		_viewControl.prevMousePos = sf::Mouse::getPosition(window);
};

void Board::zoomView(sf::RenderWindow& window, float dt_zoom, float dt)
{
	float zoom_factor;

	if (dt_zoom > 0)
		zoom_factor = 1.f - dt * BOARD_ZOOM_SPEED;
	else// if (dt_zoom < 0)
		zoom_factor = 1.f + dt * BOARD_ZOOM_SPEED;

	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f zoom_center = window.mapPixelToCoords(currentMousePos, _areaView);

	sf::Vector2f view_center = _areaView.getCenter();
	view_center += (zoom_center - view_center) * (1 - zoom_factor);

	_areaView.setCenter(view_center);
	_areaView.zoom(zoom_factor);
}

void Board::createVideoPreset(const sfe::Movie* video)
{
	if (!video)
		return;

	Carcass* carcass = new Carcass(video->getDuration());
	_carcasses.push_back(carcass);
	//video->getPlayingOffset();
}

void Board::moveCarcass(bool is_move, sf::RenderWindow& window)
{

}
