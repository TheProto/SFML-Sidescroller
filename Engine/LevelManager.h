#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <SFML\System\Vector2.hpp>

namespace ProtoEngine {
	
	class LevelManager
	{
	public:

		//LevelManager(sf::Vector2i mapSize, std::string fileName);
		LevelManager();
		~LevelManager();

		void AddTile(sf::Sprite sprite, sf::Vector2i location);
		void RemoveTile(sf::Vector2i location);
		void DrawLevel(sf::RenderWindow &window, sf::Vector2i viewDimensions);
		void setOrigin(sf::Vector2i);
		void setSize(sf::Vector2i mapSize);
		sf::Vector2i getOrigin();
		
		sf::Sprite* get_tile(sf::Vector2i norm_position);

	private:
		std::string _fileName;
		sf::Vector2i _levelOrigin;
		sf::Vector2i _mapSize;
		std::vector<std::vector<sf::Sprite>> _tileMap;	
	};

}