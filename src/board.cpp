#include "board.h"
#include "settings.h"
#include "keygen.h"
#include "collisiondetection.h"

Board::Board(): Area ( BOARD_MIN_BOUNDS, BOARD_VIEWPORT)
{
	Init();
}

Board::~Board()
{
	if (_carcasses.empty())
		return;

	for (auto& i : _carcasses)
		delete i.second;
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

	for (auto& i : _layers)
		_carcasses.at(i)->Draw(window);
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

void Board::createCarcass(const sfe::Movie* video)
{
	if (!video)
		return;

	Carcass* carcass = new Carcass(video->getDuration());

	int id{ KeyGen::getKey() };

	while (_carcasses.find(id) != _carcasses.end())
		id = KeyGen::getKey();

	_carcasses.emplace(id, carcass);
	_layers.push_back(id);
}

void Board::moveCarcass(bool is_move, sf::RenderWindow& window)
{

}

void Board::selectCarcass(sf::RenderWindow& window)
{
	if (_carcasses.empty())
		return;

	auto it = std::make_reverse_iterator(_layers.end());  // reverse итератор потому, что мы в конце находится слой, который выше отображается

	while (it != std::make_reverse_iterator(_layers.begin()))
	{
		sf::FloatRect bounds = _carcasses.at(*it)->getBounds();

		if (isColliding(window, *this, bounds))
		{
			_movecontrol.selectedCarcass = *it;

			// меняем порядок слоев
			auto it = std::find(_layers.begin(), _layers.end(), _movecontrol.selectedCarcass);
			_layers.erase(it);
			_layers.push_back(_movecontrol.selectedCarcass);

			return;
		}
		++it;
	}

	_movecontrol.selectedCarcass = NOT_SELECTED;
}
