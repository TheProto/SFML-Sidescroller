#pragma once
#include <SFML/Graphics.hpp>
#include "LevelManager.h"

namespace ProtoEngine {
	class MovementManager
	{
	public:
		
		MovementManager(float gravity, float drag, sf::Vector2f position,
			LevelManager *_level_ptr);
		~MovementManager();

		void updatePosition(float dt);
//		void DrawEntity(sf::RenderWindow &window);

		float getGravity();
		void setGravity(float gravity);

		float getDrag();
		void setDrag(float drag);

		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f entityPosition);

//		sf::Sprite getSprite();
//		void setSprite(sf::Sprite entitySprite);

		sf::Vector2f getEntityPosition();
		sf::Vector2f getEntityVelocity();

		float getEntityVelocity_X();
		float getEntityVelocity_Y();
		
		void setEntityVelocity(sf::Vector2f entityVelocity);
		void addEntityVelocity(sf::Vector2f entityVelocity);
		
		void setEntityVelocity_X(float entityVelocity_X);
		void addEntityVelocity_X(float entityVelocity_X);
		void setEntityVelocity_Y(float entityVelocity_Y);
		void addEntityVelocity_Y(float entityVelocity_Y);

		bool isGoingRight();
		bool isOnGronund();
		bool isIdle();

		//int getActiveEntities();

	private:
		float _gravity;
		float _drag;
		sf::Vector2f _entityPosition;
		sf::Vector2f _realEntityPosition;
		sf::Vector2f _newEntityPosition;
		sf::Vector2f _entityVelocity;
		//sf::Sprite _entitySprite;

		LevelManager *_level_ptr;

		bool _goingRight;
		bool _entityOnGround;
		bool _isIdle;
		//static long _activeEntities;
	};
}

