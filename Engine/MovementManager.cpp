#include "MovementManager.h"
#include <math.h>

namespace ProtoEngine {

	MovementManager::MovementManager(float gravity, float drag, sf::Vector2f position, sf::Sprite entitySprite,
		LevelManager *level_ptr) {
		this->_gravity = gravity;
		this->_drag = drag;
		this->_entityPosition = position;
		this->_entitySprite = entitySprite;
		//this->_activeEntities++;
		this->_level_ptr = level_ptr;
	}

	MovementManager::~MovementManager() {
		//this->_activeEntities--;
	}

	void MovementManager::updatePosition(float dt) {
		
		//Gravity;
		_entityVelocity.y += _gravity * dt;

		//Drag
		if (_entityOnGround) {
			_entityVelocity.x += _drag * _entityVelocity.x * dt;
			if (fabs(_entityVelocity.x) < 0.01f) {
				_entityVelocity.x = 0.0f;
			}
		}

		// Clamp velocities
		if (_entityVelocity.x > 10.0f)
			_entityVelocity.x = 10.0f;

		if (_entityVelocity.x < -10.0f)
			_entityVelocity.x = -10.0f;

		if (_entityVelocity.y > 100.0f)
			_entityVelocity.y = 100.0f;

		if (_entityVelocity.y < -100.0f)
			_entityVelocity.y = -100.0f;

		// Calculate potential new position
		_newEntityPosition.x = _entityPosition.x + _entityVelocity.x * dt;
		_newEntityPosition.y = _entityPosition.y + _entityVelocity.y * dt;

		//Checking for collision
		if (_entityVelocity.x <= 0)//Moving Left
		{
			if (_level_ptr->get_tile(sf::Vector2i(_newEntityPosition.x + 0.0f, _entityPosition.y + 0.0f)) != NULL ||
				_level_ptr->get_tile(sf::Vector2i(_newEntityPosition.x + 0.0f, _entityPosition.y + 0.9f)) != NULL) 
			{
				_newEntityPosition.x = (int)_newEntityPosition.x + 1;
				_entityVelocity.x = 0;
			}
		}
		else
		{
			if (_level_ptr->get_tile(sf::Vector2i(_newEntityPosition.x + 1.0f, _entityPosition.y + 0.0f)) != NULL ||
				_level_ptr->get_tile(sf::Vector2i(_newEntityPosition.x + 1.0f, _entityPosition.y + 0.9f)) != NULL) 
			{
				_newEntityPosition.x = (int)_newEntityPosition.x;
				_entityVelocity.x = 0;
			}

		}
		
		_entityOnGround = false;
		if (_entityVelocity.y <= 0)//Moving Up
		{
			if (_level_ptr->get_tile(sf::Vector2i(_newEntityPosition.x + 0.0f, _newEntityPosition.y)) != NULL ||
				_level_ptr->get_tile(sf::Vector2i(_newEntityPosition.x + 0.9f, _newEntityPosition.y)) != NULL)
			{
				_newEntityPosition.y = (int)_newEntityPosition.y + 1;
				_entityVelocity.y = 0;
			}
		}
		else
		{
			if (_level_ptr->get_tile(sf::Vector2i(_newEntityPosition.x + 0.0f, _newEntityPosition.y + 1.0f)) != NULL ||
				_level_ptr->get_tile(sf::Vector2i(_newEntityPosition.x + 0.9f, _newEntityPosition.y + 1.0f)) != NULL)
			{
				_newEntityPosition.y = (int)_newEntityPosition.y;
				_entityVelocity.y = 0;
				_entityOnGround = true;

			}
		}

		//Applying new position.
		_entityPosition.x = _newEntityPosition.x;
		_entityPosition.y = _newEntityPosition.y;

		//_entitySprite.setPosition(sf::Vector2f(_entityPosition.x*16,_entityPosition.x*16));
		//_entitySprite.setPosition(sf::Vector2f(_level_ptr->getOrigin().x + (_entityPosition.x * _entitySprite.getGlobalBounds().width),
			//_level_ptr->getOrigin().y + (_entityPosition.y * _entitySprite.getGlobalBounds().height)));

		_entitySprite.setPosition(sf::Vector2f(_level_ptr->getOrigin().x + (_entityPosition.x * _entitySprite.getGlobalBounds().width),
			_level_ptr->getOrigin().y + (_entityPosition.y * _entitySprite.getGlobalBounds().height)));
	}

	void MovementManager::DrawEntity(sf::RenderWindow &window) {
		window.draw(_entitySprite);
	}

	float MovementManager::getGravity() {
		return this->_gravity;
	}
	void MovementManager::setGravity(float gravity) {
		this->_gravity = gravity;
	}

	float MovementManager::getDrag() {
		return this->_drag;
	}
	void MovementManager::setDrag(float drag) {
		this->_drag = drag;
	}

	sf::Vector2f MovementManager::getPosition() {
		return this->_entityPosition;
	}
	void MovementManager::setPosition(sf::Vector2f position) {
		this->_entityPosition = position;
	}

	sf::Sprite MovementManager::getSprite() {
		return this->_entitySprite;
	}
	void MovementManager::setSprite(sf::Sprite entitySprite) {
		this->_entitySprite = entitySprite;
	}

	sf::Vector2f MovementManager::getEntityVelocity() {
		return this->_entityVelocity;
	}
	float MovementManager::getEntityVelocity_X() {
		return this->_entityVelocity.x;
	}
	float MovementManager::getEntityVelocity_Y() {
		return this->_entityVelocity.y;
	}

	void MovementManager::setEntityVelocity(sf::Vector2f entityVelocity) {
		this->_entityVelocity = entityVelocity;
	}
	void MovementManager::addEntityVelocity(sf::Vector2f entityVelocity) {
		this->_entityVelocity.x += entityVelocity.x;
		this->_entityVelocity.y += entityVelocity.y;
	}

	void MovementManager::setEntityVelocity_X(float entityVelocity_X) {
		this->_entityVelocity.x = entityVelocity_X;
	}
	void MovementManager::addEntityVelocity_X(float entityVelocity_X) {
		this->_entityVelocity.x += entityVelocity_X;
	}
	void MovementManager::setEntityVelocity_Y(float entityVelocity_Y) {
		this->_entityVelocity.y = entityVelocity_Y;
	}
	void MovementManager::addEntityVelocity_Y(float entityVelocity_Y) {
		this->_entityVelocity.y += entityVelocity_Y;
	}

	//int MovementManager::getActiveEntities() {
		//return this->_activeEntities;
	//}
}
