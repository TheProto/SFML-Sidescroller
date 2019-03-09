#include "SpawnableEntity.h"

namespace ProtoEngine {

	SpawnableEntity::SpawnableEntity(float gravity, float drag, sf::Vector2f position,
		LevelManager *level_ptr, int animationRows, int animUpdateFreq) 
	{
		_moveManager = new MovementManager(gravity, drag, position, level_ptr);
		_anim = new FlipBook(animationRows);
		_level_ptr = level_ptr;
		_animFrameLimit = animUpdateFreq;
		_animFrameCounter = 0;
	}

	SpawnableEntity::~SpawnableEntity() {
	
	}

	void SpawnableEntity::UpdateEntity(float dt) {
		_moveManager->updatePosition(dt);

		//UpdateAnimation
		if (_animFrameCounter >= _animFrameLimit) {
			_animFrameCounter = 0;

			//And is on the ground.
			if (_moveManager->isOnGronund()) {
				
				//PlayingIdleAnimation
				if (_moveManager->isIdle()) {
					
					if (_moveManager->isGoingRight()) {
						//IdlingRight;
						_entitySprite = _anim->requestSpriteByRow(4);
						//std::cout << "RightIdleAnimation" << std::endl;
					}
					else {
						//IdlingLeft;
						_entitySprite = _anim->requestSpriteByRow(5);
						//std::cout << "LeftIdleAnimation" << std::endl;
					}
					//_entitySprite = _anim->requestSpriteByRow(5);
					//_entitySprite.setPosition(_moveManager->getEntityPosition());
				} else {
					if (_moveManager->isGoingRight()) {
						//GoingRight;
						_entitySprite = _anim->requestSpriteByRow(0);
						//std::cout << "RightMovingAnimation" << std::endl;
					}
					else {
						//GoingLeft;
						_entitySprite = _anim->requestSpriteByRow(1);
						//std::cout << "LeftMovingAnimation" << std::endl;
					}
				}
			} else {
				if (_moveManager->isGoingRight()) {
					//GoingRight;
					_entitySprite = _anim->requestSpriteByRow(2);
					//std::cout << "RightJumpAnimation" << std::endl;
				}
				else {
					//GoingLeft;
					_entitySprite = _anim->requestSpriteByRow(3);
					//std::cout << "LeftJumpAnimation" << std::endl;
				}
			}

		} else {
			_animFrameCounter++;
		}

		//_entitySprite.setPosition(_moveManager->getEntityPosition());

		sf::Vector2f tempPosition;
		tempPosition = _moveManager->getEntityPosition();
		
		_entitySprite.setPosition(sf::Vector2f(_level_ptr->getOrigin().x + (tempPosition.x * _entitySprite.getGlobalBounds().width),
			_level_ptr->getOrigin().y + (tempPosition.y * _entitySprite.getGlobalBounds().height)));
	}

	void SpawnableEntity::DrawEntity(sf::RenderWindow &window) {
		window.draw(_entitySprite);
	}

	sf::Sprite SpawnableEntity::getEntitySprite() {
		return _entitySprite;
	}

	MovementManager* SpawnableEntity::getMovementMaganer() {
		return _moveManager;
	}
	
	FlipBook* SpawnableEntity::getFlipBook() {
		return _anim;
	}
}