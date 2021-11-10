#include "SkillState.h"



int SkillState::Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager) {

    int currIndex = 0;
    int MAX_INDEX = 3;
    Cursor cursor;


    Vector2f mousePos;
    skillButtons[currIndex].OnFocused();

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
            }
               
            int flag = 0;
            for (unsigned int i = 0; i < skillButtons.size(); i++) {

                if (skillButtons[i].GlobalBounds().contains(mousePos)) {
                    if (i != currIndex) {
                        skillButtons[currIndex].OffFocused();
                        skillButtons[i].OnFocused();
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
                    if (skillButtons[0].MenuClick(mousePos) == 1) {
                        return 1;
                    }
                    if (skillButtons[1].MenuClick(mousePos) == 1) {
                        return 4;
                    }
                    if (skillButtons[2].MenuClick(mousePos) == 1) {
                        return -1;
                    }
                }
            }

        }

        window.clear();
        for (unsigned int i = 0; i < skillButtons.size(); i++) {
            skillButtons[i].Update(window);
        }


        //window.draw(Banner);
        window.display();
    }
    return 2;
}