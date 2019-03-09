#pragma once
#include "MovementManager.h"
#include "FlipBook.h"

namespace ProtoEngine {
	class SpawnableEntity
	{
	public:

		SpawnableEntity(float gravity, float drag, sf::Vector2f position,
			LevelManager *level_ptr, int animationRows, int animationUpdateCounter);
		~SpawnableEntity();

		void UpdateEntity(float dt);
		void DrawEntity(sf::RenderWindow &window);

		sf::Sprite getEntitySprite();

		MovementManager* getMovementMaganer();
		FlipBook* getFlipBook();

	private:

		LevelManager *_level_ptr;

		sf::Sprite _entitySprite;
		MovementManager *_moveManager;
		FlipBook *_anim;
		unsigned int _animFrameLimit;
		unsigned int _animFrameCounter;
	};
}

