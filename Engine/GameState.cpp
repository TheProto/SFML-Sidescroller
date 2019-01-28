#pragma once
#include "GameState.h"
#include "DEFINITIONS.h"
#include <sstream>
#include <iostream>
#include "MovementManager.h"

namespace ProtoEngine {
	GameState::GameState(GameDataRef data) : _data(data) {
		//_data->machine.GetActiveState()->set_name("GameState");
		this->set_name("GameState");
	}

	void GameState::Init() {
		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("TestSpritesheet", GAME_TEST_SPRITESHEET);
		_level.setSize(sf::Vector2i(20, 30));

		//this->_data->playerView.setCenter(sf::Vector2f(PLAYER_VIEW_WIDTH/2, PLAYER_VIEW_HEIGHT/2));
		//this->_data->playerView.zoom(0.5);
		this->_data->playerView.setSize(PLAYER_VIEW_WIDTH, PLAYER_VIEW_HEIGHT);
		//this->_data->playerView.zoom();
		sf::Vector2f playerViewCentre = _data->playerView.getCenter();
		printf("Player View Centre - x[%f] y[%f]!\n", playerViewCentre.x, playerViewCentre.y);
		//system("PAUSE");
		//this->_data->playerView.setCenter(sf::Vector2f((20*16) / 2, (30 * 16) / 2));
		this->_data->playerView.setCenter(sf::Vector2f(240, 240));
		this->_data->window.setView(this->_data->playerView);
		//this->_data->playerView.setCenter(sf::Vector2f( 0, 0));
		
		_spriteSheet.IndexSpritesheet(this->_data->assets.GetTexture("TestSpritesheet"),
			1, 16);
		
		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(5, 10));
		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(6, 10));
		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(7, 10));
		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(8, 10));
		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(9, 10));


		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(0, 0));
		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(19, 0));
		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(0, 29));
		_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(19, 29));

		for (int i = 1; i < 29; i++) {
			_level.AddTile(_spriteSheet.getSpriteId(1), sf::Vector2i(i, 19));
		}

		_background.setTexture(this->_data->assets.GetTexture("Game Background"));

		_hero = new MovementManager(20.0f, -3.0f,sf::Vector2f(2.0f,2.0f), _spriteSheet.getSpriteId(3), &_level);
	}

	void GameState::HandleInput(float dt) {

		sf::Event event;

		while (this->_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			else if (sf::Event::KeyPressed == event.type) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					_hero->addEntityVelocity_X(25 * dt);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					_hero->addEntityVelocity_X(-25 * dt);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					_hero->setEntityVelocity_Y(-6.0f);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					_hero->setEntityVelocity_Y(6.0f);
				}

			}
		}
	}

	void GameState::Update(float dt) {
		_hero->updatePosition(dt);

		this->_data->playerView.setCenter(sf::Vector2f(_hero->getSprite().getPosition().x, 195));

	}

	void GameState::Draw(float dt) {
		sf::Sprite tempSprite;

		this->_data->window.clear();
		this->_data->window.draw(_background);
		
		tempSprite = _spriteSheet.getSpriteId(0);
		tempSprite.setPosition(sf::Vector2f(20,20));
		_level.DrawLevel(this->_data->window, sf::Vector2i(PLAYER_VIEW_HEIGHT, PLAYER_VIEW_WIDTH));
		this->_hero->DrawEntity(this->_data->window);
		this->_data->window.draw(tempSprite);
		this->_data->window.setView(_data->playerView);
		this->_data->window.display();
	}


}