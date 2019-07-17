#include "MovementManager.h"
#include <math.h>

namespace ProtoEngine {

	MovementManager::MovementManager(LevelManager *level_ptr) {
		this->_level_ptr = level_ptr;
	}

	MovementManager::~MovementManager() {
	}

	int MovementManager::addEntity(SpawnableEntity *ent) {
		(*ent).setEntityId(_entityId);
		_entityVector.push_back(ent);
		_entityId++;
		_entityCount++;
		return 0;
	}

	int MovementManager::addEntity(float gravity, float drag, sf::Vector2f position,
		LevelManager *level_ptr, int animationRows, int animUpdateFreq) {

		//SpawnableEntity *newEntity;
		//newEntity = new SpawnableEntity(gravity, drag, position, level_ptr, animationRows, animUpdateFreq);
		//*_entityVector.push_back(SpawnableEntity(gravity, drag, position, level_ptr, animationRows, animUpdateFreq));
		return 0;
	}
	
	int MovementManager::removeEntity(unsigned long long int id) {
		std::vector<SpawnableEntity *>::iterator iter;

		for (iter = _entityVector.begin(); iter != _entityVector.end(); iter++) {
			if ((*iter)->getEntityId() == id) {
				_entityVector.erase(iter);
				_entityCount--;
			}
		}
		return 0;
	}

	void MovementManager::updateEntities(float dt) {
		std::vector<SpawnableEntity *>::iterator iter;
		std::cout << "ActiveEntities:" << _entityVector.size()<< std::endl;
		//temp physics variables

		sf::Sprite tempEntitySprite;
		sf::Vector2f newEntityPosition;
		sf::Vector2f tempEntityPosition;
		sf::Vector2f tempVelocity;
		FlipBook *tempFlipBook;
		float tempGravity;
		float tempDrag;
		unsigned int tempFrameCounter;
		unsigned int tempFrameLimit;

		for (iter = _entityVector.begin(); iter != _entityVector.end(); iter++) {

			//Resetting Variables


			//Getting Initial Entity Info
			tempEntityPosition = (*iter)->getEntityPosition();
			tempVelocity = (*iter)->getEntityVelocity();
			tempGravity = (*iter)->getGravity();
			tempDrag = (*iter)->getDrag();

			if ((*iter)->isAI()) {
				if ((*iter)->aiGoingRight()) {
					tempVelocity.x += 35;
				} else {
					tempVelocity.x -= 35;
				}
			}

			//Calculating gravity
			tempVelocity.y += tempGravity * dt;

			//Drag
			if ((*iter)->isOnGronund()) {
				tempVelocity.x += tempDrag * tempVelocity.x * dt;
				if (fabs(tempVelocity.x) < 0.01f) {
					tempVelocity.x = 0.0f;
				}
			}


			// Clamp velocities
			if (tempVelocity.x > 10.0f) { tempVelocity.x = 10.0f; }
			if (tempVelocity.x < -10.0f) { tempVelocity.x = -10.0f; }

			if (tempVelocity.y > 100.0f) { tempVelocity.y = 100.0f; }
			if (tempVelocity.y < -100.0f) { tempVelocity.y = -100.0f; }


			// Calculate potential new position
			newEntityPosition.x = tempEntityPosition.x + tempVelocity.x * dt;
			newEntityPosition.y = tempEntityPosition.y + tempVelocity.y * dt;

			//Checking for collision
			if (tempVelocity.x <= -0.000001f)//Moving Left
			{
				(*iter)->setGoingRight(false);
				if (_level_ptr->get_tile(sf::Vector2i(newEntityPosition.x + 0.0f, tempEntityPosition.y + 0.0f)) != NULL ||
					_level_ptr->get_tile(sf::Vector2i(newEntityPosition.x + 0.0f, tempEntityPosition.y + 0.9f)) != NULL)
				{
					newEntityPosition.x = (int)newEntityPosition.x + 1;
					tempVelocity.x = 0;
					if ((*iter)->isAI()) {
						(*iter)->setAiGoingRight(true);
					}
				}
			}
			else if (tempVelocity.x >= 0.000001f)//Moving Right
			{
				(*iter)->setGoingRight(true);
				if (_level_ptr->get_tile(sf::Vector2i(newEntityPosition.x + 1.0f, tempEntityPosition.y + 0.0f)) != NULL ||
					_level_ptr->get_tile(sf::Vector2i(newEntityPosition.x + 1.0f, tempEntityPosition.y + 0.9f)) != NULL)
				{
					newEntityPosition.x = (int)newEntityPosition.x;
					tempVelocity.x = 0;
					if ((*iter)->isAI()) {
						(*iter)->setAiGoingRight(false);
					}
				}

			}

			(*iter)->setOnGround(false);
			if (tempVelocity.y <= 0)//Moving Up
			{
				if (_level_ptr->get_tile(sf::Vector2i(newEntityPosition.x + 0.0f, newEntityPosition.y)) != NULL ||
					_level_ptr->get_tile(sf::Vector2i(newEntityPosition.x + 0.9f, newEntityPosition.y)) != NULL)
				{
					newEntityPosition.y = (int)newEntityPosition.y + 1;
					tempVelocity.y = 0;
				}
			}
			else //OnGround
			{
				if (_level_ptr->get_tile(sf::Vector2i(newEntityPosition.x + 0.0f, newEntityPosition.y + 1.0f)) != NULL ||
					_level_ptr->get_tile(sf::Vector2i(newEntityPosition.x + 0.9f, newEntityPosition.y + 1.0f)) != NULL)
				{
					newEntityPosition.y = (int)newEntityPosition.y;
					tempVelocity.y = 0;
					(*iter)->setOnGround(true);
				}
			}

			//Checking Idle
			if (tempVelocity.x >= -0.5f && tempVelocity.x <= 0.5f) {
				(*iter)->setIdle(true);
			} else {
				(*iter)->setIdle(false);
			}

			//Applying new position.
			tempEntityPosition.x = newEntityPosition.x;
			tempEntityPosition.y = newEntityPosition.y;

			(*iter)->setEntityVelocity(tempVelocity);
			(*iter)->setPosition(tempEntityPosition);

			//UpdateAnimation
			
			tempEntitySprite = (*iter)->getEntitySprite();
			tempFlipBook = (*iter)->getFlipBook();
			tempFrameCounter = (*iter)->getAnimFrameCounter();
			tempFrameLimit = (*iter)->getAnimFrameLimit();

				if (tempFrameCounter >= tempFrameLimit) {
					tempFrameCounter = 0;

					//And is on the ground.
					if ((*iter)->isOnGronund()) {

						//PlayingIdleAnimation
						if ((*iter)->isIdle()) {

							if ((*iter)->isGoingRight()) {
								//IdlingRight;
								tempEntitySprite = tempFlipBook->requestSpriteByRow(4);
								//std::cout << "RightIdleAnimation" << std::endl;
							}
							else {
								//IdlingLeft;
								tempEntitySprite = tempFlipBook->requestSpriteByRow(5);
								//std::cout << "LeftIdleAnimation" << std::endl;
							}
							//_entitySprite = _anim->requestSpriteByRow(5);
							//_entitySprite.setPosition(_moveManager->getEntityPosition());
						}
						else {
							if ((*iter)->isGoingRight()) {
								//GoingRight;
								tempEntitySprite = tempFlipBook->requestSpriteByRow(0);
								//std::cout << "RightMovingAnimation" << std::endl;
							}
							else {
								//GoingLeft;
								tempEntitySprite = tempFlipBook->requestSpriteByRow(1);
								//std::cout << "LeftMovingAnimation" << std::endl;
							}
						}
					}
					else {
						if ((*iter)->isGoingRight()) {
							//GoingRight;
							tempEntitySprite = tempFlipBook->requestSpriteByRow(2);
							//std::cout << "RightJumpAnimation" << std::endl;
						}
						else {
							//GoingLeft;
							tempEntitySprite = tempFlipBook->requestSpriteByRow(3);
							//std::cout << "LeftJumpAnimation" << std::endl;
						}
					}

				}
				else {
					//_animFrameCounter++;
					tempFrameCounter++;
				}
				
				(*iter)->setAnimFrameCounter(tempFrameCounter);

				tempEntitySprite.setPosition(sf::Vector2f(_level_ptr->getOrigin().x + (tempEntityPosition.x * tempEntitySprite.getGlobalBounds().width),
					_level_ptr->getOrigin().y + (tempEntityPosition.y * tempEntitySprite.getGlobalBounds().height)));

				(*iter)->setEntitySprite(tempEntitySprite);

				//Checking for other collisions
				
				std::vector<SpawnableEntity *>::iterator colIter;
				sf::FloatRect curEntityRect(tempEntityPosition, sf::Vector2f(0.8, 0.8));

				sf::Vector2f newEntityPos;
				//std::cout << "EntityPosX:" << tempEntityPosition.x << " EntityPosY:" << tempEntityPosition.y << std::endl;
				for (colIter = _entityVector.begin(); colIter != _entityVector.end(); colIter++) {
					
					if ((*iter)->getEntityId() == (*colIter)->getEntityId()) {
						continue;
					}
					
					newEntityPos = (*colIter)->getEntityPosition();
					if (newEntityPos.x < 0 || newEntityPos.y > 26) {
						if (!(*colIter)->isGod()) {
							(*colIter)->setDead(true);
							continue; 
						}
					}

					sf::FloatRect newEntityRect(newEntityPos, sf::Vector2f(0.8, 0.8));

					if (curEntityRect.intersects(newEntityRect)) {

						if ((*iter)->getDestFactor() > (*colIter)->getDestFactor()) {
							
							if (!(*colIter)->isGod()) {
								(*colIter)->setDead(true);
							}
						} else if ((*iter)->getDestFactor() < (*colIter)->getDestFactor()){

							if (!(*iter)->isGod()) {
								(*iter)->setDead(true);
							}
						} else {
						    
						}

						//std::cout << "Intersects!" << std::endl;
						if (tempEntityPosition.x > newEntityPos.x) {
							tempEntityPosition.x = newEntityPos.x + 0.8;
						} else {
							tempEntityPosition.x = newEntityPos.x - 0.8;
						}

						/*
						if (tempEntityPosition.x > newEntityPos.x) {

						} else {

						}
						*/
					}
				}

				(*iter)->setPosition(tempEntityPosition);
				//(*iter)->setEntityVelocity(tempVelocity);

		}

		//Deleting killed entities
		std::vector<SpawnableEntity *>::iterator colIter;
		for (colIter = _entityVector.begin(); colIter != _entityVector.end(); colIter++)
		{
			if ((*colIter)->isDead()) {
				_entityVector.erase(colIter);
				colIter = _entityVector.begin();
			}
		}
	}


	void MovementManager::drawEntities(sf::RenderWindow &window) {
		std::vector<SpawnableEntity *>::iterator iter;

		for (iter = _entityVector.begin(); iter != _entityVector.end(); iter++) {
			(*iter)->DrawEntity(window);
		}
	}
}
