#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"


using namespace sf;

class SkillState :public State
{

public:
    vector<Button> skillButtons;
    virtual int Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager);

    SkillState() {
    
    }

};