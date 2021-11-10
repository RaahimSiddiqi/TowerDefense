#include "GameOverState.h"
#include "button.h"
#include <ctime>


int GameOverState::Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager) {


	int currIndex = 0;
	int MAX_INDEX = 2;
    Score.setString("SCORE: " + to_string(gameManager.getScore()));

    time_t now = time(NULL);
    char str[26] = {};
    ctime_s(str, 26, &now);

    string s(str);
    s.erase(std::remove(s.begin(), s.end(), '\n'),
        s.end());

    ofstream out;
    out.open("scores.txt", ios::app);
    out << gameManager.getScore() << endl;
    out.close();


    if (gameManager.gameState == 2) {
        display.setString("YOU ARE VICTORIOUS!");
        gameManager.PlaySoundEffect("Victory", 15);
    }
    else {
        display.setString("YOU HAVE BEEN DEFEATED");
        gameManager.PlaySoundEffect("GameOver", 10);
    }

    gameManager.clear();

	Vector2f mousePos;
    gameOverButtons[currIndex].OnFocused();

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
                    gameOverButtons[currIndex].OffFocused();
                    if (currIndex == 0) {
                        currIndex = MAX_INDEX - 1;
                        gameOverButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex -= 1;
                        gameOverButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Down:
                    gameOverButtons[currIndex].OffFocused();
                    if (currIndex == MAX_INDEX - 1) {
                        currIndex = 0;
                        gameOverButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex += 1;
                        gameOverButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Enter:
                    //if (currIndex == 0) {
                   //     return 1;
                    //}
                    if (currIndex == 0) {
                        return -1;
                    }
                    if (currIndex == 1) {
                        return 0;
                    }
                }
            }

            for (unsigned int i = 0; i < gameOverButtons.size(); i++) {
                if (gameOverButtons[i].GlobalBounds().contains(mousePos)) {
                    if (i != currIndex) {
                        gameOverButtons[currIndex].OffFocused();
                        gameOverButtons[i].OnFocused();
                        currIndex = i;
                    }

                }
            }

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//if (gameOverButtons[0].MenuClick(mousePos) == 1) {
					//	return 1;
					//}
					if (gameOverButtons[0].MenuClick(mousePos) == 1) {
						return -1;
					}
					if (gameOverButtons[1].MenuClick(mousePos) == 1) {
						return 0;
					}
				}
			}		
		}

		window.clear();
        window.draw(display);
        window.draw(Score);
		for (unsigned int i = 0; i < gameOverButtons.size(); i++) {
			gameOverButtons[i].Update(window);
		}

		window.display();
	}

    return -1;
}