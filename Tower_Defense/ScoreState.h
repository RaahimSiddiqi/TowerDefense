#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"


using namespace sf;

class ScoreState :public State
{
    Text title;
    Sprite Banner;
    Sprite Banner2;

public:
    vector<Button> scoreButtons;
    virtual int Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager);

    ScoreState() {
        Banner.setPosition(890, 200);
        Banner.setTexture(TextureManager::getInstance()->GetTexture("Banner"));
        Banner2.setPosition(100, 200);
        Banner2.setTexture(TextureManager::getInstance()->GetTexture("Banner"));

        Button exit(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(50, 610), "Frostbite");
        exit.setText("EXIT", 50, Color::White);
        exit.setHoverColor(Color::Yellow);
        scoreButtons.push_back(exit);

        title.setCharacterSize(60);
        title.setFillColor(Color::Red);
        title.setFont(TextureManager::getInstance()->GetFont("MachineGunk"));
        title.setPosition(500, 50);
        title.setString("TOP SCORES");
    }

};