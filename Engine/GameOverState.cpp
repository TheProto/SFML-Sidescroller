#pragma once
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include <sstream>
#include <iostream>

namespace ProtoEngine {
	GameOverState::GameOverState(GameDataRef data) : _data(data) {
		//_data->machine.GetActiveState()->set_name("GameOverState");
		this->set_name("GameOverState");
	}

	void GameOverState::Init() {
		this->_data->assets.LoadTexture("GameOver Background", GAME_OVER_BACKGROUND_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("GameOver Background"));

	}

	void GameOverState::HandleInput() {

		sf::Event event;

		while (this->_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

		}
	}

	void GameOverState::Update(float dt) {

	}

	void GameOverState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(_background);

		this->_data->window.display();
	}


}