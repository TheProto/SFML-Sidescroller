#pragma once
#include "SplashState.h"
#include "DEFINITIONS.h"
#include <sstream>
#include <iostream>

namespace ProtoEngine {
	SplashState::SplashState(GameDataRef data) : _data(data) {
	}

	void SplashState::Init() {
		_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
	}

	void SplashState::HandleInput() {
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt) {
		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
			std::cout << "Go To Main Menu" << std::endl;
		}
	}

	void SplashState::Draw(float dt) {
		_data->window.clear();
		_data->window.draw(_background);
		_data->window.display();
	}


}