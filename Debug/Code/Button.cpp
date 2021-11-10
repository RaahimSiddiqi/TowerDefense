#include "button.h"
#include "GameManager.h"
#include "TextureManager.h"
#include "DisplayMenu.h"


Button::Button()
{
	rect.setSize(Vector2f(70, 30));
	rect.setFillColor(Color::Green);
	displayText.setFont(TextureManager::getInstance()->GetFont("Neuropol"));
	displayText.setFillColor(Color::Transparent);
	displayText.setCharacterSize(18);
	displayText.setString("Button");
	focus = 0;
}

Button::Button(Color ButtonColor, Color TextColor, Color HoverColor, Vector2f size, Vector2f Position, string font) {
	rect.setSize(size);
	rect.setFillColor(ButtonColor);
	this->HoverColor = HoverColor;
	displayText.setFont(TextureManager::getInstance()->GetFont(font));
	displayText.setFillColor(TextColor);
	displayText.setCharacterSize(18);
	displayText.setString("Button");
	setPosition(Position);
	focus = 0;
}

void Button::setSize(Vector2f size) {
	rect.setSize(size);
}

void Button::Update(RenderWindow& window) {
	//cout << displayText.getPosition().x << " . " << displayText.getPosition().y << endl;
	if (sprite.getTexture() == nullptr) {
		window.draw(rect);
	}
	else {
		window.draw(sprite);
	}
	window.draw(displayText);
}


void Button::setColor(Color color) {
	rect.setFillColor(color);
}

void Button::setPosition(Vector2f target) {
	position = target;
	rect.setPosition(position);

	//displayText.setOrigin(rect.getLocalBounds().width / 2.f, rect.getLocalBounds().height / 2.f);
	//displayText.setPosition(rect.getPosition().x + (rect.getGlobalBounds().width / 3.f + 5) - (displayText.getLocalBounds().width / 2.f ),
							//srect.getPosition().y + (rect.getGlobalBounds().height / 3.f + 5) - (displayText.getLocalBounds().height / 2.f));

	const sf::FloatRect bounds(displayText.getLocalBounds());
	const sf::Vector2f box(rect.getSize());
	displayText.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
	displayText.setPosition(position);

}

void Button::setText(string text) {
	displayText.setString(text);
}

void Button::setText(string text, int size) {
	displayText.setString(text);
	displayText.setCharacterSize(size);
}

void Button::setText(string text, int size, Color color) {
	TextColor = color;
	displayText.setString(text);
	displayText.setCharacterSize(size);
	displayText.setFillColor(color);
}

int Button::isClicked(Vector2f mousePos) {
	if (rect.getGlobalBounds().contains(mousePos)) {
		GameManager::getInstance()->PlaySoundEffect("ButtonMouseClick");
		return ID;
	}
	return -1;
}

int Button::MenuClick(Vector2f mousepos) {
	if (rect.getGlobalBounds().contains(mousepos)) {
		GameManager::getInstance()->PlaySoundEffect("ButtonMouseClick");
		return 1;
	}
	return -1;
}

void Button::setID(int id) {
	ID = id;
}

int Button::getID() {
	return ID;
}


void Button::OnFocused() {
	displayText.setFillColor(HoverColor);
	displayText.setCharacterSize(displayText.getCharacterSize() + textHoverSize);
	GameManager::getInstance()->PlaySoundEffect("MenuSelect");
	focus = 1;
}

void Button::OffFocused() {
	displayText.setFillColor(this->TextColor);
	displayText.setCharacterSize(displayText.getCharacterSize() - textHoverSize);
	focus = 0;
}

void Button::ImageLoad(string name) {
	sprite.setTexture(TextureManager::getInstance()->GetTexture(name));
	sprite.setPosition(rect.getPosition());
}

void Button::addTextOffset(Vector2f pos) {
	displayText.setPosition(displayText.getPosition() + pos);

}