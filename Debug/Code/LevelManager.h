#pragma once
#include "GameManager.h"

class LevelManager
{

private:
	Clock timer;
	Clock minSpawnTime;

	int currEnemies[4] = { 0, 0, 0, 0 };
	int waveEnemies[4] = { 0, 0, 0, 0 };
	int generatedEnemies[4] = { 0, 0, 0, 0 };
	int round = 0;
	int wave = 0;
	float spawnTime;
	static LevelManager* instance;
	int levelInterlude;

	int Minos[11] =     { 800,  5, 10, 0,  0 , 0 , 10, 0 , 0 , 10, 10 };
	int BlueMinos[11] = { 1200, 0, 0 , 10, 0 , 0 , 0 , 10, 0 , 10, 10 };
	int Wraiths[11] =   { 600,  0, 0 , 0 , 20, 0 , 0 , 0 , 20, 10, 0 };
	int Trolls[11] =    { 2000, 0, 0 , 0 , 0 , 5 , 5 , 5 , 5,  0 , 6 };

	int BaseMinos[11] =     { 800,  5, 10, 0,  0 , 0 , 10, 0 , 0 , 12, 10 };
	int BaseBlueMinos[11] = { 1200, 0, 0 , 10, 0 , 0 , 0 , 10, 0 , 12, 10 };
	int BaseWraiths[11] =   { 600,  0, 0 , 0 , 20, 0 , 0 , 0 , 20, 10, 0 };
	int BaseTrolls[11] =    { 2000, 0, 0 , 0 , 0 , 5 , 5 , 5 , 5,  0 , 6 };

	vector<Clock> SpawnClocks; 
	void ResetClocks();
	void ResetClock(int ID);
	void Debug();
	void LevelCorrection();
	void LevelUpdate();
	int active;

public:
	LevelManager();

	void Win();
	void NextLevel();
	void LevelInterlude();
	void EndLevel();
	void Update();
	void Begin();
	void clear();
	~LevelManager();
	static LevelManager* getInstance();
	void enemyKilled(string name);
	int getWave() {
		return wave;
	}
};

