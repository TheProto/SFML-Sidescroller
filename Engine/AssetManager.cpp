#include <SFML\Graphics.hpp>
#include "AssetManager.h"

namespace ProtoEngine
{	
	AssetManager::AssetManager() {
	}

	AssetManager::~AssetManager() {
	}

	void AssetManager::LoadTexture(std::string name, std::string fileName) {
		sf::Texture tex;

		if (tex.loadFromFile(fileName)) {
			this->_textures[name] = tex;
		}
	}

	sf::Texture &AssetManager::GetTexture(std::string name) {
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(std::string name, std::string fileName) {
		sf::Font font;

		if (font.loadFromFile(fileName)) {
			//this->_fonts[name] = font;
			this->_fonts.insert(std::pair<std::string, sf::Font>(name, font));
		}
	}

	sf::Font &AssetManager::GetFont(std::string name) {
		
		if (_fonts.count(name) > 0) {
			return this->_fonts.at(name);
		}
		else {
			std::cout << "Could not find font file:" << name << std::endl;
		}

	}
}