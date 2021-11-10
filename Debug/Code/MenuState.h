#pragma once
#include "State.h"

using namespace sf;

class MenuState :public State
{
    Sprite Banner;
    Sprite Background;

public:
	vector<Button> menuButtons;
	virtual int Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager);
	void Execute();


	MenuState() {

        Background.setTexture(TextureManager::getInstance()->GetTexture("background"));
        Background.setPosition(Vector2f(0, 0));
        Background.setScale(1, 1.06);


		Button play(Color::Transparent, Color::Black, Color::Yellow, Vector2f(200, 80), Vector2f(475, 220), "Frostbite");
		Button options(Color::Transparent, Color::Black, Color::Yellow, Vector2f(200, 80), Vector2f(475, 350), "Frostbite");
        Button leaderboard(Color::Transparent, Color::Black, Color::Yellow, Vector2f(300, 80), Vector2f(370, 480), "Frostbite");
		Button exit(Color::Transparent, Color::Black, Color::Yellow, Vector2f(200, 80), Vector2f(475, 610), "Frostbite");

        play.setText("PLAY", 45, Color::Black);
        options.setText("HELP", 45, Color::Black);
        leaderboard.setText("LEADERBOARD", 45, Color::Black);
        exit.setText("EXIT", 45, Color::Black);

        play.setID(3);
        options.setID(4);
        leaderboard.setID(5);
        exit.setID(6);

        play.setHoverColor(Color::Yellow);
        options.setHoverColor(Color::Yellow);
        leaderboard.setHoverColor(Color::Yellow);
        exit.setHoverColor(Color::Yellow);

        menuButtons.push_back(play);
        menuButtons.push_back(options);
        menuButtons.push_back(leaderboard);
        menuButtons.push_back(exit);

	}

};

