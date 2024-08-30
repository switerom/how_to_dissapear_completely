#pragma once

#include "stdafx.h"
#include "node.h"

class Fragment: public Node
{
public:
	Fragment();
	~Fragment() {};

protected:
	sf::Text _text;

};
