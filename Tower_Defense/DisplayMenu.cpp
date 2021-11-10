#include "DisplayMenu.h"
#include "GameManager.h"
#include "TextureManager.h"
#include "button.h"
#include <sstream>
#include <iomanip>

DisplayMenu* DisplayMenu::instance = nullptr;

DisplayMenu::DisplayMenu(Vector2f origin) : Origin(origin) {
	
	DMenu.setSize(Vector2f(250, 700));

	DMenu.setPosition(Origin);
	DMenu.setFillColor(Color::White);
	DMenu.setOutlineColor(Color::Black);
	DMenu.setOutlineThickness(2);
	selectedSprite.setPosition(1020, 300);
	instance = this;

	sprite.setTexture(TextureManager::getInstance()->GetTexture("sideMenu"));
	sprite.setPosition(origin);
	selectedSprite.setScale(Vector2f(1.2, 1.2));

	HealthText.setFont(TextureManager::getInstance()->GetFont("Vermin"));
	HealthText.setPosition(Vector2f(origin.x + 15, origin.y + 90));
	//HealthText.setFillColor(Color::Black);
	HealthText.setString("Health: " + to_string(health) + "/" + to_string(maxHealth));
	HealthText.setCharacterSize(20);

	MoneyText.setFont(TextureManager::getInstance()->GetFont("Vermin"));
	MoneyText.setPosition(Vector2f(origin.x + 15, origin.y + 120));
	//MoneyText.setFillColor(Color::Black);
	MoneyText.setString("Money: " + to_string(money));
	MoneyText.setCharacterSize(20);

	FPSText.setFont(TextureManager::getInstance()->GetFont("Vermin"));
	FPSText.setPosition(Vector2f(origin.x + 15, origin.y + 150));
	//FPSText.setFillColor(Color::Black);
	FPSText.setString("FPS: " + to_string(GameManager::getInstance()->FPS));
	FPSText.setCharacterSize(18);

	TitleText.setFont(TextureManager::getInstance()->GetFont("Frostbite"));
	TitleText.setPosition(Vector2f(1020, 20));
	TitleText.setFillColor(Color::Red);
	TitleText.setString("Tower Defense");
	TitleText.setCharacterSize(36);


	NameText.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
	NameText.setPosition(Vector2f(1080, 300));
	NameText.setCharacterSize(16);
	//NameText.setFillColor(Color::Black);

	AttackText.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
	AttackText.setPosition(Vector2f(1080, 325));
	AttackText.setCharacterSize(16);
	//AttackText.setFillColor(Color::Black);

	RangeText.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
	RangeText.setPosition(Vector2f(1080, 350));
	RangeText.setCharacterSize(16);
	//RangeText.setFillColor(Color::Black);

	SpeedText.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
	SpeedText.setPosition(Vector2f(origin.x + 80, origin.y + 375));
	SpeedText.setCharacterSize(16);
	//SpeedText.setFillColor(Color::Black);

	ProjectileSpeedText.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
	ProjectileSpeedText.setPosition(Vector2f(origin.x + 80, origin.y + 400));
	ProjectileSpeedText.setCharacterSize(16);

	Title1.setFont(TextureManager::getInstance()->GetFont("Frostbite"));
	Title1.setString("Stats");
	Title1.setPosition(Vector2f(origin.x + 100, origin.y + 250));
	Title1.setCharacterSize(26);

	Title2.setFont(TextureManager::getInstance()->GetFont("Frostbite"));
	Title2.setString("Workshop");
	Title2.setPosition(Vector2f(origin.x + 70, origin.y + 490));
	Title2.setCharacterSize(26);

	value.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
	value.setPosition(Vector2f(origin.x + 40, origin.y + 540));
	value.setCharacterSize(20);

	UpgradeCost.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
	UpgradeCost.setPosition(Vector2f(origin.x + 40, origin.y + 570));
	UpgradeCost.setCharacterSize(20);

	Lvl.setFont(TextureManager::getInstance()->GetFont("Frostbite"));
	Lvl.setPosition(Vector2f(origin.x + 15, origin.y + 380));
	Lvl.setCharacterSize(30);

	//ProjectileSpeedText.setFillColor(Color::Black);

	Upgradebutton.setPosition(Vector2f(origin.x + 60, origin.y + 620));
	Upgradebutton.setSize(Vector2f(100, 40));
	Destroybutton.setPosition(Vector2f(origin.x + 60, origin.y + 670));
	Destroybutton.setSize(Vector2f(100, 40));

	Destroybutton.setColor(Color::Red);

	Upgradebutton.setID(1);
	Destroybutton.setID(2);

	Upgradebutton.ImageLoad("WoodButton");
	Destroybutton.ImageLoad("WoodButton");
	Upgradebutton.addTextOffset(Vector2f(7, 1));
	Destroybutton.addTextOffset(Vector2f(7, 1));
	Destroybutton.setHoverColor(Color::Red);
	Upgradebutton.setHoverColor(Color::Green);
	Upgradebutton.setTextHoverSize(1);
	Destroybutton.setTextHoverSize(1);

	Wood1.setTexture(TextureManager::getInstance()->GetTexture("WoodRectangle"));
	Wood2.setTexture(TextureManager::getInstance()->GetTexture("WoodRectangle"));
	Wood1.setPosition(Vector2f(origin.x + 15, origin.y + 485));
	Wood2.setPosition(Vector2f(origin.x + 15, origin.y + 245));

	Upgradebutton.setText("Upgrade", 20, Color::Black);
	Destroybutton.setText("Destroy", 20, Color::Black);
	GameManager::getInstance()->buttons.push_back(Upgradebutton);
	GameManager::getInstance()->buttons.push_back(Destroybutton);

	tower = nullptr;
}


void DisplayMenu::Update(Vector2f mousePos) {
	HealthText.setString("Health: " + to_string(health) + "/" + to_string(maxHealth));
	MoneyText.setString("Money: " + to_string(money));
	if (UpdateClock.getElapsedTime().asSeconds() > 1) {
		FPSText.setString("FPS: " + to_string(GameManager::getInstance()->FPS));
		UpdateClock.restart();
	}

	if (Upgradebutton.GlobalBounds().contains(mousePos)) {
		if (Upgradebutton.getFocus() == 0) {
			Upgradebutton.OnFocused();
		}
	}
	else {
		if (Upgradebutton.getFocus() == 1) {
			Upgradebutton.OffFocused();
		}	
	}

	if (Destroybutton.GlobalBounds().contains(mousePos)) {
		if (Destroybutton.getFocus() == 0) {
			Destroybutton.OnFocused();
		}
	}
	else {
		if (Destroybutton.getFocus() == 1) {
			Destroybutton.OffFocused();
		}
	}


	Draw();
}

void DisplayMenu::UpdateFPS() {

}

void DisplayMenu::Draw() {
	//GameManager::getInstance()->Window.draw(DMenu);
	GameManager::getInstance()->Window.draw(sprite);
	if (tower != nullptr) {
		GameManager::getInstance()->Window.draw(selectedSprite);

		stringstream ss;
		ss << std::fixed << std::setprecision(1);
		ss << tower->getAttack();

		AttackText.setString("Attack: " + ss.str());
		ss.str("");

		ss << tower->getSpeed();
		SpeedText.setString("Speed: " + ss.str());
		ss.str("");

		ss << tower->getRange();
		RangeText.setString("Range: " + ss.str());
		ss.str("");

		Lvl.setString("Lvl " + to_string(tower->getLevel()));
		if (tower->getLevel() == 3) {
			UpgradeCost.setString("Upgrade Cost: N/A");
		}
		else {
			UpgradeCost.setString("Upgrade Cost: " + to_string((tower->getLevel() + 1) * tower->getCost()));
		}
		
		value.setString("Current Value: " + to_string(tower->getValue()));

		ss << tower->getProjectileSpeed();
		ProjectileSpeedText.setString("Projectile Speed: " + ss.str());
		ss.str("");
		NameText.setString("Name: " + tower->displayName);
		GameManager::getInstance()->Window.draw(Wood1);
		GameManager::getInstance()->Window.draw(Wood2);
		GameManager::getInstance()->Window.draw(AttackText);
		GameManager::getInstance()->Window.draw(NameText);
		GameManager::getInstance()->Window.draw(SpeedText);
		GameManager::getInstance()->Window.draw(ProjectileSpeedText);
		GameManager::getInstance()->Window.draw(RangeText);
		GameManager::getInstance()->Window.draw(tower->range);
		GameManager::getInstance()->Window.draw(Title1);
		GameManager::getInstance()->Window.draw(Title2);
		GameManager::getInstance()->Window.draw(Lvl);
		GameManager::getInstance()->Window.draw(UpgradeCost);
		GameManager::getInstance()->Window.draw(value);
		Upgradebutton.Update(GameManager::getInstance()->Window);
		Destroybutton.Update(GameManager::getInstance()->Window);


	}
	GameManager::getInstance()->Window.draw(HealthText);
	GameManager::getInstance()->Window.draw(TitleText);
	GameManager::getInstance()->Window.draw(MoneyText);
	GameManager::getInstance()->Window.draw(FPSText);
}



DisplayMenu* DisplayMenu::getInstance()
{
	return instance;
}

DisplayMenu::~DisplayMenu()
{
	if (instance == this)
	{
		instance = nullptr;
	}
}

int DisplayMenu::getMoney() {
	return money;
}

void DisplayMenu::setMoney(int amount) {
	money = amount;
}

float DisplayMenu::getHealth() {
	return health;
}

int DisplayMenu::setHealth(int currHealth, int inc) {
	if (currHealth >= 0 && currHealth <= 100) {
		health = currHealth + inc;
		if (health >= 100) health = 100;
		if (health <= 0) health = 0;
		return 1;
	}
	else {
		cout << "Invalid Heath" << endl;
	}
	return 0;
}

void DisplayMenu::ExecuteEvents(int buttonID) {
	if (buttonID == 1) {
		GameManager::getInstance()->PlaySoundEffect("UpgradeTower");
		cout << "Upgrading tower " << tower->name << endl;
		tower->Upgrade();
	}
	else if (buttonID == 2) {
		tower->DestroyTower();
		tower = NULL;
	}
}

