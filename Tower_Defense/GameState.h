#pragma once
#include "State.h"
#include "button.h"
#include <list>
#include <deque>
#include "GameManager.h"
#include "DisplayMenu.h"
#include "basicTower.h"
#include "arrowTower.h"
#include "magicTower.h"
#include "MudBullet.h"
#include "MagicBullet.h"
#include "PoisonBullet.h"
#include "ArrowBullet.h"
#include "FireBullet.h"
#include "IceBullet.h"
#include "IceTower.h"
#include "poisonTower.h"
#include "WindBullet.h"
#include "MortarTower.h"
#include "WizardTower.h"

class GameState : public State
{
    TextureManager& textureManager;
    Sprite cute;
    Text wave;
    Text score;
    Cursor cursor;
    float fps;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime;
    sf::Time currentTime;

public:
	virtual int Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager);

	GameState(RenderWindow& window, TextureManager& t) : textureManager(t) {
        fps = 0;
        if (cursor.loadFromSystem(sf::Cursor::Arrow))
            window.setMouseCursor(cursor);

        cute.setTexture(textureManager.GetTexture("WoodMenu"));
        cute.setPosition(400, 582);


        wave.setFont(textureManager.GetFont("Frostbite"));
        wave.setCharacterSize(32);
        wave.setPosition(480, 585);
        wave.setString("Wave 0");

        score.setCharacterSize(30);
        score.setFont(textureManager.GetFont("Neuropol"));
        score.setFillColor(Color::White);
        score.setPosition(Vector2f(1040, 200));
	}
};

