#include "areacontroller.h"
#include "collisiondetection.h"

AreaController::AreaController(Explorer& explorer, VideoPlayer& videoplayer, Board& board): _explorer(explorer), _videoplayer(videoplayer), _board(board)
{
    _areas.push_back(&explorer);
    _areas.push_back(&videoplayer);
    _areas.push_back(&board);

    _maximized = Area::None;
}

void AreaController::Draw(sf::RenderWindow& window)
{
	for (auto& area : _areas)
	{
		if (area->isMaximized())
		{
			_maximized = area->getAreaID();
			area->Draw(window);
            return;
		}
	}

    _maximized = Area::None;

	for (auto& area : _areas)
	{
		area->Draw(window);
	}
}

void AreaController::Update(sf::RenderWindow& window, float dt)
{
	for (auto& area : _areas)
	{
		if (area->isMaximized())
		{
			_maximized = area->getAreaID();
			area->Update(window, dt);
            return;
		}
	}

    _maximized = Area::None;

    for (auto& area : _areas)
    {
        area->Update(window, dt);
    }
}

void AreaController::setAreaID(Area::ID area)
{
	_maximized = area;
}

void AreaController::EventControl(sf::Event& event, sf::RenderWindow& window, TimeController& timecontroller)
{ 
    if (_explorer.isMaximized())
        explorerEvents(event, window, timecontroller);
    else if(_videoplayer.isMaximized())
        videoplayerEvents(event, window, timecontroller);
    else if (_videoplayer.isMaximized())
        boardEvents(event, window, timecontroller);
    else
    {
        
        if (event.type == sf::Event::TextEntered && _explorer.isSearchBoxSelected())
        {
            _explorer.typeInSearchBox(event);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && _explorer.isSearchBoxSelected())
        {
            _explorer.search(_explorer.getSearchBoxText());
        }

        if(isColliding(window, _explorer.getAreaView()))
            explorerEvents(event, window, timecontroller);
        else if (isColliding(window, _videoplayer.getAreaView()))
            videoplayerEvents(event, window, timecontroller);
        else if (isColliding(window, _board.getAreaView()))
            boardEvents(event, window, timecontroller);
    }
}

void AreaController::explorerEvents(sf::Event& event, sf::RenderWindow& window, TimeController& timecontroller)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            _explorer.selectItem(window);

            if (timecontroller.isDoubleClick(window))
            {
                if (isColliding(window, _explorer, _explorer.getTopBoxRect()))
                {
                    //_explorer.toggleMaximize();
                }
                else
                {
                    _videoplayer.toggleVideoPlayback(_explorer.getCurrentVideo(), _explorer.getVideoPlayback());
                }
            }
        }
    }
    else if (event.type == sf::Event::MouseWheelScrolled)
    {
        _explorer.scrollView(event.mouseWheelScroll.delta, timecontroller.getDt());
    }
}

void AreaController::videoplayerEvents(sf::Event& event, sf::RenderWindow& window, TimeController& timecontroller)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (timecontroller.isDoubleClick(window))
            {
                //_videoplayer.toggleMaximize();
            }
            else if (isColliding(window, _videoplayer, _videoplayer.getBarBounds()))
            {
                _videoplayer.changePlayTime(window);
            }
            else if (isColliding(window, _videoplayer, _videoplayer.getSubsBounds()))
            {
                _videoplayer.startSelectSubs(window);
            }
            else
            {
                _videoplayer.toggleVideoPlayback();
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            if (timecontroller.isDoubleClick(window))
            {
                //_board.createCarcass(_videoplayer.getCurrentVideo(), _videoplayer.getVideoName());
                _explorer.search(_videoplayer.getSelectedString());
            }
            else
            {
                _videoplayer.startScreenshot(window);
            }
        }
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        _videoplayer.setScreenshotRect(window);
        _videoplayer.setSelectSubs(window);
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            _videoplayer.endSelectSubs();
        }
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            _videoplayer.endScreenshot();
            _board.addScreenshot(_videoplayer.getScreenshot());
        }
    }
}

void AreaController::boardEvents(sf::Event& event, sf::RenderWindow& window, TimeController& timecontroller)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Middle)
        {
            _board.setViewMoving(window, true);
        }
        else if (event.mouseButton.button == sf::Mouse::Left)
        {
            _board.selectCarcass(window);
            _board.setCarcassMoving(true);
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Middle)
        {
            _board.setViewMoving(window, false);
        }
        else if (event.mouseButton.button == sf::Mouse::Left)
        {
            _board.setCarcassMoving(false);
        }
    }
    else if (event.type == sf::Event::MouseWheelScrolled)
    {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
        {
            _board.zoomView(window, event.mouseWheelScroll.delta, timecontroller.getDt());
        }
    }
}