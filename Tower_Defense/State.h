#pragma once
#include "map.h"
#include "path.h"
#include "button.h"
#include "GameManager.h"


#include <iostream>
using namespace sf;

class State
{
public:

	virtual int Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager) = 0;
};

