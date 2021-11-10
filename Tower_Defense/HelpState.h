#pragma once
#include "State.h"

class HelpState : public State
{
public:
	vector<Texture> pages;
	Sprite Background;
	vector<Button> helpButtons;
	Vector2f mousePos;
	Cursor cursor;

	virtual int Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager);
	HelpState() {
		Background.setScale(0.9, 0.9);
		pages.push_back(TextureManager::getInstance()->GetTexture("HelpPage1"));
		pages.push_back(TextureManager::getInstance()->GetTexture("HelpPage2"));
		pages.push_back(TextureManager::getInstance()->GetTexture("HelpPage3"));
		pages.push_back(TextureManager::getInstance()->GetTexture("HelpPage4"));

		Button forward(Color::Transparent, Color::White, Color::Yellow, Vector2f(100, 60), Vector2f(200, 660), "Frostbite");
		Button back(Color::Transparent, Color::White, Color::Yellow, Vector2f(100, 60), Vector2f(10, 660), "Frostbite");
		Button quit(Color::Transparent, Color::White, Color::Yellow, Vector2f(100, 60), Vector2f(10, 10), "Frostbite");

		forward.setText("FORWARD", 30, Color::White);
		back.setText("BACK", 30, Color::White);
		quit.setText("QUIT", 32, Color::White);

		helpButtons.push_back(forward);
		helpButtons.push_back(back);
		helpButtons.push_back(quit);
	}

};

