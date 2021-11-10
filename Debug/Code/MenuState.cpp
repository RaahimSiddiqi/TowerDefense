#include "MenuState.h"
#include "Particle.h"

void MenuState::Execute() {

}

int MenuState::Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager){

    int currIndex = 0;
    int MAX_INDEX = 3;
    Cursor cursor;


    vector<Particle> particles;
    vector<Particle> particles2;

    Particle::setNum(0);

    Text title;
    title.setFont(textureManager.GetFont("Frostbite"));
    title.setCharacterSize(66);
    title.setPosition(440, 40);
    title.setString("Tower Defense");
    title.setFillColor(Color::Black);

    Text subtitle;
    subtitle.setFont(textureManager.GetFont("Frostbite"));
    subtitle.setCharacterSize(44);
    subtitle.setPosition(480, 110);
    subtitle.setString("Arcana Battles");
    subtitle.setFillColor(Color::Black);

    Vector2f mousePos;
    menuButtons[currIndex].OnFocused();

    //Background.setTextureRect(IntRect(30, 30, 1250, 700));
    srand(time(0));

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
                    menuButtons[currIndex].OffFocused();
                    if (currIndex == 0) {
                        currIndex = MAX_INDEX - 1;
                        menuButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex -= 1;
                        menuButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Down:
                    menuButtons[currIndex].OffFocused();
                    if (currIndex == MAX_INDEX - 1) {
                        currIndex = 0;
                        menuButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex += 1;
                        menuButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Enter:
                    if (currIndex == 0) {
                        menuButtons[0].OffFocused();
                        return 1;
                    }
                    if (currIndex == 1) {
                        menuButtons[1].OffFocused();
                        return 4;
                    }
                    if (currIndex == 2) {
                        menuButtons[2].OffFocused();
                        return 6;
                    }
                    if (currIndex == 3) {
                        menuButtons[3].OffFocused();
                        return -1;
                    }
                }
            }
            int flag = 0;
            for (unsigned int i = 0; i < menuButtons.size(); i++) {
                
                if (menuButtons[i].GlobalBounds().contains(mousePos)) {
                    if (i != currIndex) {
                        menuButtons[currIndex].OffFocused();
                        menuButtons[i].OnFocused();
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
                    if (menuButtons[0].MenuClick(mousePos) == 1) {
                        menuButtons[0].OffFocused();
                        return 1;
                    }
                    if (menuButtons[1].MenuClick(mousePos) == 1) {
                        menuButtons[1].OffFocused();
                        return 4;
                    }
                    if (menuButtons[2].MenuClick(mousePos) == 1) {
                        menuButtons[2].OffFocused();
                        return 6;
                    }
                    if (menuButtons[3].MenuClick(mousePos) == 1) {
                        menuButtons[3].OffFocused();
                        return -1;
                    }
                }
            }

        }
 
        window.clear();
        window.draw(Background);
        for (unsigned int i = 0; i < menuButtons.size(); i++) {
            menuButtons[i].Update(window);
        }

        
        if (Particle::getNum() < 400) {

            particles.push_back(Particle(gameManager.Window, 15, Vector2f(350 - rand()% 30 + (15), 150 - rand() % 10), Color(240, 20, 20)));
            particles.push_back(Particle(gameManager.Window, 15, Vector2f(350 - rand() % 30 + (15), 150 - rand() % 10), Color(240, 20, 20)));
        }
        //cout << Particle::getNum() << endl;
        //cout << particles[0].getNum() << endl;
        vector<Particle>::iterator i;
        for (i = particles.begin(); i != particles.end();) {
            if (i->getAlpha() <= 0 || i->getColor() >= 255) {
                i = particles.erase(i);
                Particle::decNum();
            }
            else
            {
                i->update();
                //i->draw();
                ++i;
            }
        }


        if (Particle::getNum() < 450) {

            particles2.push_back(Particle(gameManager.Window, 15, Vector2f(950 - rand() % 30 + (20), 150 - rand() % 10), Color(240, 20, 20)));
            particles2.push_back(Particle(gameManager.Window, 15, Vector2f(950 - rand() % 30 + (20), 150 - rand() % 10), Color(240, 20, 20)));
        }

        for (i = particles2.begin(); i != particles2.end();) {
            if (i->getAlpha() <= 0 || i->getColor() >= 255) {
                i = particles2.erase(i);
                Particle::decNum();
            }
            else
            {
                i->update();
                //i->draw();
                ++i;
            }
        }


        window.draw(title);
        window.draw(subtitle);
        
       // window.draw(Banner);
       
        window.display();
    }
    return -1;
}