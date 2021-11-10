#include "path.h"
#include <iostream>
#include "GameManager.h"
using namespace std;



Path::Path(int width, int height, int segments, int twists, int path) {
	/*
	if (path == 1) {
		Path1(width, height, segments, twists);
	}
	if (path == 2) {
		Path2(width, height, segments, twists);
	}
	if (path == 3) {
		//Path3(width, height, segments, twists);
	}
	*/
}


void Path::Forward(int length) {
	Color grey(100, 100, 100);

	if (currpoint.x > 1 && Map::getInstance()->tiles[currpoint.x - 1][currpoint.y].getID() != 1)
		Map::getInstance()->tiles[currpoint.x - 1][currpoint.y].setID(2);

	if (currpoint.x > 1 && Map::getInstance()->tiles[currpoint.x - 1][currpoint.y - 1].getID() != 1)
		Map::getInstance()->tiles[currpoint.x - 1][currpoint.y - 1].setID(2);

	if (currpoint.x > 1 && Map::getInstance()->tiles[currpoint.x - 1][currpoint.y + 1].getID() != 1)
		Map::getInstance()->tiles[currpoint.x - 1][currpoint.y + 1].setID(2);


	for (int i = 0; i < length; i++) {
		if (currpoint.x == 49) {
			endpoint = currpoint * (20.f, 20.f);
			endpoint -= Vector2f(100, 100);
			Map::getInstance()->castleLocation = endpoint;
			Map::getInstance()->CastleHP.hbar.setPosition(endpoint);
			return;
		}
		else if (currpoint.x >= 49) {
			return;
		}
		if (Map::getInstance()->tiles[currpoint.x][currpoint.y - 1].getID() != 1)
			Map::getInstance()->tiles[currpoint.x][currpoint.y - 1].setID(2);

		Map::getInstance()->tiles[currpoint.x][currpoint.y].setID(1);

		if (Map::getInstance()->tiles[currpoint.x][currpoint.y + 1].getID() != 1)
			Map::getInstance()->tiles[currpoint.x][currpoint.y + 1].setID(2);
		currpoint.x += 1;

	}
}


void Path::Back(int length) {
	Color grey(100, 100, 100);

	if (currpoint.x > 1 && Map::getInstance()->tiles[currpoint.x + 1][currpoint.y].getID() != 1)
		Map::getInstance()->tiles[currpoint.x + 1][currpoint.y].setID(2);

	if (currpoint.x > 1 && Map::getInstance()->tiles[currpoint.x + 1][currpoint.y + 1].getID() != 1)
		Map::getInstance()->tiles[currpoint.x + 1][currpoint.y + 1].setID(2);


	for (int i = 0; i < length; i++) {
		if (Map::getInstance()->tiles[currpoint.x][currpoint.y - 1].getID() != 1)
			Map::getInstance()->tiles[currpoint.x][currpoint.y - 1].setID(2);

		Map::getInstance()->tiles[currpoint.x][currpoint.y].setID(1);

		if (Map::getInstance()->tiles[currpoint.x][currpoint.y + 1].getID() != 1)
			Map::getInstance()->tiles[currpoint.x][currpoint.y + 1].setID(2);
		currpoint.x -= 1;

	}

	if (currpoint.y < 29 && Map::getInstance()->tiles[currpoint.x - 1][currpoint.y - 1].getID() != 1)
		Map::getInstance()->tiles[currpoint.x - 1][currpoint.y - 1].setID(2);

	if (currpoint.y < 29 && Map::getInstance()->tiles[currpoint.x - 1][currpoint.y + 1].getID() != 1)
		Map::getInstance()->tiles[currpoint.x - 1][currpoint.y + 1].setID(2);
}


void Path::Up(int length) {
	Color grey(100, 100, 100);

	if (currpoint.y < 29 && Map::getInstance()->tiles[currpoint.x][currpoint.y + 1].getID() != 1)
		Map::getInstance()->tiles[currpoint.x][currpoint.y + 1].setID(2);

	if (currpoint.y < 29 &&  Map::getInstance()->tiles[currpoint.x + 1][currpoint.y + 1].getID() != 1)
		Map::getInstance()->tiles[currpoint.x + 1][currpoint.y + 1].setID(2);


	for (int i = 0; i < length; i++) {
		if (Map::getInstance()->tiles[currpoint.x - 1][currpoint.y].getID() != 1)
			Map::getInstance()->tiles[currpoint.x - 1][currpoint.y].setID(2);

		Map::getInstance()->tiles[currpoint.x][currpoint.y].setID(1);

		if (Map::getInstance()->tiles[currpoint.x + 1][currpoint.y].getID() != 1)
			Map::getInstance()->tiles[currpoint.x + 1][currpoint.y].setID(2);
		currpoint.y -= 1;
	}

	if (currpoint.y < 29 && Map::getInstance()->tiles[currpoint.x + 1][currpoint.y - 1].getID() != 1)
		Map::getInstance()->tiles[currpoint.x + 1][currpoint.y - 1].setID(2);

}

void Path::Down(int length) {
	Color grey(100, 100, 100);

	if (currpoint.y > 0) {
		if (Map::getInstance()->tiles[currpoint.x][currpoint.y - 1].getID() != 1)
			Map::getInstance()->tiles[currpoint.x][currpoint.y - 1].setID(2);

		if (Map::getInstance()->tiles[currpoint.x + 1][currpoint.y - 1].getID() != 1)
			Map::getInstance()->tiles[currpoint.x + 1][currpoint.y - 1].setID(2);
	}

	for (int i = 0; i < length; i++) {
		if (currpoint.y == 30) {
			endpoint = currpoint * (20.f, 20.f);
			endpoint -= Vector2f(100, 80);
			Map::getInstance()->castleLocation = endpoint;
			Map::getInstance()->CastleHP.hbar.setPosition(endpoint);

			return;
		}
		if (Map::getInstance()->tiles[currpoint.x - 1][currpoint.y].getID() != 1)
			Map::getInstance()->tiles[currpoint.x - 1][currpoint.y].setID(2);

		Map::getInstance()->tiles[currpoint.x][currpoint.y].setID(1);

		if (Map::getInstance()->tiles[currpoint.x + 1][currpoint.y].getID() != 1)
			Map::getInstance()->tiles[currpoint.x + 1][currpoint.y].setID(2);
		currpoint.y += 1;
	}
}

void Path::PathCreator(int *array, int size) {
	for (int i = 0; i < size; i++) {
		if (array[i] == 0) {
			Forward(5);
		}
		else if (array[i] == 1) {
			Up(5);
		}
		else if (array[i] == 2) {
			Down(5);
		}
		else if (array[i] == 3) {
			Back(5);
		}
	}
	Map::getInstance()->RenderFoilage();
}


void Path::PathCreator(int* array, int size, int segment) {
	for (int i = 0; i < size; i++) {
		if (array[i] == 0) {
			Forward(segment);
		}
		else if (array[i] == 1) {
			Up(segment);
		}
		else if (array[i] == 2) {
			Down(segment);
		}
		else if (array[i] == 3) {
			Back(segment);
		}
	}
}


Path::Path(int mapNum) {
	Color grey(100, 100, 100);
	if (mapNum == 1) {
		this->startpoint = Vector2f(0, 15);
		currpoint = this->startpoint;
		Map::getInstance()->spawnPoint = currpoint;
		int array[18] = { 0, 0, 1, 1, 0, 0, 2, 2, 2, 2, 0, 0, 1, 1, 0, 0, 0 ,0};
		PathCreator(array, 18);
	}
	if (mapNum == 2) {
		this->startpoint = Vector2f(5, 0);
		currpoint = this->startpoint;
		Map::getInstance()->spawnPoint = currpoint;
		int array[40] = { 2, 2, 2, 2, 2, 2, 0, 0, 1, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 0, 0, 1, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0};
		PathCreator(array, 40, 4);
	}
	if (mapNum == 3) {
		this->startpoint = Vector2f(44, 0);
		currpoint = this->startpoint;
		Map::getInstance()->spawnPoint = currpoint;
		int array[27] = {2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		PathCreator(array, 27, 4);
	}
	if (mapNum == 4) {
		this->startpoint = Vector2f(20, 29);
		currpoint = this->startpoint;
		Map::getInstance()->spawnPoint = currpoint;
		int array[25] = { 1, 1, 3, 3, 3, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 2, 2, 2};
		PathCreator(array, 25);
	}
	if (mapNum == 5) {
		this->startpoint = Vector2f(0, 14);
		currpoint = this->startpoint;
		Map::getInstance()->spawnPoint = currpoint;
		int array[1] = { 0 };
		PathCreator(array, 1, 50);
	}
	if (mapNum == 99) {
		this->startpoint = Vector2f(0, 1);
		currpoint = this->startpoint;
		Map::getInstance()->spawnPoint = currpoint;
		int array[45] = { 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 2, 3, 3, 3, 3, 3, 3, 2, 2, 2, 0, 0, 0, 0, 0, 0};
		PathCreator(array, 45, 2);
	}
}

/*
void Path::Path1(int width, int height, int segments, int twists) {
	srand(time(NULL));
	//Color grey(0x00818589);
	int direction = 0;
	int turns = twists;

	std::vector<vector<Tile>> tiles = Map::getInstance()->tiles;

	Vector2f currpoint = Vector2f(0, (600 / 2) / 20);
	this->startpoint = currpoint;

	int offsety = 1;
	int offsetx = 0;
	int ydirection = 0;
	int nextmove = NULL;
	int flag = NULL;
	Color grey(100, 100, 100);

	while (currpoint.x < 49) {
		if (currpoint.x == 48) {
			endpoint = currpoint;
			Map::getInstance()->castleLocation = endpoint;
			cout << "endpoint is" << endpoint.x << endl;
		}
		//cout << "works" << endl;
		for (int i = 0; i < segments; i++) {
			//cout << "i:" << currpoint.x << " " << "j: " << currpoint.y << endl;
			if (Map::getInstance()->tiles[currpoint.x - offsetx][currpoint.y - offsety].tile.getFillColor() != Color::Red)
				Map::getInstance()->tiles[currpoint.x - offsetx][currpoint.y - offsety].tile.setFillColor(grey);
			//cout << "works" << endl;
			Map::getInstance()->tiles[currpoint.x ][currpoint.y].tile.setFillColor(Color::Red);
			//cout << "works" << endl;
			if (Map::getInstance()->tiles[currpoint.x + offsetx][currpoint.y + offsety].tile.getFillColor() != Color::Red)
				Map::getInstance()->tiles[currpoint.x + offsetx][currpoint.y + offsety].tile.setFillColor(grey);
		

			if (direction == 0) {
				if (currpoint.x < 49 and currpoint.x >= 0) 
					currpoint.x += 1;
			}
			else if (direction == 1) {
				nextmove = 1;
				if (ydirection == 0) {
					if (currpoint.y < 27 and currpoint.y > 2) // Stops it from going over the eidge
						currpoint.y += 1;  // Moves Down
				}
				else if (ydirection == 1) {
					if (currpoint.y < 27 and currpoint.y > 2) // Stops it from going over the edge
						currpoint.y -= 1;  // Moves Up
				}
			}
		}
		if (turns > 0 and nextmove == NULL) {
			direction = rand() % 2;
			if (direction == 0) { // Point forward
				//cout << "Moving Forward  " << endl;
				offsety = 1;
				offsetx = 0;
			} 
			else {   // Point down

				offsetx = 1;
				offsety = 0;
			}
			ydirection = rand() % 2;
			if (ydirection == 0) {
				//cout << "Pointing Up  " << endl;
				Map::getInstance()->tiles[currpoint.x][currpoint.y - 1].tile.setFillColor(grey);
			}
			else {
				//cout << "Pointing Down  " << endl;
				Map::getInstance()->tiles[currpoint.x][currpoint.y + 1].tile.setFillColor(grey);
			}
			turns -= 1;
			//cout << "TURN!" << endl;
		}
		else if (turns > 0 and nextmove == NULL) {
			direction = 0;
			offsety = 1;
			offsetx = 0;
		}
		if (nextmove == 1) { // It moves either up or down, then it defaults the next move to move forward (to avoid errors in pathbuilding)
			if (ydirection == 0 or ydirection == 1) { 
				int nextmovedirection = rand() % 2;
				if (nextmovedirection == 0) {
					direction = 0;
					offsety = 1;
					offsetx = 0;
				}
			}
			nextmove = NULL;

		}
	
	}

	//cout << id;

}


void Path::Path2(int width, int height, int segments, int twists) {
	srand(time(NULL));
	Color grey(100, 100, 100);
	int direction = 0;
	int turns = twists;

	std::vector<vector<Tile>> tiles = Map::getInstance()->tiles;

	Vector2f currpoint = Vector2f(0, (600 / 2) / 20);
	this->startpoint = currpoint;

	int offsety = 1;
	int offsetx = 0;
	int ydirection = 0;
	int nextmove = NULL;
	int flag = NULL;

	while (currpoint.x < 49) {
		if (currpoint.x == 48) {
			endpoint = currpoint * (20.f, 20.f);
			endpoint -= Vector2f(100, 100);
			cout << "endpoint is" << endpoint.x << endl;
			Map::getInstance()->castleLocation = endpoint;
		}
		//cout << "works" << endl;
		for (int i = 0; i < segments; i++) {
			//cout << "i:" << currpoint.x << " " << "j: " << currpoint.y << endl;
			if (Map::getInstance()->tiles[currpoint.x - offsetx][currpoint.y - offsety].tile.getFillColor() != Color::Red)
				Map::getInstance()->tiles[currpoint.x - offsetx][currpoint.y - offsety].tile.setFillColor(grey);
			//cout << "works" << endl;
			Map::getInstance()->tiles[currpoint.x][currpoint.y].tile.setFillColor(Color::Red);
			//cout << "works" << endl;
			if (Map::getInstance()->tiles[currpoint.x + offsetx][currpoint.y + offsety].tile.getFillColor() != Color::Red)
				Map::getInstance()->tiles[currpoint.x + offsetx][currpoint.y + offsety].tile.setFillColor(grey);


			if (direction == 0) {
				if (currpoint.x < 49 and currpoint.x >= 0)
					currpoint.x += 1;
			}
			else if (direction == 1) {
				nextmove = 1;
				if (ydirection == 0) {
					if (currpoint.y < 27 and currpoint.y > 2) // Stops it from going over the eidge
						currpoint.y += 1;  // Moves Down
				}
				else if (ydirection == 1) {
					if (currpoint.y < 27 and currpoint.y > 2) // Stops it from going over the edge
						currpoint.y -= 1;  // Moves Up
				}
			}
		}
		if (turns > 0 and nextmove == NULL) {
			direction = rand() % 2;
			if (direction == 0) { // Point forward
				//cout << "Moving Forward  " << endl;
				offsety = 1;
				offsetx = 0;
			}
			else {   // Point down

				offsetx = 1;
				offsety = 0;
			}
			ydirection = rand() % 2;
			if (ydirection == 0) {
				//cout << "Pointing Up  " << endl;
				Map::getInstance()->tiles[currpoint.x][currpoint.y - 1].tile.setFillColor(grey);
			}
			else {
				//cout << "Pointing Down  " << endl;
				Map::getInstance()->tiles[currpoint.x][currpoint.y + 1].tile.setFillColor(grey);
			}
			turns -= 1;
			//cout << "TURN!" << endl;
		}
		else if (turns > 0 and nextmove == NULL) {
			direction = 0;
			offsety = 1;
			offsetx = 0;
		}
		if (nextmove == 1) { // It moves either up or down, then it defaults the next move to move forward (to avoid errors in pathbuilding)
			if (ydirection == 0 or ydirection == 1) {
					direction = 0;
					offsety = 1;
					offsetx = 0;
			}
			nextmove = NULL;
		}

		if (currpoint.x == 48) {
			endpoint = currpoint;
			Map::getInstance()->castleLocation = endpoint;
		}
	}

	//cout << id;

}*/