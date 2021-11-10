#include "MapSelectionState.h"
#include <iostream>
#include "Button.h"


int MapSelectionState::Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager) {

    int currIndex = 0;
    int MAX_INDEX = 6;
    Cursor cursor;
    //Background.setTextureRect(IntRect(30, 30, 1250, 700));
   // play.setID(3);
    //exit.setID(4);

    Vector2f mousePos;
    mapPreivew.setPosition(500, 200);
    mapButtons[currIndex].OnFocused();

    while (window.isOpen())
    {
        Event event;

        mousePos = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    mapButtons[currIndex].OffFocused();
                    if (currIndex == 0) {
                        currIndex = MAX_INDEX - 1;
                        mapButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex -= 1;
                        mapButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Down:
                    mapButtons[currIndex].OffFocused();
                    if (currIndex == MAX_INDEX - 1) {
                        currIndex = 0;
                        mapButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex += 1;
                        mapButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Enter:
                    if (currIndex >= 0 && currIndex < 5) {
                        gameManager.setMap(currIndex + 1);
                        gameManager.resetScore();
                        mapButtons[currIndex].OffFocused();
                        return 2;
                    }
                    else if (currIndex == 5) {
                        mapButtons[currIndex].OffFocused();
                        return 0;
                    }
                    break;
                }
            }

            int flag = 0;
            for (unsigned int i = 0; i < mapButtons.size(); i++) {

                if (mapButtons[i].GlobalBounds().contains(mousePos)) {
                    if (i != currIndex) {
                        mapButtons[currIndex].OffFocused();
                        mapButtons[i].OnFocused();
                        currIndex = i;
                    }
                    flag = 1;
                }
            }

            if (flag == 1) {
                if (cursor.loadFromSystem(sf::Cursor::Hand))
                    window.setMouseCursor(cursor);
            }
            else {
                if (cursor.loadFromSystem(sf::Cursor::Arrow))
                    window.setMouseCursor(cursor);
            }


            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (cursor.loadFromSystem(sf::Cursor::Arrow))
                        window.setMouseCursor(cursor);

                    for (unsigned int i = 0; i < mapButtons.size() - 1; i++) {
                        if (mapButtons[i].isClicked(mousePos) != -1) {
                            gameManager.setMap(i + 1);
                            gameManager.resetScore();
                            mapButtons[currIndex].OffFocused();
                            return 2;
                        }
                    }
                    if (mapButtons[mapButtons.size() - 1].isClicked(mousePos) != -1) {
                        mapButtons[currIndex].OffFocused();
                        return 0;
                    }
                }
            }

        }

        window.clear();
        //window.draw(Background);

        if (currIndex != MAX_INDEX - 1) {
            mapPreivew.setTexture(maps[currIndex]);
            window.draw(mapPreivew);
        }

        for (unsigned int i = 0; i < mapButtons.size(); i++) {
            mapButtons[i].Update(window);
        }
 
      
        window.display();
    }
    return -1;
}