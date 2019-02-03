#include "LevelManager.h"

namespace ProtoEngine {

	/*
	LevelManager::LevelManager(sf::Vector2i mapSize, std::string fileName) {
		_mapSize = mapSize;
		_fileName = fileName;

		//Reserving memory for the map;
		_tileMap.reserve(_mapSize.y);
		for (int i = 0; i < _mapSize.y; i++) {
			_tileMap[i].reserve(_mapSize.x);
		}
	}
	*/

	LevelManager::LevelManager() {
	}

	LevelManager::~LevelManager() {
	}

	void LevelManager::AddTile(sf::Sprite sprite, sf::Vector2i location) {
		//sf::Sprite *targetSprite = &_tileMap[location.y][location.x];
		//_tileMap[location.y][location.x] = sprite;
		if (location.x >= _mapSize.x || location.y >= _mapSize.y) {
			printf("Failed to add tile with coordinates - [%d][%d]", location.x, location.y);
			return;
		}
		printf("Adding tile with coordinates [%d][%d]\n", location.x, location.y);
		_tileMap[location.y][location.x] = sprite;
		_tileMap[location.y][location.x].setPosition(sf::Vector2f(
			_levelOrigin.x + (location.x * _tileMap[location.y][location.x].getGlobalBounds().width),
			_levelOrigin.y + (location.y * _tileMap[location.y][location.x].getGlobalBounds().height)));

		//targetSprite->getTexture = sprite.getTexture;
	}
	
	void LevelManager::RemoveTile(sf::Vector2i location) {
		sf::Sprite *targetSprite = &_tileMap[location.y][location.x];
		targetSprite->setPosition(sf::Vector2f(-1, -1));
	}
	
	void LevelManager::DrawLevel(sf::RenderWindow &window, sf::Vector2i viewDimensions) {
		for (int i = 0 ; i < _mapSize.y ; ++i) {
			for (int j = 0; j < _mapSize.x; ++j) {
				
				if (_tileMap[i][j].getPosition().x > 0 && _tileMap[i][j].getPosition().y > 0) {
					//std::cout << "----------Window draw Call - Tile[" << i << "][" << j << "]!" << std::endl;
					//std::cout << "Tile Coordinates [" << _tileMap[i][j].getPosition().x << "][" <<
					//	_tileMap[i][j].getPosition().y << "]" << std::endl;
					window.draw(_tileMap[i][j]);
				}
			}
		}
		//system("PAUSE");
	}
	
	void LevelManager::setSize(sf::Vector2i size) {
		_mapSize = size;
		
		_levelOrigin.y = 1;
		_levelOrigin.x = 1;

		_tileMap.resize(_mapSize.y);
		for (int i = 0; i < _mapSize.y; i++) {
			std::cout << "Reserving elements\n" << std::endl;
			_tileMap[i].resize(_mapSize.x);
		}
		std::cout << "Trying to access an element in the level array\n" << std::endl;
		_tileMap[5][0].setPosition(sf::Vector2f (10,10));
		std::cout << "Trying to access an element in the level array\n" << std::endl;
	}

	void LevelManager::setOrigin(sf::Vector2i) {
	}
	
	/*
	sf::Vector2i LevelManager::getOrigin(sf::Vector2i) {
		return sf::Vector2i(10, 10);
	}
	*/
	sf::Vector2i LevelManager::getOrigin() {
		return _levelOrigin;
	}

	sf::Sprite* LevelManager::get_tile(sf::Vector2i norm_position) {
		
		//printf("Tilemap position requested! - X = %d, Y = %d\n",
			//norm_position.x, norm_position.y);

		if ((norm_position.x < _mapSize.x && norm_position.x > -1) &&
			(norm_position.y < _mapSize.y && norm_position.y > -1)) {
			if (_tileMap[norm_position.y][norm_position.x].getTexture() != NULL) {
				return &_tileMap[norm_position.y][norm_position.x];
			}
			else {
				return NULL;
			}
		}
		else {
			//std::cout << "Invalid tilemap position requested!" << std::endl;
			printf("Invalid tilemap position requested! - X = %d, Y = %d\n",
				norm_position.x, norm_position.y);
			return NULL;
		}
	
	}
	
	int LevelManager::loadFromFile(std::string filename, SpriteIndex &_spriteSheet) {

		std::ifstream level_file;
		level_file.open(filename);

		std::stringstream ss; 
		std::string temp_str;
		int temp_int;

		getline(level_file, temp_str);
		
		ss << temp_str;
	
		ss >> temp_int;
		_mapSize.x = temp_int;
		ss >> temp_int;
		_mapSize.y = temp_int;
		
		//Allocating memory
		this->setSize(_mapSize);

		for (int i = 0; i < _mapSize.y; i++) {
		
			getline(level_file, temp_str);
			for (int k = 0 ; k < _mapSize.x ; k++) {
				/*
				switch (temp_str[k]) {
					case '.':
						break;
					
					case 'X':
						//_tileMap[i][k] = _spriteSheet.getSpriteId(1);
						printf("registered cube at y = %d , X= ")
						this->AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(k, i));

						break;
				}
				*/

				if (temp_str[k] >= 65 && temp_str[k] <= 92) {
					this->AddTile(_spriteSheet.getSpriteId(temp_str[k]-65), sf::Vector2i(k, i));
				}
			}
		}
		return 0;
	}

}