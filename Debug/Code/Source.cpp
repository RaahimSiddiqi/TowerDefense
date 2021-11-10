#include "GameManager.h"
#include "DisplayMenu.h"
#include "LevelManager.h"
#include "States.h"
#include <windows.h>

using namespace sf;
using namespace std;


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{

    RenderWindow window(VideoMode(1250, 750), "Tower Defense", Style::Default);
    window.setFramerateLimit(60);
    TextureManager textureManager;
    GameManager gameManager(window);

    std::vector<State*> States;
    int state = 0;

    MenuState s0;
    States.push_back(&s0);
    MapSelectionState s1;
    States.push_back(&s1);
    GameState s2(window, textureManager);
    States.push_back(&s2);
    GameOverState s3;
    States.push_back(&s3);
    HelpState s4;
    States.push_back(&s4);
    SkillState s5;
    States.push_back(&s5);
    ScoreState s6;
    States.push_back(&s6);

    while (state >= 0)
    {
        state = States[state]->Run(window, textureManager, gameManager);
    }
}




    /*
    TextureManager textureManager;
    Map mappy = Map(window);

    ConstructionMenu constructionMenu = ConstructionMenu(window);
    LevelManager levelManager;
    GameManager gameManager(window);
    DisplayMenu displayMenu = DisplayMenu();

    float fps;
    sf::Clock clock = sf::Clock::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

   
    
    mappy.RenderMap(1000, 600, 50, 30, 1);
    Path path = Path(1000, 600, 6, 6, 2);
    

    while (window.isOpen())
    {
        Event event;
        

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == Keyboard::G) {
                    gameManager.toggleGridMode();
                }
                if (event.key.code == Keyboard::N) {
                    levelManager.NextLevel();
                }
                if (event.key.code == Keyboard::T) {
                    gameManager.toggleTileMode();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    Vector2f mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

                    for (int i = 0; i < gameManager.buttons.size(); i++) {
                        gameManager.buttons[i].isClicked(mousePos);
                    }

                    for (int i = 0; i < gameManager.basicTowers.size(); i++) {
                        if (gameManager.basicTowers[i].sprite.getGlobalBounds().contains(mousePos) && gameManager.basicTowers[i].builtFlag == 1) {
                            cout << "Selected Tower at " << gameManager.basicTowers[i].sprite.getGlobalBounds().top << " . " << gameManager.basicTowers[i].sprite.getGlobalBounds().left << endl;
                            //basicTowers[i].DestroyTower();
                           //displayMenu.towerInWorkshop = basicTowers[i].getClassObject();
                            displayMenu.tower = NULL;
                            displayMenu.tower = &gameManager.basicTowers[i];
                            displayMenu.selectedSprite.setTexture(textureManager.GetTexture("basicTower"));
                            displayMenu.selectedSprite.setTextureRect(IntRect(0, 0, 40, 60));
                        }
                    }

                    for (int i = 0; i < gameManager.arrowTowers.size(); i++) {
                        if (gameManager.arrowTowers[i].sprite.getGlobalBounds().contains(mousePos) && gameManager.arrowTowers[i].builtFlag == 1) {
                            cout << "Selected Tower at " << gameManager.arrowTowers[i].sprite.getGlobalBounds().top << " . " << gameManager.arrowTowers[i].sprite.getGlobalBounds().left << endl;
                            //basicTowers[i].DestroyTower();
                           //displayMenu.towerInWorkshop = arrowTowers[i].getClassObject();
                            displayMenu.tower = NULL;
                            displayMenu.tower = &gameManager.arrowTowers[i];
                            displayMenu.selectedSprite.setTexture(textureManager.GetTexture("arrowTower"));
                            displayMenu.selectedSprite.setTextureRect(IntRect(0, 0, 40, 58));
                        }
                    }

                    for (int i = 0; i < gameManager.magicTowers.size(); i++) {
                        if (gameManager.magicTowers[i].sprite.getGlobalBounds().contains(mousePos) && gameManager.magicTowers[i].builtFlag == 1) {
                            cout << "Selected Tower at " << gameManager.magicTowers[i].sprite.getGlobalBounds().top << " . " << gameManager.magicTowers[i].sprite.getGlobalBounds().left << endl;
                            //basicTowers[i].DestroyTower();
                            //displayMenu.towerInWorkshop = magicTowers[i].getClassObject();
                            displayMenu.tower = NULL;
                            displayMenu.tower = &gameManager.magicTowers[i];
                            displayMenu.selectedSprite.setTexture(textureManager.GetTexture("magicTower"));
                            displayMenu.selectedSprite.setTextureRect(IntRect(0, 0, 40, 70)); 
                        }
                    }

                    if (constructionMenu.basicTower.getGlobalBounds().contains(mousePos)) {
                        if (gameManager.checkCost(0)) {
                            displayMenu.tower = NULL;
                            basicTower basictower = basicTower();
                            gameManager.basicTowers.emplace_back(basictower);
                        }
                    }
                    else if (constructionMenu.magicTower.getGlobalBounds().contains(mousePos)) {
                        if (gameManager.checkCost(1)) {
                            displayMenu.tower = NULL;
                           magicTower magictower = magicTower();
                            gameManager.magicTowers.emplace_back(magictower);
                        }
                    }
                    else if (constructionMenu.arrowTower.getGlobalBounds().contains(mousePos)) {
                        if (gameManager.checkCost(2)) {
                            displayMenu.tower = NULL;
                           arrowTower arrowtower = arrowTower();
                            gameManager.arrowTowers.emplace_back(arrowtower);
                        }
                    }


                }

                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    cout << "genrate enemy " << endl;
                    Enemy enemy;
                    gameManager.Enemies.push_back(enemy);
                }
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2f mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
            //cout << "Mouse Position: " << Mouse::getPosition(window).x << " . " << Mouse::getPosition(window).y  << endl;
            //cout << "Mouse is at the htile: " << Mouse::getPosition(window).x / 20 << endl;
            //cout << "Mouse is at the vtile: " << Mouse::getPosition(window).y / 20 << endl;

            if (constructionMenu.basicTower.getGlobalBounds().contains(mousePos)) {
               // cout << "clicking basic tower" << endl;
               // Tower basicTower = Tower(window);
               // gameManager.basicTowers.push_back(basicTower);

           }
        }

        window.clear();
        mappy.UpdateMap(50, 30);
        //gameManager.UpdateSprites();


        for (int i = 0; i < gameManager.basicTowers.size(); i++)
            gameManager.basicTowers[i].Update();
        for (int i = 0; i < gameManager.magicTowers.size(); i++)
            gameManager.magicTowers[i].Update();
        for (int i = 0; i < gameManager.arrowTowers.size(); i++)
            gameManager.arrowTowers[i].Update();
        for (int i = 0; i < gameManager.Enemies.size(); i++)
            gameManager.Enemies[i].Update();
        gameManager.Update();

        for (int i = 0; i < gameManager.basicTowers.size(); i++) {
            for (int j = 0; j < gameManager.Enemies.size(); j++) {
                if (gameManager.basicTowers[i].range.getGlobalBounds().intersects(gameManager.Enemies[j].shape.getGlobalBounds())) {
                    gameManager.basicTowers[i].Attack(gameManager.Enemies[j].shape.getPosition() + Vector2f(10, 0));
                }
            }
        }

        for (int i = 0; i < gameManager.arrowTowers.size(); i++) {
            for (int j = 0; j < gameManager.Enemies.size(); j++) {
                if (gameManager.arrowTowers[i].range.getGlobalBounds().intersects(gameManager.Enemies[j].shape.getGlobalBounds())) {
                    gameManager.arrowTowers[i].Attack(gameManager.Enemies[j].shape.getPosition() + Vector2f(10, 0));
                }
            }
        }

        for (int i = 0; i < gameManager.magicTowers.size(); i++) {
            for (int j = 0; j < gameManager.Enemies.size(); j++) {
                if (gameManager.magicTowers[i].range.getGlobalBounds().intersects(gameManager.Enemies[j].shape.getGlobalBounds())) {
                    gameManager.magicTowers[i].Attack(gameManager.Enemies[j].shape.getPosition() + Vector2f(10, 0));
                }
            }
        }

        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds()); // the asSeconds returns a float
        //std::cout << "fps =" << floor(fps) << std::endl; // flooring it will make the frame rate a rounded number
        gameManager.FPS = fps;
        previousTime = currentTime;

        constructionMenu.drawConstructionMenu();
    

        for (int i = 0; i < GameManager::getInstance()->bullets.size(); i++) {
            GameManager::getInstance()->bullets[i].Update();
        }
        levelManager.Update();

        window.display();

    }
    return 0;
    */
//}