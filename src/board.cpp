#include "board.h"

Board::Board(): Area ( BOARD_MIN_BOUNDS, BOARD_VIEWPORT)
{
	Init();
}

Board::~Board()
{
}

void Board::Init()
{
	// Фон окна
	_bigRect.setFillColor(BOARD_BACK_COLOR);
	_bigRect.setSize(sf::Vector2f(WIDTH, HEIGHT));

	_viewControl.isMoving = false;
	_selectedNodeID = NOT_SELECTED;
	_control.isNodeMoving = false;
	_control.selectShift = sf::Vector2f(0.f, 0.f);
	_control.isCutting = false;
	_control.isLinePulled = false;
	_control.mousePos = sf::Vector2f(0.f, 0.f);
}

void Board::Draw(sf::RenderWindow& window)
{
	window.setView(_areaView);

	window.draw(_bigRect);

	for (auto& i : _layers)
		_nodes.at(i)->Draw(window);

	for (auto& i : _lines)
		window.draw(i.second->v, 4, sf::Quads);

	if (_control.isLinePulled)
		window.draw(_pulledLine.v, 4, sf::Quads);
}

void Board::Update(sf::RenderWindow& window, float dt)
{
	//window.setView(_areaView);

	if (_viewControl.isMoving)
		moveView(window, dt);
	else if (_control.isNodeMoving)
	{
		moveNode(window);
	}
	else if (_control.isLinePulled)
	{
		sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
		_control.mousePos = window.mapPixelToCoords(currentMousePos, _areaView);

		_pulledLine.moveLine(_control.pulledLineNodePos, _control.mousePos);
	}
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

void Board::selectNode(sf::RenderWindow& window)
{
	if (_nodes.empty())
		return;

	if(_selectedNodeID != NOT_SELECTED)
		_nodes.at(_selectedNodeID)->select(false);

	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	auto it = std::make_reverse_iterator(_layers.end());  // get reverse iterator to last element in vector

	while (it != std::make_reverse_iterator(_layers.begin()))
	{
		auto rect = _nodes.at(*it)->getRect();

		if (isColliding(worldPos, rect))
		{
			_nodes.at(*it)->select(true);

			// нужно для того, чтобы каркасс перемещался ровно из того места, где его взяли
			_control.selectShift.x = worldPos.x - rect.left;
			_control.selectShift.y = worldPos.y - rect.top;

			_selectedNodeID = *it;
			// Change layers order
			auto it = std::find(_layers.begin(), _layers.end(), _selectedNodeID);
			_layers.erase(it);
			_layers.push_back(_selectedNodeID);

			return;
		}
		++it;
	}

	_selectedNodeID = NOT_SELECTED;
}

void Board::moveNode(sf::RenderWindow& window)
{
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	if (_selectedNodeID != NOT_SELECTED)
	{
		sf::Vector2f pos;
		pos.x = worldPos.x -_control.selectShift.x + NODE_OUTLINE_THK;
		pos.y = worldPos.y -_control.selectShift.y + NODE_OUTLINE_THK;
		_nodes.at(_selectedNodeID)->setPosition(pos);
	}

	// Move all lines connected to moved node
	for (auto& line : _lines)
	{
		if (line.first.src == _selectedNodeID || line.first.dest == _selectedNodeID)
		{
			sf::Vector2f point1 = sf::Vector2f(_nodes.at(line.first.src)->getRect().left, _nodes.at(line.first.src)->getRect().top);
			sf::Vector2f point2 = sf::Vector2f(_nodes.at(line.first.dest)->getRect().left, _nodes.at(line.first.dest)->getRect().top);

			line.second->moveLine(point1, point2);
		}
	}
}

void Board::deleteNode()
{
	if (_selectedNodeID == NOT_SELECTED)
		return;

	_nodes.erase(_selectedNodeID);

	//Remove edges
	for (auto line = _lines.begin(); line != _lines.end();)
	{
		if (line->first.src == _selectedNodeID || line->first.dest == _selectedNodeID)
		{
			line = _lines.erase(line);
		}
		else
			++line;
	}

	// Remove from layers
	auto it = std::find(_layers.begin(), _layers.end(), _selectedNodeID);
	_layers.erase(it);

	_selectedNodeID = NOT_SELECTED;
}

void Board::pullLine(sf::RenderWindow& window)
{
	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	auto it = std::make_reverse_iterator(_layers.end());  // get reverse iterator to last element in vector

	while (it != std::make_reverse_iterator(_layers.begin()))
	{
		auto rect = _nodes.at(*it)->getRect();

		if (isColliding(worldPos, rect))
		{
			_control.isLinePulled = true;

			_control.pulledLineNode = *it;
			
			_control.pulledLineNodePos.x = _nodes.at(_control.pulledLineNode)->getRect().left;
			_control.pulledLineNodePos.y = _nodes.at(_control.pulledLineNode)->getRect().top;

			//if (_selectedNodeID != 0 && _selectedNodeID != nodeToConnect)
			//	addConnection(_selectedNodeID, nodeToConnect);
			//_selectedNodeID = NOT_SELECTED;
			return;
		}

		++it;
	}
}

void Board::releaseLine(const sf::RenderWindow& window)
{
	if (!_control.isLinePulled)
		return;

	sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
	sf::Vector2f worldPos = window.mapPixelToCoords(currentMousePos, _areaView);

	auto it = std::make_reverse_iterator(_layers.end());  // get reverse iterator to last element in vector

	while (it != std::make_reverse_iterator(_layers.begin()))
	{
		auto rect = _nodes.at(*it)->getRect();

		if (isColliding(worldPos, rect))
		{
			int nodeToConnect = *it;

			if (_control.pulledLineNode != nodeToConnect)
				addConnection(_control.pulledLineNode, nodeToConnect);
			//_selectedNodeID = NOT_SELECTED;
			break;
		}

		++it;
	}

	_control.isLinePulled = false;
}

void Board::addConnection(int src, int dest)
{
	Edge edge{ src, dest };

	auto it = _lines.find(edge);
	if (it != _lines.end())
		return;

	sf::Vector2f point1 = sf::Vector2f(_nodes.at(edge.src)->getRect().left, _nodes.at(edge.src)->getRect().top);
	sf::Vector2f point2 = sf::Vector2f(_nodes.at(edge.dest)->getRect().left, _nodes.at(edge.dest)->getRect().top);

	auto line = std::make_unique<Line>();
	line->moveLine(point1, point2);
	_lines.emplace(edge, std::move(line));
}

void Board::saveBoard()
{
	if (_nodes.empty())
		return;

	std::string save_dir_path = getAbsolutePath(SAVE_DIR);
	std::string save_file_path = getAbsolutePath(SAVE_FILE);
	std::string tex_save_dir = getAbsolutePath(TEX_SAVE_DIR);

	// Create directories if they don't exist
	if (!std::filesystem::exists(save_dir_path))
		std::filesystem::create_directory(save_dir_path);

	if (!std::filesystem::exists(tex_save_dir))
		std::filesystem::create_directory(tex_save_dir);

	// Предварительно удаляем предыдущие сохранения
	for (const auto& entry : std::filesystem::recursive_directory_iterator(tex_save_dir))
	{
		if (!std::filesystem::is_directory(entry))
			std::filesystem::remove(entry.path());
	}

	std::ofstream save_file(save_file_path, std::ios::binary);
///////////////////////////////////////////////////////////////////////////////////////
	// Сохраняем количество слоев
	auto layers_size = _layers.size();
	save_file.write(reinterpret_cast<char*>(&layers_size), sizeof(layers_size));			
	
	// Сохраняем слои
	for(auto& layer:_layers)
		save_file.write(reinterpret_cast<char*>(&layer), sizeof(layer));

	// Сохраняем количество нод
	auto nodes_size = _nodes.size();
	save_file.write(reinterpret_cast<char*>(&nodes_size), sizeof(nodes_size));

	// Сохраняем ноды
	for (auto& i : _nodes)
		i.second->saveNode(i.first, save_file);

	// Сохраняем количество эджей
	auto lines_size = _lines.size();
	save_file.write(reinterpret_cast<char*>(&lines_size), sizeof(lines_size));
	
	// Сохраняем эджи
	for (auto it{ _lines.begin() }; it != _lines.end(); ++it)
	{
		Edge edge = it->first;
		save_file.write(reinterpret_cast<char*>(&edge), sizeof(edge));
	}

	save_file.close();
}

void Board::loadBoard()
{
	std::string save_file_path = getAbsolutePath(SAVE_FILE);
	std::string save_dir_path = getAbsolutePath(SAVE_DIR);

	// Create directories if they don't exist
	if (!std::filesystem::exists(save_dir_path))
		return;

	_nodes.clear();
	_lines.clear();
	_layers.clear();

	std::ifstream save_file(save_file_path, std::ios::binary);

	/////////////////////////////////////////////////////////////////////
	// Загружаем слои

	size_t layers_size;
	save_file.read(reinterpret_cast<char*>(&layers_size), sizeof(layers_size));

	int layer;

	for (size_t i{0}; i < layers_size; ++i)
	{
		save_file.read(reinterpret_cast<char*>(&layer), sizeof(layer));
		_layers.push_back(layer);
	}

	/////////////////////////////////////////////////////////////////////
	// Загружаем ноды

	size_t nodes_size;
	save_file.read(reinterpret_cast<char*>(&nodes_size), sizeof(nodes_size));

	for (size_t i{ 0 }; i < nodes_size; ++i)
	{
		int nodes_type;
		save_file.read(reinterpret_cast<char*>(&nodes_type), sizeof(nodes_type));

		if (nodes_type == SAMPLE)
		{
			int id;
			save_file.read(reinterpret_cast<char*>(&id), sizeof(id));

			sf::Vector2f pos;
			save_file.read(reinterpret_cast<char*>(&pos), sizeof(pos));

			size_t wstr_size;
			save_file.read(reinterpret_cast<char*>(&wstr_size), sizeof(wstr_size));
			std::wstring wstr(wstr_size, L'\0');
			save_file.read(reinterpret_cast<char*>(wstr.data()), wstr_size * sizeof(wchar_t));

			Audio aud;
			aud.wstr = wstr;

			std::unique_ptr<Sample> sample = std::make_unique<Sample>(pos, aud);

			_nodes.emplace(std::make_pair(id, std::move(sample)));
		}
		else if (nodes_type == STILL)
		{
			int id;
			save_file.read(reinterpret_cast<char*>(&id), sizeof(id));

			sf::Vector2f pos;
			save_file.read(reinterpret_cast<char*>(&pos), sizeof(pos));

			sf::IntRect texRect;
			save_file.read(reinterpret_cast<char*>(&texRect), sizeof(texRect));

			std::unique_ptr<Still> still = std::make_unique<Still>(id, pos, texRect);

			_nodes.emplace(std::make_pair(id, std::move(still)));
		}
	}

	/////////////////////////////////////////////////////////////////////
	// Загружаем эджи

	size_t edges_size;
	save_file.read(reinterpret_cast<char*>(&edges_size), sizeof(edges_size));

	Edge edge;

	for (size_t i{ 0 }; i < edges_size; ++i)
	{
		save_file.read(reinterpret_cast<char*>(&edge), sizeof(edge));

		sf::Vector2f pos1, pos2;

		pos1 = sf::Vector2f(_nodes.at(edge.src)->getRect().left, _nodes.at(edge.src)->getRect().top);
		pos2 = sf::Vector2f(_nodes.at(edge.dest)->getRect().left, _nodes.at(edge.dest)->getRect().top);

		std::unique_ptr<Line> line = std::make_unique<Line>();
		line->moveLine(pos1, pos2);

		_lines.emplace(edge, std::move(line));
	}

	save_file.close();
}

void Board::resetAction()
{
	_control.isNodeMoving = false;
	_control.isLinePulled = false;
	_control.isCutting = false;
	_viewControl.isMoving = false;
}