#pragma once
#include "GameState.h"
#include "DEFINITIONS.h"
#include <sstream>
#include <iostream>

namespace ProtoEngine {
	GameState::GameState(GameDataRef data) : _data(data) {
		//_data->machine.GetActiveState()->set_name("GameState");
		this->set_name("GameState");
	}

	void GameState::Init() {
		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("TestSpritesheet", GAME_TEST_SPRITESHEET);

		_spriteSheet.IndexSpritesheet(this->_data->assets.GetTexture("TestSpritesheet"),
			1, 16);
		_background.setTexture(this->_data->assets.GetTexture("Game Background"));
	}

	void GameState::HandleInput() {

		sf::Event event;

		while (this->_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

		}
	}

	void GameState::Update(float dt) {

	}

	void GameState::Draw(float dt) {
		sf::Sprite tempSprite;

		this->_data->window.clear();
		this->_data->window.draw(_background);
		
		tempSprite = _spriteSheet.getSpriteId(0);
		tempSprite.setPosition(sf::Vector2f(20,20));
		this->_data->window.draw(tempSprite);
		
		this->_data->window.display();
	}


}