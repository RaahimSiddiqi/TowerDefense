#include "ScoreState.h"


void swap(string* xp, string* yp)
{
    string temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// An optimized version of Bubble Sort
vector<string> bubbleSort(vector<string> arr)
{
    int n = arr.size();

    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (stoi(arr[j]) > stoi(arr[j + 1]))
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
    return arr;
}


int ScoreState::Run(RenderWindow& window, TextureManager& textureManager, GameManager& gameManager) {

    int currIndex = 0;
    int MAX_INDEX = 1;
    Cursor cursor;

    vector<Text> texts;

    vector<string> scores;
    scores.reserve(10);
    ifstream fin;
    fin.open("scores.txt");

    while (!fin.eof()) {
        string temp;
        fin >> temp;
        if (temp == '\n' || temp == "") continue;
        scores.push_back(temp);
    }
    fin.close();

    scores = bubbleSort(scores);
    cout << scores.size() << endl;

    int j = 0;
    for (unsigned int i = scores.size(); i > 0 && j < 10; i--, j++) {
        Text temp;
        temp.setFont(textureManager.GetFont("MachineGunk"));
        temp.setPosition(600, 140 + (j * 54));
        temp.setString(to_string(j + 1) + ". " + scores[i - 1]);

        if (j <= 3) {
            temp.setCharacterSize(38 + ((3 - j)*7));
            temp.setPosition(temp.getPosition() + Vector2f(-(3 - j) * 5, 0));
        }
        else {
            temp.setCharacterSize(38);
        }

        texts.push_back(temp);
    }

    Vector2f mousePos;
    scoreButtons[currIndex].OnFocused();

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
                    scoreButtons[currIndex].OffFocused();
                    if (currIndex == 0) {
                        currIndex = MAX_INDEX - 1;
                        scoreButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex -= 1;
                        scoreButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Down:
                    scoreButtons[currIndex].OffFocused();
                    if (currIndex == MAX_INDEX - 1) {
                        currIndex = 0;
                        scoreButtons[currIndex].OnFocused();
                    }
                    else {
                        currIndex += 1;
                        scoreButtons[currIndex].OnFocused();
                    }
                    break;
                case sf::Keyboard::Enter:
                    if (currIndex == 0) {
                        scoreButtons[0].OffFocused();
                        return 0;
                    }
                }
            }

            int flag = 0;
            for (unsigned int i = 0; i < scoreButtons.size(); i++) {

                if (scoreButtons[i].GlobalBounds().contains(mousePos)) {
                    if (i != currIndex) {
                        scoreButtons[currIndex].OffFocused();
                        scoreButtons[i].OnFocused();
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
                    if (scoreButtons[0].MenuClick(mousePos) == 1) {
                        scoreButtons[0].OffFocused();
                        return 0;
                    }
                }
            }

        }

        window.clear();
        for (unsigned int i = 0; i < scoreButtons.size(); i++) {
            scoreButtons[i].Update(window);
        }

        for (unsigned int i = 0; i < texts.size(); i++) {
            window.draw(texts[i]);
        }

        window.draw(title);
        window.draw(Banner);
        window.draw(Banner2);

        //window.draw(Banner);
        window.display();
    }
    return 2;
}