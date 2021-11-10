#pragma once
#include "State.h"

class GameOverState : public State
{

public:
	vector<Button> gameOverButtons;
	virtual int Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager);
	Text display;
	Text Score;

	GameOverState() {
		//Button repeat(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(450, 200), "Frostbite");
		display.setCharacterSize(50);
		display.setFillColor(Color::White);
		display.setPosition(Vector2f(390, 150));
		display.setFont(TextureManager::getInstance()->GetFont("Frostbite"));

		Score.setCharacterSize(50);
		Score.setPosition(Vector2f(500, 250));
		Score.setFont(TextureManager::getInstance()->GetFont("Frostbite"));
		

		Button quit(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(470, 350), "Frostbite");
		Button menu(Color::Transparent, Color::White, Color::Yellow, Vector2f(200, 80), Vector2f(440, 460), "Frostbite");

		//repeat.setText("Try Again", 40, Color::White);
		quit.setText("Quit", 40, Color::White);
		menu.setText("Main Menu", 40, Color::White);

		//repeat.setHoverColor(Color::Yellow);
		quit.setHoverColor(Color::Yellow);
		menu.setHoverColor(Color::Yellow);

		//gameOverButtons.push_back(repeat);
		gameOverButtons.push_back(quit);
		gameOverButtons.push_back(menu);
	}
};

