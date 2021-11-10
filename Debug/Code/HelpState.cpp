#include "HelpState.h"


int HelpState::Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager) {
    int currIndex = 0;
    int MAX_INDEX = 3;

    int pageIndex = 0;
    Background.setTexture(pages[0]);
    helpButtons[currIndex].OnFocused();


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
                    helpButtons[currIndex].OffFocused();
                    if (currIndex == 0) {
                        currIndex = MAX_INDEX - 1;
                        helpButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex -= 1;
                        helpButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Down:
                    helpButtons[currIndex].OffFocused();
                    if (currIndex == MAX_INDEX - 1) {
                        currIndex = 0;
                        helpButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex += 1;
                        helpButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Enter:
                    if (currIndex == 0) {
                        if (pageIndex < 3) pageIndex += 1;
                        Background.setTexture(pages[pageIndex]);
                    }
                    if (currIndex == 1) {
                        if (pageIndex > 0) pageIndex -= 1;
                        Background.setTexture(pages[pageIndex]);
                    }
                    if (currIndex == 2) {
                        return 0;
                    }
                }
            }
            int flag = 0;
            for (unsigned int i = 0; i < helpButtons.size(); i++) {

                if (helpButtons[i].GlobalBounds().contains(mousePos)) {
                    if (i != currIndex) {
                        helpButtons[currIndex].OffFocused();
                        helpButtons[i].OnFocused();
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
                    if (helpButtons[0].MenuClick(mousePos) == 1) {
                        if (pageIndex < 3) pageIndex += 1;
                        Background.setTexture(pages[pageIndex]);
                    }
                    if (helpButtons[1].MenuClick(mousePos) == 1) {
                        if (pageIndex > 0) pageIndex -= 1;
                        Background.setTexture(pages[pageIndex]);
                    }
                    if (helpButtons[2].MenuClick(mousePos) == 1) {
                        return 0;
                    }
                }
            }

        }
        window.clear();
        //window.draw(Background);
        window.draw(Background);
        for (unsigned int i = 0; i < helpButtons.size(); i++) {
            helpButtons[i].Update(window);
        }

        


        window.display();

    }
	return 0;
}