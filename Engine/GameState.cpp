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
		this->_data->window.clear();
		this->_data->window.draw(_background);

		this->_data->window.display();
	}


}