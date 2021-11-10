#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <map>

using namespace sf;

class TextureManager {
public:
	TextureManager();
	~TextureManager();
	static TextureManager* getInstance();

	void LoadTexture(std::string name, std::string fileName);
	Texture& GetTexture(std::string name);

	void LoadFont(std::string name, std::string fileName);
	Font& GetFont(std::string name);

	void LoadSound(std::string name, std::string fileName);
	SoundBuffer& GetSound(std::string name);

private:
	std::map<std::string, Texture> _textures;
	std::map<std::string, Font> _fonts;
	std::map<std::string, SoundBuffer> _soundBuffers;
	static TextureManager* instance;
};