#include "LevelManager.h"
#include "Minotaur.h"
#include "BlueMinotaur.h"
#include "Wraith.h"
#include "Troll.h"

LevelManager* LevelManager::instance = nullptr;

LevelManager::LevelManager() {
	instance = this;
	levelInterlude = 1;
	active = 0;
}

void LevelManager::Begin() {
	SpawnClocks.push_back(Clock());  // Minotaur
	SpawnClocks.push_back(Clock());  // Blue Minotaur
	SpawnClocks.push_back(Clock());  // Wraiths
	SpawnClocks.push_back(Clock());  // Trolls

	this->active = 1;
	GameManager::getInstance()->gameState = 1;
}

void LevelManager::EndLevel() {

}

void LevelManager::Update() {
	if (this->active == 0) return;

	if (this->wave != 0 && this->levelInterlude == 0) {

		
		if (SpawnClocks[0].getElapsedTime().asMilliseconds() > Minos[0] && generatedEnemies[0] < waveEnemies[0] && minSpawnTime.getElapsedTime().asMilliseconds() > 500) {
			GameManager::getInstance()->Enemies.push_back(shared_ptr<Enemy>(new Minotaur(round + 1)));
			generatedEnemies[0] += 1;
			ResetClock(0);
		}
		if (SpawnClocks[1].getElapsedTime().asMilliseconds() > BlueMinos[0] && generatedEnemies[1] < waveEnemies[1] && minSpawnTime.getElapsedTime().asMilliseconds() > 500) {
			GameManager::getInstance()->Enemies.push_back(shared_ptr<Enemy>(new BlueMinotaur(round + 1)));
			generatedEnemies[1] += 1;
			ResetClock(1);
		}
		if (SpawnClocks[2].getElapsedTime().asMilliseconds() > Wraiths[0] && generatedEnemies[2] < waveEnemies[2] && minSpawnTime.getElapsedTime().asMilliseconds() > 500) {
			GameManager::getInstance()->Enemies.push_back(shared_ptr<Enemy>(new Wraith(round + 1)));
			generatedEnemies[2] += 1;
			ResetClock(2);
		}
		if (SpawnClocks[3].getElapsedTime().asMilliseconds() > Trolls[0] && generatedEnemies[3] < waveEnemies[3] && minSpawnTime.getElapsedTime().asMilliseconds() > 500) {
			GameManager::getInstance()->Enemies.push_back(shared_ptr<Enemy>(new Troll(round + 1)));
			generatedEnemies[3] += 1;
			ResetClock(3);
		}



	}
	else if (levelInterlude == 1) {
		if (timer.getElapsedTime().asSeconds() > 5) {
			this->NextLevel();
		}
	}
}

void LevelManager::ResetClocks() {
	for (int i = 0; i < SpawnClocks.size(); i++) {
		SpawnClocks[i].restart();
	}
	minSpawnTime.restart();
}

void LevelManager::LevelCorrection() {
	Minos[1] += 10;
	BlueMinos[2] += 5;
	Trolls[5] += 5;
}

void LevelManager::LevelUpdate() {
	for (int i = 1; i < 11; i++) {
		Minos[i] += BaseMinos[i];
		BlueMinos[i] += BaseBlueMinos[i];
		Wraiths[i] += BaseWraiths[i];
		Trolls[i] += BaseTrolls[i];
	}
}

void LevelManager::ResetClock(int ID) {
	SpawnClocks[ID].restart();
	minSpawnTime.restart();
}

void LevelManager::LevelInterlude() {
	this->levelInterlude = 1;
}

void LevelManager::NextLevel() {
	this->wave += 1;
	if (wave == 11) {
		LevelCorrection();
	}

	if (wave == 30) {
		Win();
	}

	for (int i = 0; i < 4; i++) {
		this->generatedEnemies[i] = 0;
		
	}
	this->waveEnemies[0] = Minos[wave - (10 * round)];
	this->currEnemies[0] = Minos[wave -(10 * round)];
	this->waveEnemies[1] = BlueMinos[wave - (10 * round)];
	this->currEnemies[1] = BlueMinos[wave - (10 * round)];
	this->waveEnemies[2] = Wraiths[wave - (10 * round)];
	this->currEnemies[2] = Wraiths[wave - (10 * round)];
	this->waveEnemies[3] = Trolls[wave - (10 * round)];
	this->currEnemies[3] = Trolls[wave - (10 * round)];

	if (wave % 10 == 0) {
		round += 1;
		LevelUpdate();
	}
	
	this->levelInterlude = 0;
	GameManager::getInstance()->file << "Begin Wave " << this->wave << endl;
	this->timer.restart();
	ResetClocks();
}

LevelManager* LevelManager::getInstance()
{
	return instance;
}

LevelManager::~LevelManager()
{
	if (instance == this)
	{
		instance = nullptr;
	}
}

void LevelManager::Debug() {
	for (int i = 0; i < 4; i++) {
		cout << "Enemies Left: (" << i << ") " << currEnemies[i] << endl;
	}
}

void LevelManager::enemyKilled(string name) {
	//cout << name << " was killed " << endl;
	//Debug();
	if (name == "minotaur") this->currEnemies[0] -= 1;
	if (name == "blueminotaur") this->currEnemies[1] -= 1;
	if (name == "wraith") this->currEnemies[2] -= 1;
	if (name == "troll") this->currEnemies[3] -= 1;
	//cout << currEnemies << endl;

	if (currEnemies[0] == 0 && currEnemies[1] == 0 && currEnemies[2] == 0 && currEnemies[3] == 0) {
		cout << "stageCleared" << endl;
		LevelInterlude();
	}
}

void LevelManager::Win() {
	SpawnClocks.clear();
	active = 0;
	GameManager::getInstance()->gameState = 2;
}

void LevelManager::clear() {
	SpawnClocks.clear();
	wave = 0;
	round = 0;
}