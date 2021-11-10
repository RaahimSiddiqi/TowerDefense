#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameManager.h"
#include "DisplayMenu.h"
#include "map.h"
#include <windows.h>

GameManager* GameManager::instance = nullptr;

GameManager::GameManager(RenderWindow& window) : Window(window){
    instance = this;
    FPS = 60;
    Map = 0;
    score = 0;
    SYSTEM_INFO siSysInfo;

    // Copy the hardware information to the SYSTEM_INFO structure. 
    GetSystemInfo(&siSysInfo);

    file.open("GameLog.txt");

    file << "--------GAME LOG-------------" << endl;
    file << "OEM ID: " << siSysInfo.dwOemId << endl;
    file << "Processor Type: " << siSysInfo.dwProcessorType << endl;
    file << "Number of Processors: " << siSysInfo.dwNumberOfProcessors << endl;
    file << "Page File Size: " << siSysInfo.dwPageSize << endl;

}

void GameManager::toggleGridMode() {
    if (gridmode == 0) {
        gridmode = 1;
       // Map::getInstance()->onToggleGridMode();
    }
    else {
        gridmode = 0;
        //Map::getInstance()->offToggleGridMode();
    }
}

void GameManager::toggleTileMode() {
    if (tilemode == 0) {
        tilemode = 1;
        Map::getInstance()->onToggleTileMode();
    }
    else {
        tilemode = 0;
        Map::getInstance()->offToggleTileMode();
    }
}

void GameManager::Update(Vector2f mousePos) {
    removeSounds();

    if (battleOn == 1) {

        removeEffects();
        removeBullets();
        removeEnemies();
        checkCollisions();

        DisplayMenu::getInstance()->Update(mousePos);

        for (unsigned int i = 0; i < Spells.size(); i++) {
            if (Spells[i].Update() == 0) {
                Spells.erase(Spells.begin() + i);
            }
        }

        for (unsigned int i = 0; i < DestroyedBullets.size(); i++) {
            if (DestroyedBullets[i]->PlayAnimation() == 0) {
                DestroyedBullets.erase(DestroyedBullets.begin() + i);
            }
            else {
                Window.draw(DestroyedBullets[i]->sprite);
            }
        }

    }
}

void GameManager::PlaySoundEffect(string name) {
    this->sounds.push_back(Sound());
    sounds.back().setBuffer(TextureManager::getInstance()->GetSound(name));
    sounds.back().setVolume(masterVolume * VolumeMultiplier);
    sounds.back().play();
}


void GameManager::PlaySoundEffect(string name, float vol) {
    this->sounds.push_back(Sound());
    sounds.back().setBuffer(TextureManager::getInstance()->GetSound(name));
    sounds.back().setVolume(vol * VolumeMultiplier);
    sounds.back().play();
}


void GameManager::removeSounds() {
    list<Sound>::iterator i;
    for (i = this->sounds.begin(); i != this->sounds.end();) {
        if (i->getStatus() == SoundSource::Status::Stopped)
        {
            i = sounds.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

void GameManager::removeEffects() {
    vector<DamageEffect>::iterator i;
    for (i = this->dmgEffects.begin(); i != this->dmgEffects.end();) {
        if ( i->getFrame() >= 60)
        {
            i = dmgEffects.erase(i);
        }
        else
        {
            i->Update(Window);
            ++i;
            
        }
    }
}

GameManager* GameManager::getInstance()
{
    return instance;
}

GameManager::~GameManager()
{
    file.close();
    if (instance == this)
    {
        instance = nullptr;
    }
}


int GameManager::removeBullets() {
    if (bullets.size() == 0) {
        return 0;
    }

    for (unsigned int i = 0; i < bullets.size(); i++) {
        if (!((bullets[i]->shot.getPosition().x < 1000 && bullets[i]->shot.getPosition().x > 0) && (bullets[i]->shot.getPosition().y < 600 && bullets[i]->shot.getPosition().y > 0))) {
            bullets.erase(bullets.begin() + i);
        }
    }
    return 1;
}


int GameManager::removeEnemies() {
    if (Enemies.size() == 0) {
        return 0;
    }

    for (unsigned int i = 0; i < Enemies.size(); i++) {
        if (Enemies[i]->shape.getGlobalBounds().intersects(Map::getInstance()->castleSprite.getGlobalBounds())) {
            DisplayMenu::getInstance()->setHealth((int) DisplayMenu::getInstance()->getHealth(), -Enemies[i]->getAttack()); 
            Enemies[i]->setHealth(0);
            LevelManager::getInstance()->enemyKilled(Enemies[i]->getName());
            score -= Enemies[i]->getAttack() + Enemies[i]->getMaxHealth();
            Enemies.erase(Enemies.begin() + i);
        }
    }
    return 1;
}


void GameManager::checkDeadEnemies() {
    for (unsigned int i = 0; i < Enemies.size(); i++) {
        if (Enemies[i]->getHealth() <= 0) {
            DisplayMenu::getInstance()->setMoney(DisplayMenu::getInstance()->getMoney() + Enemies[i]->getMoney());
            LevelManager::getInstance()->enemyKilled(Enemies[i]->getName());
            Enemies.erase(Enemies.begin() + i);   
        }
    }

}

void GameManager::checkDeadEnemy(Enemy &enemy, int index) {
    if (Enemies[index]->getHealth() <= 0) {
        DisplayMenu::getInstance()->setMoney(DisplayMenu::getInstance()->getMoney() + enemy.getMoney());
        LevelManager::getInstance()->enemyKilled(Enemies[index]->getName());
        Enemies.erase(Enemies.begin() + index);
    }
}

int GameManager::checkCollisions() {

    if (bullets.size() == 0 || Enemies.size() == 0) {
        return 0;
    }

    for (unsigned int i = 0; i < bullets.size(); i++) {
        for (unsigned int j = 0; j < Enemies.size(); j++) {
           // cout << "BULLETS: " << bullets.size() <<  "   I: " << i << endl;
           // cout << "ENEMIES: " << Enemies.size() << "    J: " << j << endl;

            if (bullets[i]->shot.getGlobalBounds().intersects(Enemies[j]->shape.getGlobalBounds())) {     
               // cout << "Collision!" << endl;
                int armor = Enemies[j]->getArmor();
                if (bullets[i]->getType() == "magic" || bullets[i]->getType() == "poison") {
                    armor = 0;
                }
                else {
                    armor = Enemies[j]->getArmor();
                }
                if (Enemies[j]->getHealth() - bullets[i]->getAttack() + armor <= 0) {
                    //Enemies[j].takeDamage(bullets[i].getAttack());               
                    LevelManager::getInstance()->enemyKilled(Enemies[j]->getName());
                    DisplayMenu::getInstance()->setMoney(DisplayMenu::getInstance()->getMoney() + Enemies[j]->getMoney());
                    if (bullets[i]->getTextureBurst() == 1) {
                        DestroyedBullets.push_back(bullets[i]);
                    }
                    Enemies[j]->takeDamage(bullets[i]->getAttack(), Color::White, bullets[i]->getType());
                    score += Enemies[j]->getAttack() + Enemies[j]->getMaxHealth();
                    bullets.erase(bullets.begin() + i);
                    Enemies.erase(Enemies.begin() + j);
      
                }    
                else {
                   Enemies[j]->takeDamage(bullets[i]->getAttack(), Color::White, bullets[i]->getType());
                   if (bullets[i]->getTextureBurst() == 1) {
                       DestroyedBullets.push_back(bullets[i]);
                   }
                   Enemies[j]->ApplyEffect(bullets[i]->getEffect(), bullets[i]->getAttack(), bullets[i]->getDuration());
                   bullets.erase(bullets.begin() + i);
                    Enemies[j]->setColor();
                }
                j = Enemies.size();              
            }
        }   
    }
    return 1;
}

int GameManager::checkCost(int ID) {
    if (DisplayMenu::getInstance()->getMoney() >= costs[ID]) {
        cout << "Enough money is availbile" << endl;
        DisplayMenu::getInstance()->setMoney(DisplayMenu::getInstance()->getMoney() - costs[ID]);
        return 1;
    }
    else {
        return 0;
    }
    
}

void GameManager::removeTower() {
    for (unsigned int i = 0; i < towers.size(); i++) {
        if (towers[i]->builtFlag == 0) {
            DisplayMenu::getInstance()->setMoney(DisplayMenu::getInstance()->getMoney() + towers[i]->getRefund());
            towers.erase(towers.begin() + i);
        }
    }

}

void GameManager::clear() {
    Enemies.clear();
    towers.clear();
    Spells.clear();
    music.stop();
    gameState = 0;
}
