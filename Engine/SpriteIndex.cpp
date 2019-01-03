#include "SpriteIndex.h"

namespace ProtoEngine {
	
	SpriteIndex::SpriteIndex() {
	}
	
	SpriteIndex::~SpriteIndex() {
	}

	SpriteIndex::SpriteIndex(sf::Texture &tileTexture, int borderSize, int spriteSize) {
		IndexSpritesheet(tileTexture, borderSize, spriteSize);
	}

	int SpriteIndex::IndexSpritesheet(sf::Texture &tileTexture, int borderSize, int spriteSize) {

		sf::Vector2i position, size;
		bool IndexingTexturesFlag = true;

		size.x = spriteSize;
		size.y = spriteSize;

		position.y += borderSize;

		while (IndexingTexturesFlag) {
			std::cout << "Started indexing textures" << std::endl;

			position.x += borderSize;

			if (position.x < tileTexture.getSize().x &&
				position.y < tileTexture.getSize().y) {

				std::cout << "Creating a sprite from x:" << position.x <<
					" y:" << position.y << std::endl;

				sf::IntRect tempRect(position, size);
				sf::Sprite tempSprite(tileTexture, tempRect);

				_SpIndex.push_back(tempSprite);

				position.x += spriteSize;
				//position.y += spriteSize;
			}
			else
			{
				std::cout << "Finished Indexing Textures" << std::endl;
				IndexingTexturesFlag = false;
			}
		}
		return 0;
	}
	
	sf::Sprite SpriteIndex::getSpriteId(int id) {
		return _SpIndex.at(id);
	}
}