#pragma once
#include "FlipBook.h"
#include "LevelManager.h"

namespace ProtoEngine {
	class SpawnableEntity
	{
	public:

		SpawnableEntity(float gravity, float drag, sf::Vector2f position,
			LevelManager *level_ptr, int animationRows, int animationUpdateCounter);
		~SpawnableEntity();

		//void UpdateEntity(float dt);
		void DrawEntity(sf::RenderWindow &window);

		sf::Sprite getEntitySprite();
		void setEntitySprite(sf::Sprite sprt);

		FlipBook* getFlipBook();

		float getGravity();
		void setGravity(float gravity);

		float getDrag();
		void setDrag(float drag);

		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f entityPosition);

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

		void setGoingRight(bool state);
		void setOnGround(bool state);
		void setIdle(bool state);

		unsigned long long int getEntityId();
		int setEntityId(unsigned long long int id);

		unsigned int getAnimFrameLimit();
		void setAnimFrameLimit(unsigned int cntr);

		unsigned int getAnimFrameCounter();
		void setAnimFrameCounter(unsigned int cntr);

	private:

		LevelManager *_level_ptr;

		//Position Variables
		unsigned long long int _entityId;

		float _gravity;
		float _drag;
		sf::Vector2f _entityPosition;
		sf::Vector2f _realEntityPosition;
		//sf::Vector2f _newEntityPosition;
		sf::Vector2f _entityVelocity;

		bool _goingRight;
		bool _entityOnGround;
		bool _isIdle;

		//Entity Assets
		sf::Sprite _entitySprite;
		FlipBook *_anim;
		unsigned int _animFrameLimit;
		unsigned int _animFrameCounter;
	};
}

