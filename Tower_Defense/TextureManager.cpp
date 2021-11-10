#include <SFML/Graphics.hpp>
#include <iostream>
#include "TextureManager.h"


TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager() {
	instance = this;
	LoadTexture("basicTower", "./Textures/basicTower.png");
	LoadTexture("magicTower", "./Textures/magicTower.png");
	LoadTexture("arrowTower", "./Textures/arrowTower.png");
	LoadTexture("arrowTowerL", "./Textures/arrowTowerL.png");
	LoadTexture("basicTowerL", "./Textures/basicTowerL.png");
	LoadTexture("magicTowerL", "./Textures/magicTowerL.png");
	LoadTexture("Castle", "./Textures/castle.png");
	LoadTexture("GrassBackground", "./Textures/grass.jpg");
	LoadTexture("spritesheet", "./Textures/spritesheetR.png");
	LoadTexture("spritesheet2", "./Textures/spritesheetR2.png");
	LoadTexture("spritesheet3", "./Textures/WraithSpritesheet.png");
	LoadTexture("spritesheet4", "./Textures/TrollSpritesheet.png");
	LoadTexture("spritesheet42", "./Textures/2DTrollSpritesheet.png");;
	LoadTexture("sideMenu", "./Textures/sideMenu.jpg");
	LoadTexture("CMenu", "./Textures/bottomMenu.png");
	LoadTexture("Spells", "./Textures/spells.png");
	LoadTexture("LightningAnimations", "./Textures/LightningSpritesheet.png");
	LoadTexture("IceBulletAnimations", "./Textures/IceSpritesheet.png");
	LoadTexture("PoisionBulletAnimations", "./Textures/PoisonSpritesheet.png");
	LoadTexture("IceTowerSprites", "./Textures/IceTowerSprites.png");
	LoadTexture("BasicTowerSprites", "./Textures/BasicTowerSprites.png");
	LoadTexture("ArrowTowerSprites", "./Textures/ArrowTowerSprites.png");
	LoadTexture("Arrow", "./Textures/arrow.png");
	LoadTexture("Explosion", "./Textures/ExplosionSprites.png");
	LoadTexture("Shot", "./Textures/shot.png");
	LoadTexture("magicExplosion", "./Textures/magicExplosionS.png");
	LoadTexture("MagicShot", "./Textures/MagicShot.png");
	LoadTexture("FireShot", "./Textures/FireShot.png");
	LoadTexture("MagicTowerSprites", "./Textures/MagicTowerSprites.png");
	LoadTexture("PoisonTowerSprites", "./Textures/PoisonTowerSprites.png");
	LoadTexture("WizardTower", "./Textures/WizardTower.png");
	LoadTexture("WindBlast", "./Textures/WindBlastAnimation.png");
	LoadTexture("MortarTower", "./Textures/MortarTowerSprites.png");
	LoadTexture("IceBolt", "./Textures/iceBolt.png");
	LoadTexture("CannonBall", "./Textures/cannonBall.png");
	LoadTexture("PoisonBottle", "./Textures/poisonBottle.png");
	LoadTexture("TowerCosts", "./Textures/TowerCosts.png");
	LoadTexture("TileTexture", "./Textures/TileTexture.png");
	LoadTexture("Map1", "./Textures/Map1.jpg");
	LoadTexture("Map2", "./Textures/Map2.jpg");
	LoadTexture("Map3", "./Textures/Map3.jpg");
	LoadTexture("Map4", "./Textures/Map4.jpg");
	LoadTexture("Map5", "./Textures/Map5.jpg");
	LoadTexture("Banner", "./Textures/Banner.png");
	LoadTexture("SelectionArrow", "./Textures/selectionArrow.png");
	LoadTexture("ToolTip", "./Textures/ToolTip.png");
	LoadTexture("BlueButton", "./Textures/BlueButton.png");
	LoadTexture("RedButton", "./Textures/RedButton.png");
	LoadTexture("WoodButton", "./Textures/WoodButton.png");
	LoadTexture("DisplayMenu", "./Textures/DisplayMenu.png");
	LoadTexture("WoodMenu", "./Textures/WoodMenu.png");
	LoadTexture("WoodRectangle", "./Textures/WoodRectangle.png");
	LoadTexture("topmenu", "./Textures/TopMenu.png");
	LoadTexture("title", "./Textures/WoodTitle.png");
	LoadTexture("hearts", "./Textures/HeartsSpriteSheet.png");
	LoadTexture("mouseHand", "./Textures/mouseHand.png");
	LoadTexture("mouseCursor", "./Textures/mouseCursor.png");
	LoadTexture("PurpleSwirl", "./Textures/PurpleSwirlSprites.png");
	LoadTexture("WhiteFlash", "./Textures/WhiteFlashSprites.png");
	LoadTexture("Trees", "./Textures/isometric_Trees.png");
	LoadTexture("HelpPage1", "./Textures/HelpPage1.png");
	LoadTexture("HelpPage2", "./Textures/HelpPage2.png");
	LoadTexture("HelpPage3", "./Textures/HelpPage3.png");
	LoadTexture("HelpPage4", "./Textures/HelpPage4.png");
	LoadTexture("rocks", "./Textures/rocks.png");
	LoadTexture("background", "./Textures/menu-background2.jpeg");

	LoadSound("explosion", "./Sounds/pixel-fireball.wav");
	LoadSound("Crossbow", "./Sounds/CrossbowTwang.wav");
	LoadSound("ButtonMouseClick", "./Sounds/ClassicMouseClick.wav");
	LoadSound("UpgradeTower", "./Sounds/MetalAnvil.wav");
	LoadSound("MouseClick", "./Sounds/simpleMouseClick.wav");
	LoadSound("LightImpact", "./Sounds/lightImpact.wav");
	LoadSound("TowerConstruct", "./Sounds/TowerConstruct.wav");
	LoadSound("WindBlast", "./Sounds/windBlast.wav");
	LoadSound("Freeze", "./Sounds/freezeSound.wav");
	LoadSound("MenuSelect", "./Sounds/menuChoice.wav");
	LoadSound("Victory", "./Sounds/VSound1.wav");
	LoadSound("GameOver", "./Sounds/gameoverdark.wav");

	LoadFont("Frostbite", "./Fonts/Frostbite.ttf");
	LoadFont("Vermin", "./Fonts/Vermin.ttf");
	LoadFont("Neuropol", "./Fonts/NRT.ttf");
	LoadFont("MachineGunk", "./Fonts/MachineGunk.ttf");
}

void TextureManager::LoadTexture(std::string name, std::string fileName) {
	Texture tex;

	if (tex.loadFromFile(fileName)) {
		this->_textures[name] = tex;
	}
	else {
		std::cout << fileName << " Texture not loaded" << std::endl;
	}
}


Texture &TextureManager::GetTexture(std::string name) {
		return this->_textures.at(name);
}

void TextureManager::LoadFont(std::string name, std::string fileName) {
	Font font;

	if (font.loadFromFile(fileName)) {
		this->_fonts[name] = font;
	}
	else {
		std::cout << fileName << " Font not loaded" << std::endl;
	}
}


Font &TextureManager::GetFont(std::string name) {
	return this->_fonts.at(name);
}


void TextureManager::LoadSound(std::string name, std::string fileName) {
	SoundBuffer buff;

	if (buff.loadFromFile(fileName)) {
		this->_soundBuffers[name] = buff;
	}
	else {
		std::cout << fileName << " Sound not loaded" << std::endl;
	}
}


SoundBuffer& TextureManager::GetSound(std::string name) {
	return this->_soundBuffers.at(name);
}


TextureManager* TextureManager::getInstance()
{
	return instance;
}

TextureManager::~TextureManager()
{
	if (instance == this)
	{
		instance = nullptr;
	}
}