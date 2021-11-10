#pragma once
#include "State.h"
#include "SFML/Graphics.hpp"


using namespace sf;

class MapSelectionState :public State
{

public:
    vector<Texture> maps;
    Sprite Background;
    Sprite mapPreivew;
    vector<Button> mapButtons;
	virtual int Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager);
    

	MapSelectionState() {
        mapPreivew.setScale(0.6, 0.6);

        Button Map1(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(50, 80), "Frostbite");
        Button Map2(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(50, 180), "Frostbite");
        Button Map3(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(50, 280), "Frostbite");
        Button Map4(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(50, 380), "Frostbite");
        Button Map5(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(50, 480), "Frostbite");
        Button Exit(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(50, 580), "Frostbite");


        Map1.setText("Map1", 40, Color::White);
        Map2.setText("Map2", 40, Color::White);
        Map3.setText("Map3", 40, Color::White);
        Map4.setText("Map4", 40, Color::White);
        Map5.setText("Map5", 40, Color::White);
        Exit.setText("Exit", 40, Color::White);

        mapButtons.push_back(Map1);
        mapButtons.push_back(Map2);
        mapButtons.push_back(Map3);
        mapButtons.push_back(Map4);
        mapButtons.push_back(Map5);
        mapButtons.push_back(Exit);
        
        maps.push_back(Texture(TextureManager::getInstance()->GetTexture("Map1")));
        maps.push_back(Texture(TextureManager::getInstance()->GetTexture("Map2")));
        maps.push_back(Texture(TextureManager::getInstance()->GetTexture("Map3")));
        maps.push_back(Texture(TextureManager::getInstance()->GetTexture("Map4")));
        maps.push_back(Texture(TextureManager::getInstance()->GetTexture("Map5")));
	}
};

