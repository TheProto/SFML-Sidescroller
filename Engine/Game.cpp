#include "Game.h"
#include <iostream>
#include "SplashState.h"
#include "Definitions.h"

namespace ProtoEngine
{
	Game::Game(int width, int height, std::string title) {
		_data->window.create(sf::VideoMode(width, height),title, sf::Style::Close | sf::Style::Titlebar);
		_data->playerView.setSize(sf::Vector2f(PLAYER_VIEW_WIDTH, PLAYER_VIEW_HEIGHT));
		_data->playerView.setCenter((PLAYER_VIEW_WIDTH / 2), (PLAYER_VIEW_HEIGHT / 2));
		_data->playerView.zoom(1);
		_data->window.setView(_data->playerView);
		_data->machine.AddState(StateRef(new SplashState(this->_data)));

		this->Run();
	}

	void Game::Run(){
		float newTime, frameTime, interpolation;

		float currentTime = this->_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;
		
		while(this->_data->window.isOpen()) {
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;
			
			if (frameTime > 0.25f) {
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt) {
				this->_data->machine.GetActiveState()->HandleInput(dt);
				this->_data->machine.GetActiveState()->Update(dt);

				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			this->_data->machine.GetActiveState()->Draw(interpolation);
		}
	}
}