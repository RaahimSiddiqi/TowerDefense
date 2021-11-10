#include <SFML/Graphics.hpp>
#include <iostream>
#include "ConstructionMenu.h"
#include "TextureManager.h"

using namespace std;

ConstructionMenu::ConstructionMenu(RenderWindow& window, Vector2f origin) : Window(window), Origin(origin)
{

	Cmenu.setFillColor(Color::White);
	Cmenu.setSize(Vector2f(1000, 100));
	Cmenu.setPosition(origin);
	Cmenu.setOutlineColor(Color::Black);
	Cmenu.setOutlineThickness(2);

	mainSprite.setTexture(TextureManager::getInstance()->GetTexture("CMenu"));
	mainSprite.setPosition(origin);

	basicTowerTexture = TextureManager::getInstance()->GetTexture("basicTowerL");
	magicTowerTexture = TextureManager::getInstance()->GetTexture("magicTowerL");
	arrowTowerTexture = TextureManager::getInstance()->GetTexture("arrowTowerL");
	iceTowerTexture = TextureManager::getInstance()->GetTexture("IceTowerSprites");
	poisonTowerTexture = TextureManager::getInstance()->GetTexture("PoisonTowerSprites");
	wizardTowerTexture = TextureManager::getInstance()->GetTexture("WizardTower");
	mortarTowerTexture = TextureManager::getInstance()->GetTexture("MortarTower");

	IceSpell.setTexture(TextureManager::getInstance()->GetTexture("Spells"));
	HealthRecoverSpell.setTexture(TextureManager::getInstance()->GetTexture("Spells"));
	LightningSpell.setTexture(TextureManager::getInstance()->GetTexture("Spells"));

	IntRect spriteRect1 = IntRect(266.6, 266.6, 133.33, 133.33);
	IceSpell.setTextureRect(spriteRect1);
	IntRect spriteRect2 = IntRect(133.33, 133.33, 133.33, 133.33);
	LightningSpell.setTextureRect(spriteRect2);
	IntRect spriteRect3 = IntRect(266.66, 133.33, 133.33, 133.33);
	HealthRecoverSpell.setTextureRect(spriteRect3);



	IceSpell.setScale(0.66, 0.66);
	LightningSpell.setScale(0.66, 0.66);
	HealthRecoverSpell.setScale(0.66, 0.66);

	basicTower.setTexture(basicTowerTexture);
	magicTower.setTexture(magicTowerTexture);
	arrowTower.setTexture(arrowTowerTexture);
	iceTower.setTexture(iceTowerTexture);
	wizardTower.setTexture(wizardTowerTexture);
	mortarTower.setTexture(mortarTowerTexture);
	poisonTower.setTexture(poisonTowerTexture);

	IntRect rect = IntRect(0, 20, 53, 80);
	iceTower.setTextureRect(rect);
	poisonTower.setTextureRect(IntRect(0, 5, 51, 70));
	poisonTower.scale(1.2, 1.2);
	wizardTower.setTextureRect(IntRect(0, 20, 40, 90));
	wizardTower.scale(1.2, 1.2);
	mortarTower.setTextureRect(IntRect(0, 5, 68, 75));


	 
	Cost1.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost1.setTextureRect(IntRect(0, 0, 90, 29));
	
	Cost2.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost2.setTextureRect(IntRect(360, 0, 90, 29));
	 
	Cost3.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost3.setTextureRect(IntRect(90, 0, 90, 29));

	Cost4.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost4.setTextureRect(IntRect(180, 0, 90, 29));

	Cost5.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost5.setTextureRect(IntRect(270, 0, 90, 29));

	Cost6.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost6.setTextureRect(IntRect(270, 0, 90, 29));

	Cost7.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost7.setTextureRect(IntRect(270, 0, 90, 29));

	Cost9.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost9.setTextureRect(IntRect(270, 0, 90, 29));

	Cost10.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost10.setTextureRect(IntRect(270, 0, 90, 29));

	Cost11.setTexture(TextureManager::getInstance()->GetTexture("TowerCosts"));
	Cost11.setTextureRect(IntRect(270, 0, 90, 29));
	

	//T8 = TextureManager::getInstance()->GetTexture("TowerCosts");
	//Cost8.setTexture(T8);
	//Cost8.setTextureRect(IntRect(270, 0, 90, 29));

	//Window.draw(basicTower);
	spell1.startCount();
	spell2.startCount();
	spell3.startCount();

	updatePosition();
}

void ConstructionMenu::Update() {

	spell1.Update();
	spell2.Update();
	spell3.Update();

	if (!spell1.Ready()) {
		LightningSpell.setColor(Color(255, 255, 255, 160));
	}
	else {
		LightningSpell.setColor(Color(255, 255, 255, 255));
	}

	if (!spell2.Ready()) {
		IceSpell.setColor(Color(255, 255, 255, 160));
	}
	else {
		IceSpell.setColor(Color(255, 255, 255, 255));
	}

	if (!spell3.Ready()) {
		HealthRecoverSpell.setColor(Color(255, 255, 255, 160));
	}
	else {
		HealthRecoverSpell.setColor(Color(255, 255, 255, 255));
	}


	/*
	if (LightningSpell.getGlobalBounds().contains(pos)) {

	}

	if (IceSpell.getGlobalBounds().contains(pos)) {

	}

	if (HealthRecoverSpell.getGlobalBounds().contains(pos)) {

	}*/

}

void ConstructionMenu::drawConstructionMenu() {
	//Window.draw(this->Cmenu);
	Window.draw(this->mainSprite);

	Window.draw(arrowTower);
	Window.draw(magicTower);
	Window.draw(basicTower);
	Window.draw(iceTower);
	Window.draw(poisonTower);
	Window.draw(wizardTower);
	Window.draw(mortarTower);

	Window.draw(IceSpell);
	Window.draw(LightningSpell);
	Window.draw(HealthRecoverSpell);

	Window.draw(Cost1);
	Window.draw(Cost2);
	Window.draw(Cost3);
	Window.draw(Cost4);
	Window.draw(Cost5);
	Window.draw(Cost6);
	Window.draw(Cost7);
	Window.draw(Cost8);
	//Window.draw(Cost9);
	//Window.draw(Cost10);
	//Window.draw(Cost11);

	spell1.Draw(Window);
	spell2.Draw(Window);
	spell3.Draw(Window);

}

void ConstructionMenu::updatePosition() {
	Vector2f origin = Origin;

	IceSpell.setPosition(Vector2f(825, origin.y + 12));
	LightningSpell.setPosition(Vector2f(732, origin.y + 10));
	HealthRecoverSpell.setPosition(Vector2f(915, origin.y + 12));

	basicTower.setPosition(Origin.x + 20 + (0 * Cmenu.getSize().x / 10.5), origin.y + 10);
	mortarTower.setPosition(Origin.x + 20 + (1 * Cmenu.getSize().x / 10.5), origin.y + 10);
	magicTower.setPosition(Origin.x + 20 + (2 * Cmenu.getSize().x / 10.5), origin.y + 10);
	arrowTower.setPosition(Origin.x + 20 + (3 * Cmenu.getSize().x / 10.5), origin.y + 10);
	iceTower.setPosition(Origin.x + 20 + (4 * Cmenu.getSize().x / 10.5), origin.y + 10);
	wizardTower.setPosition(Origin.x + 20 + (5 * Cmenu.getSize().x / 10.5), origin.y + 10);
	poisonTower.setPosition(Origin.x + 20 + (6 * Cmenu.getSize().x / 10.5), origin.y + 10);


	Cost1.setPosition(10, origin.y + 74);
	Cost2.setPosition(105, origin.y + 74);
	Cost3.setPosition(200, origin.y + 74);
	Cost4.setPosition(295, origin.y + 74);
	Cost5.setPosition(390, origin.y + 74);
	Cost6.setPosition(485, origin.y + 74);
	Cost7.setPosition(580, origin.y + 74);
	//Cost9.setPosition(725, origin.y + 80);
	//Cost10.setPosition(815, origin.y + 80);
	//Cost11.setPosition(905, origin.y + 80);

}
