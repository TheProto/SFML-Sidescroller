#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>

namespace ProtoEngine {
	class SpriteIndex
	{
	public:
		SpriteIndex(sf::Texture &tileTexture, int borderSize, int spriteSize);
		SpriteIndex();
		~SpriteIndex();

		int IndexSpritesheet(sf::Texture &tileTexture, int borderSize, int spriteSize);
		int getSpriteCount();

		sf::Sprite getSpriteId(int id);
	private:
		std::vector<sf::Sprite> _SpIndex;
		int _spriteCount;

	};
}

