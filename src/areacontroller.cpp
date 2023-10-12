#include "areacontroller.h"
#include "collisiondetection.h"

AreaController::AreaController(Explorer& explorer, VideoPlayer& videoplayer): _explorer(explorer), _videoplayer(videoplayer)
{
    _areas.push_back(&explorer);
    _areas.push_back(&videoplayer);

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

    _maximized == Area::None;

	for (auto& area : _areas)
	{
		area->Draw(window);
	}
}

void AreaController::Update(float dt)
{
	for (auto& area : _areas)
	{
		if (area->isMaximized())
		{
			_maximized = area->getAreaID();
			area->Update(dt);
            return;
		}
	}

    _maximized == Area::None;

    for (auto& area : _areas)
    {
        area->Update(dt);
    }
}

void AreaController::setAreaID(Area::ID area)
{
	_maximized = area;
}

void AreaController::EventControl(sf::Event& event, sf::RenderWindow& window, TimeController& timecontroller)
{ 
    if (_explorer.isMaximized())
    {
        explorerEvents(event, window, timecontroller);
    }
    else if(_videoplayer.isMaximized())
        videoplayerEvents(event, window, timecontroller);
    else
    {
        if(isColliding(window, _explorer))
            explorerEvents(event, window, timecontroller);
        else if (isColliding(window, _videoplayer))
            videoplayerEvents(event, window, timecontroller);
    }
    
    //if (event.type == sf::Event::MouseButtonPressed)
    //{
    //    if (event.mouseButton.button == sf::Mouse::Left)
    //    {
    //        if (isColliding(window, _explorer))  
    //        {
    //            _explorer.selectItem(window);

    //            if (timecontroller.isDoubleClick(window))
    //            {
    //                if (isColliding(window, _explorer, _explorer.getTopBoxRect()))
    //                {
    //                    _explorer.toggleMaximize();
    //                }
    //                else
    //                {
    //                    _videoplayer.toggleVideoPlayback(_explorer.getCurrentVideo());
    //                }
    //            }
    //        }
    //        else if (isColliding(window, _videoplayer))
    //        {
    //            if (timecontroller.isDoubleClick(window))
    //            {
    //                _videoplayer.toggleMaximize();
    //            }
    //            else if (isColliding(window, _videoplayer, _videoplayer.getBarBounds()))
    //            {
    //                _videoplayer.changePlayTime(window);
    //            }
    //            else
    //            {
    //                _videoplayer.toggleVideoPlayback();
    //            }
    //        }
    //    }
    //}
    //else if (event.type == sf::Event::MouseWheelScrolled)
    //{
    //    _explorer.scrollView(event.mouseWheelScroll.delta, timecontroller.getDt());
    //}
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
                    _explorer.toggleMaximize();
                }
                else
                {
                    _videoplayer.toggleVideoPlayback(_explorer.getCurrentVideo());
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
                _videoplayer.toggleMaximize();
            }
            else if (isColliding(window, _videoplayer, _videoplayer.getBarBounds()))
            {
                _videoplayer.changePlayTime(window);
            }
            else
            {
                _videoplayer.toggleVideoPlayback();
            }
        }
    }
}