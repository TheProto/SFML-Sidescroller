#include "SpawnableEntity.h"

namespace ProtoEngine {

	SpawnableEntity::SpawnableEntity(float gravity, float drag, sf::Vector2f position,
		LevelManager *level_ptr, int animationRows, int animUpdateFreq) 
	{
		//_moveManager = new MovementManager(gravity, drag, position, level_ptr);
		_gravity = gravity;
		_drag = drag;
		_entityPosition = position;

		_anim = new FlipBook(animationRows);
		_level_ptr = level_ptr;
		_animFrameLimit = animUpdateFreq;
		_animFrameCounter = 0;
		this->_entityId = 0;
	}

	SpawnableEntity::~SpawnableEntity() {
	
	}

	/*
	void SpawnableEntity::UpdateEntity(float dt) {
		//_moveManager->updatePosition(dt);

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
	*/

	void SpawnableEntity::DrawEntity(sf::RenderWindow &window) {
		window.draw(_entitySprite);
	}

	sf::Sprite SpawnableEntity::getEntitySprite() {
		return _entitySprite;
	}
	
	FlipBook* SpawnableEntity::getFlipBook() {
		return _anim;
	}


	float SpawnableEntity::getGravity() {
		return this->_gravity;
	}
	void SpawnableEntity::setGravity(float gravity) {
		this->_gravity = gravity;
	}

	float SpawnableEntity::getDrag() {
		return this->_drag;
	}
	void SpawnableEntity::setDrag(float drag) {
		this->_drag = drag;
	}

	sf::Vector2f SpawnableEntity::getPosition() {
		return this->_entityPosition;
	}
	void SpawnableEntity::setPosition(sf::Vector2f position) {
		this->_entityPosition = position;
	}

	/*
		sf::Sprite SpawnableEntity::getSprite() {
			return this->_entitySprite;
		}
		void SpawnableEntity::setSprite(sf::Sprite entitySprite) {
			this->_entitySprite = entitySprite;
		}
	*/

	sf::Vector2f SpawnableEntity::getEntityPosition() {
		return this->_entityPosition;
	}

	sf::Vector2f SpawnableEntity::getEntityVelocity() {
		return this->_entityVelocity;
	}

	float SpawnableEntity::getEntityVelocity_X() {
		return this->_entityVelocity.x;
	}
	float SpawnableEntity::getEntityVelocity_Y() {
		return this->_entityVelocity.y;
	}

	void SpawnableEntity::setEntityVelocity(sf::Vector2f entityVelocity) {
		this->_entityVelocity = entityVelocity;
	}
	void SpawnableEntity::addEntityVelocity(sf::Vector2f entityVelocity) {
		this->_entityVelocity.x += entityVelocity.x;
		this->_entityVelocity.y += entityVelocity.y;
	}

	void SpawnableEntity::setEntityVelocity_X(float entityVelocity_X) {
		this->_entityVelocity.x = entityVelocity_X;
	}
	void SpawnableEntity::addEntityVelocity_X(float entityVelocity_X) {
		this->_entityVelocity.x += entityVelocity_X;
	}
	void SpawnableEntity::setEntityVelocity_Y(float entityVelocity_Y) {
		this->_entityVelocity.y = entityVelocity_Y;
	}
	void SpawnableEntity::addEntityVelocity_Y(float entityVelocity_Y) {
		this->_entityVelocity.y += entityVelocity_Y;
	}


	bool SpawnableEntity::isGoingRight() {
		return _goingRight;
	}

	bool SpawnableEntity::isOnGronund() {
		return _entityOnGround;
	}

	bool SpawnableEntity::isIdle() {
		return _isIdle;
	}

	unsigned long long int SpawnableEntity::getEntityId() {
		return _entityId;
	}
	
	int SpawnableEntity::setEntityId(unsigned long long int id) {
		if (id > 0) {
			this->_entityId = id;
		} else {
			std::cout << "Ivalid entity id!" << std::endl;
			return -EINVAL;
		}
		return 0;
	}

	void SpawnableEntity::setGoingRight(bool state) {
		this->_goingRight = state;
	}
	
	void SpawnableEntity::setOnGround(bool state) {
		this->_entityOnGround = state;
	}
	
	void SpawnableEntity::setIdle(bool state) {
		_isIdle = state;
	}

	unsigned int SpawnableEntity::getAnimFrameLimit() {
		return _animFrameLimit;
	}
	
	void SpawnableEntity::setAnimFrameLimit(unsigned int cntr) {
		this->_animFrameLimit = cntr;
	}

	unsigned int SpawnableEntity::getAnimFrameCounter() {
		return _animFrameCounter;
	}
	
	void SpawnableEntity::setAnimFrameCounter(unsigned int cntr) {
		this->_animFrameCounter = cntr;
	}

	void SpawnableEntity::setEntitySprite(sf::Sprite sprt) {
		this->_entitySprite = sprt;
	}
}