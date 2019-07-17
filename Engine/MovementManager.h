#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "LevelManager.h"
#include "SpawnableEntity.h"
#include "FlipBook.h"

namespace ProtoEngine {
	class MovementManager
	{
	public:
		
		MovementManager(LevelManager *_level_ptr);

		~MovementManager();

		int addEntity(SpawnableEntity *ent);
		int addEntity(float gravity, float drag, sf::Vector2f position,
			LevelManager *level_ptr, int animationRows, int animUpdateFreq);
		int removeEntity(unsigned long long int id);

		void updateEntities(float dt);
		void drawEntities(sf::RenderWindow &window);

	private:
		std::vector<SpawnableEntity*> _entityVector;
		LevelManager *_level_ptr;

		unsigned long long int _entityId;
		unsigned long long int _entityCount;
	};
}

