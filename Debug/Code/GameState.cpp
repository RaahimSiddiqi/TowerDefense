#include "GameState.h"
#include <math.h>
#include <vector>
#include <cstdlib>
#include "map.h"
#include "path.h"
#include "ConstructionMenu.h"




int GameState::Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager) {

     // These four will be destroyed once we move out of Game State
     Map mappy = Map(window);
     ConstructionMenu constructionMenu = ConstructionMenu(window, Vector2f(0, 630));
     LevelManager levelManager;
     DisplayMenu displayMenu = DisplayMenu(Vector2f(1000, 0));


     int flag = 0;
     gameManager.battleOn = 1;

     mappy.RenderMap(1000, 600, 50, 30, 1, Vector2f(0, 0));
     Path path = Path(gameManager.getMap());
     gameManager.toggleTileMode();
     mappy.RenderFoilage();

     while (window.isOpen())
     {
         Event event;
         wave.setString("Wave " + to_string(levelManager.getWave()));

         if (cursor.loadFromSystem(sf::Cursor::Arrow))
             window.setMouseCursor(cursor);

         while (window.pollEvent(event))
         {
             if (event.type == Event::Closed)
                 window.close();

             if (event.type == sf::Event::Resized) {
                 constructionMenu.updatePosition();
             }

             if (event.type == sf::Event::KeyPressed) {
                 if (event.key.code == Keyboard::G) {
                     gameManager.toggleGridMode();
                 }
                 if (event.key.code == Keyboard::T) {
                     gameManager.toggleTileMode();
                 }
                 if (event.key.code == Keyboard::Q) {
                     return 3;
                 }
                 if (event.key.code == Keyboard::B) {
                     levelManager.Begin();
                 }
                 if (event.key.code == Keyboard::M) {
                     gameManager.incVolume();
                 }
                 if (event.key.code == Keyboard::N) {
                     gameManager.decVolume();
                 }
                 if (event.key.code == Keyboard::Num1) {
                     if (constructionMenu.SpellCast(1)) {
                         for (unsigned int i = 0; i < gameManager.Enemies.size(); i++) {
                             Spell spell(gameManager.Enemies[i]->shape.getPosition());
                             gameManager.Spells.push_back(spell);
                             gameManager.Enemies[i]->takeDamage(spell.damage);
                         }
                         gameManager.checkDeadEnemies();
                     }                 
                 }
                 if (event.key.code == Keyboard::Num3) {
                     if (displayMenu.setHealth(displayMenu.getHealth(), 10)  && constructionMenu.SpellCast(3) == 1) {
                         Spell spell(mappy.castleLocation, 20);
                         gameManager.Spells.push_back(spell);
                     }
                     else {
                         cout << "Health Full" << endl;
                     }
                 }
                 if (event.key.code == Keyboard::Num2) {
                     if (constructionMenu.SpellCast(2)) {
                         for (unsigned int i = 0; i < gameManager.Enemies.size(); i++) {
                             Spell spell(gameManager.Enemies[i]->sprite.getPosition(), 20.f);
                             gameManager.Enemies[i]->ApplyEffect(4, 0, 5000);
                             gameManager.Spells.push_back(spell);
                         }
                     }
                 }
             }

             if (event.type == sf::Event::MouseButtonPressed)
             {
                 if (event.mouseButton.button == sf::Mouse::Left)
                 {

                     Vector2f mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
                     gameManager.PlaySoundEffect("MouseClick");

                     if (constructionMenu.LightningSpell.getGlobalBounds().contains(mousePos)) {
                         if (constructionMenu.SpellCast(1)) {
                             for (unsigned int i = 0; i < gameManager.Enemies.size(); i++) {
                                 Spell spell(gameManager.Enemies[i]->shape.getPosition());
                                 gameManager.Spells.push_back(spell);
                                 gameManager.Enemies[i]->takeDamage(spell.damage);
                             }
                             gameManager.checkDeadEnemies();
                         }
                     }

                     if (constructionMenu.HealthRecoverSpell.getGlobalBounds().contains(mousePos)) {
                         if (displayMenu.setHealth(displayMenu.getHealth(), 10) && constructionMenu.SpellCast(3) == 1) {
                             Spell spell(mappy.castleLocation, 20);
                             gameManager.Spells.push_back(spell);
                         }
                         else {
                             cout << "Health Full" << endl;
                         }
                     }

                     if (constructionMenu.IceSpell.getGlobalBounds().contains(mousePos)) {
                         if (constructionMenu.SpellCast(2)) {
                             for (unsigned int i = 0; i < gameManager.Enemies.size(); i++) {
                                 Spell spell(gameManager.Enemies[i]->sprite.getPosition(), 20.f);
                                 gameManager.Enemies[i]->ApplyEffect(4, 0, 5000);
                                 gameManager.Spells.push_back(spell);
                             }
                         }
                     }

                     for (unsigned int i = 0; i < gameManager.buttons.size(); i++) {
                         if (displayMenu.tower == nullptr) break;
                         int ID = gameManager.buttons[i].isClicked(mousePos);
                         if (ID != -1) {
                             displayMenu.ExecuteEvents(ID);
                         }
                     }

                     for (unsigned int i = 0; i < gameManager.Enemies.size(); i++) {
                         if (gameManager.Enemies[i]->shape.getGlobalBounds().contains(mousePos)) {
                             if (displayMenu.tower != nullptr) {
                                 //cout << "Selected target" << endl;
                                 if (displayMenu.tower->selectedEnemy == gameManager.Enemies[i]) {
                                     displayMenu.tower->selectedEnemy = nullptr;
                                 }
                                 else {
                                     displayMenu.tower->selectedEnemy = gameManager.Enemies[i];
                                 }
                             }
                         }
                     }

                     for (unsigned int i = 0; i < gameManager.towers.size(); i++) {
                         if (gameManager.towers[i]->sprite.getGlobalBounds().contains(mousePos) && gameManager.towers[i]->builtFlag == 1) {

                             if (displayMenu.tower == gameManager.towers[i]) {
                                 displayMenu.tower->isSelected = false;
                                 displayMenu.tower->selectedEnemy = nullptr;
                                 displayMenu.tower = nullptr;
                             }
                             else {
                                 if (displayMenu.tower != nullptr) {
                                     displayMenu.tower->isSelected = false;
                                     displayMenu.tower->selectedEnemy = nullptr;
                                     displayMenu.tower = nullptr;
                                 }
                                 
                              
                                 displayMenu.tower = gameManager.towers[i];
                                 displayMenu.tower->isSelected = true;

                                 if (gameManager.towers[i]->name == "basicTower") {
                                     displayMenu.selectedSprite.setTexture(textureManager.GetTexture("basicTower"));
                                     displayMenu.selectedSprite.setTextureRect(IntRect(0, 0, 40, 60));
                                 }
                                 else if (gameManager.towers[i]->name == "arrowTower") {
                                     displayMenu.selectedSprite.setTexture(textureManager.GetTexture("arrowTower"));
                                     displayMenu.selectedSprite.setTextureRect(IntRect(0, 0, 40, 58));
                                 }
                                 else if (gameManager.towers[i]->name == "magicTower") {
                                     displayMenu.selectedSprite.setTexture(textureManager.GetTexture("magicTower"));
                                     displayMenu.selectedSprite.setTextureRect(IntRect(0, 0, 40, 70));
                                 }
                                 else if (gameManager.towers[i]->name == "IceTowerSprites") {
                                     displayMenu.selectedSprite.setTexture(textureManager.GetTexture("IceTowerSprites"));
                                     displayMenu.selectedSprite.setTextureRect(IntRect(5, 23, 48, 75));
                                 }
                                 else if (gameManager.towers[i]->name == "wizardTower") {
                                     displayMenu.selectedSprite.setTexture(textureManager.GetTexture("WizardTower"));
                                     displayMenu.selectedSprite.setTextureRect(IntRect(0, 20, 40, 70));
                                 }
                                 else if (gameManager.towers[i]->name == "poisonTower") {
                                     displayMenu.selectedSprite.setTexture(textureManager.GetTexture("PoisonTowerSprites"));
                                     displayMenu.selectedSprite.setTextureRect(IntRect(0, 0, 50, 70));
                                 }
                                 else if (gameManager.towers[i]->name == "mortarTower") {
                                     displayMenu.selectedSprite.setTexture(textureManager.GetTexture("MortarTower"));
                                     displayMenu.selectedSprite.setTextureRect(IntRect(8, 0, 60, 75));
                                 }
                             }
                             
                         }
                     }

  
                     if (constructionMenu.basicTower.getGlobalBounds().contains(mousePos)) {
                         if (gameManager.checkCost(0)) {
                             if (displayMenu.tower != nullptr) {
                                 displayMenu.tower->isSelected = false;
                             }
                             displayMenu.tower = NULL;
                             gameManager.towers.push_back(std::shared_ptr<Tower>(new basicTower()));
                         }
                     }
                     else if (constructionMenu.magicTower.getGlobalBounds().contains(mousePos)) {
                         if (gameManager.checkCost(1)) {
                             if (displayMenu.tower != nullptr) {
                                 displayMenu.tower->isSelected = false;
                             }
                             displayMenu.tower = NULL;
                             gameManager.towers.push_back(std::shared_ptr<Tower>(new magicTower()));
                         }
                     }
                     else if (constructionMenu.arrowTower.getGlobalBounds().contains(mousePos)) {
                         if (gameManager.checkCost(2)) {
                             if (displayMenu.tower != nullptr) {
                                 displayMenu.tower->isSelected = false;
                             }
                             displayMenu.tower = NULL;
                             gameManager.towers.push_back(std::shared_ptr<Tower>(new arrowTower()));
                         }
                     }
                     else if (constructionMenu.iceTower.getGlobalBounds().contains(mousePos)) {
                         if (gameManager.checkCost(3)) {
                             if (displayMenu.tower != nullptr) {
                                 displayMenu.tower->isSelected = false;
                             }
                             displayMenu.tower = NULL;                           
                             gameManager.towers.push_back(std::shared_ptr<Tower>(new IceTower()));
                         }
                     }
                     else if (constructionMenu.poisonTower.getGlobalBounds().contains(mousePos)) {
                         if (gameManager.checkCost(4)) {
                             if (displayMenu.tower != nullptr) {
                                 displayMenu.tower->isSelected = false;
                             }
                             displayMenu.tower = NULL;
                             gameManager.towers.push_back(std::shared_ptr<Tower>(new poisonTower()));
                         }
                     }
                     else if (constructionMenu.wizardTower.getGlobalBounds().contains(mousePos)) {
                         if (gameManager.checkCost(5)) {
                             if (displayMenu.tower != nullptr) {
                                 displayMenu.tower->isSelected = false;
                             }
                             displayMenu.tower = NULL;
                             gameManager.towers.push_back(std::shared_ptr<Tower>(new wizardTower()));
                         }
                     }
                     else if (constructionMenu.mortarTower.getGlobalBounds().contains(mousePos)) {
                         if (gameManager.checkCost(6)) {
                             if (displayMenu.tower != nullptr) {
                                 displayMenu.tower->isSelected = false;
                             }
                             displayMenu.tower = NULL;
                             gameManager.towers.push_back(std::shared_ptr<Tower>(new MortarTower()));
                         }
                     }

                 }
             }
         }

  
         if (displayMenu.getHealth() <= 0) {
             gameManager.gameState = 3;
             return 3;
         }
         if (gameManager.gameState == 2) {
             return 3;
         }

         window.clear();
         mappy.UpdateMap(50, 30);
        
         gameManager.checkDeadEnemies();
        

         for (unsigned int i = 0; i < gameManager.towers.size(); i++)
             gameManager.towers[i]->Update();
         for (unsigned int i = 0; i < gameManager.Enemies.size(); i++)
             gameManager.Enemies[i]->Update(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));
            
         window.draw(cute);
         window.draw(wave);
         gameManager.Update(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));

         for (unsigned int i = 0; i < gameManager.towers.size(); i++) {
             for (unsigned int j = 0; j < gameManager.Enemies.size(); j++) {
                 if (gameManager.towers[i]->selectedEnemy != nullptr && gameManager.towers[i]->range.getGlobalBounds().intersects(gameManager.towers[i]->selectedEnemy->shape.getGlobalBounds())) {
                 }
                 else {
                     if (gameManager.towers[i]->range.getGlobalBounds().intersects(gameManager.Enemies[j]->shape.getGlobalBounds())) {
                         gameManager.towers[i]->Attack(gameManager.Enemies[j]->shape.getPosition() + (gameManager.Enemies[j]->shape.getSize() / 2.f),
                                                       gameManager.Enemies[j]->getDirection(), gameManager.Enemies[j]->getSpeed());
                         //displayDetails(gameManager.towers[i]);
                     }
                 }
             }
         }



         currentTime = clock.getElapsedTime();
         fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
         //std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
         gameManager.FPS = fps;
         previousTime = currentTime;

         constructionMenu.Update();
         constructionMenu.drawConstructionMenu();

         for (unsigned int i = 0; i < GameManager::getInstance()->bullets.size(); i++) {
             GameManager::getInstance()->bullets[i]->Update();
         }
         levelManager.Update();
         score.setString("SCORE: " + to_string(gameManager.getScore()));
         window.draw(score);

         window.display();

     }
     return 0;

}