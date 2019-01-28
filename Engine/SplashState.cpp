#pragma once
#include "SplashState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include <sstream>
#include <iostream>

namespace ProtoEngine {
	SplashState::SplashState(GameDataRef data) : _data(data) {
		//_data->machine.GetActiveState()->set_name("SplashState");
		this->set_name("SplashState");
	}

	void SplashState::Init() {
		_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));
		sf::Vector2f splashTransform;
		splashTransform.x = PLAYER_VIEW_WIDTH / _background.getGlobalBounds().width;
		splashTransform.y = PLAYER_VIEW_HEIGHT / _background.getGlobalBounds().height;
		_background.setScale(splashTransform);
	}

	void SplashState::HandleInput(float dt) {
		sf::Event event;
		while (_data->window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt) {
		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
			//std::cout << "Go To Main Menu" << std::endl;
			_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
		}
	}

	void SplashState::Draw(float dt) {
		_data->window.clear();
//		playerViewCenter =_data->playerView.getCenter();
//		_background.setPosition((playerViewCenter.x - PLAYER_VIEW_WIDTH/2),
//								(playerViewCenter.y - PLAYER_VIEW_HEIGHT/2));

		_data->window.draw(_background);
		_data->window.display();
	}


}