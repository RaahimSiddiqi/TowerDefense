#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "button.h"
#include "LevelManager.h"
#include "Spell.h"
#include <list>
#include <deque>
#include <fstream>
#include "DamageEffect.h"
#include "CountDown.h"

using namespace sf;
using namespace std;

class GameManager {
	
	static GameManager* instance;
	int buildTower = 1;
	int costs[7] = { 200, 300, 400 , 500, 500, 500, 250};
	list<Sound> sounds;
	float masterVolume = 50.f;
	float VolumeMultiplier = 1.f;
	int Map;
	int score;


public:
	ofstream file;
	RenderWindow& Window;
	Music music;
	vector<shared_ptr<Tower>> towers;
	vector<shared_ptr<Bullet>> bullets;
	vector<shared_ptr<Bullet>> DestroyedBullets;
	vector<Button> buttons;
	vector<shared_ptr<Enemy>> Enemies;
	vector<Spell> Spells;
	vector<DamageEffect> dmgEffects;
	vector<CountDown> countDowns;

	int getScore() { return score;  }
	int addScore(int n) { score += n;  }
	int lowerScore(int n) { score -= n; }
	void resetScore() { score = 0;  }

	float CastleHealth = 100;
	float FPS;
	int gridmode = 0;
	int tilemode = 1;
	int battleOn = 0;
	int gameState = 0; // 0 is for pre-battle phase
	                   // 1 is for battle
	                   // 2 is for win
	                   // 3 is for lose

	void AddTower(Tower tower);
	void UpdateSprites();
	GameManager(RenderWindow& window);
	int removeEnemies();
	~GameManager();
	static GameManager* getInstance();
	int checkCollisions();
	int removeBullets();
	int checkCost(int);
	void removeTower();
	
	void toggleGridMode();
	void toggleTileMode();
	void Update(Vector2f);
	void CreateTower(int ID);
	void checkDeadEnemies();
	void checkDeadEnemy(Enemy& enemy, int index);

	void removeSounds();
	void removeEffects();
	void PlaySoundEffect(string name);
	void PlaySoundEffect(string name, float volume);
	void clear();

	int getMap() { return Map; };
	int setMap(int map) { 
		Map = map;
		if (!music.openFromFile("./Sounds/background.wav"))
			return -1;
		music.play();
		music.setVolume(20 * VolumeMultiplier);
		music.setLoop(true);
		return 1;
	}

	void incVolume() {
		VolumeMultiplier += 0.2f;
		if (VolumeMultiplier > 2) VolumeMultiplier = 2;
		music.setVolume(20 * VolumeMultiplier);
	}

	void decVolume() {
		VolumeMultiplier -= 0.2f;
		if (VolumeMultiplier < 0) VolumeMultiplier = 0;
		music.setVolume(20 * VolumeMultiplier);
	}
};