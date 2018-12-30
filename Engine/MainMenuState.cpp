#pragma once
#include "MainMenuState.h"
#include "GameState.h"
#include "DEFINITIONS.h"
#include <sstream>
#include <iostream>

namespace ProtoEngine {
	MainMenuState::MainMenuState(GameDataRef data) : _data(data) {
		//_data->machine.GetActiveState()->set_name("MainMenuState");
		this->set_name("MainMenuState");
	}

	void MainMenuState::Init() {
		this->_data->assets.LoadTexture("MainMenu Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("GameTitle", GAME_TITLE_FILEPATH);
		this->_data->assets.LoadTexture("PlayButton", PLAY_BUTTON_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("MainMenu Background"));
		_title.setTexture(this->_data->assets.GetTexture("GameTitle"));
		_playButton.setTexture(this->_data->assets.GetTexture("PlayButton"));

//	Positioning Spirites;
		_title.setPosition( (SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width/2),  
			(_title.getGlobalBounds().height / 2));

		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));

	}

	void MainMenuState::HandleInput() {

		sf::Event event;

		while (this->_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
			{
				std::cout << "Goto gamescreen" << std::endl;
				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt) {

	}

	void MainMenuState::Draw(float dt) {
		this->_data->window.clear();
		this->_data->window.draw(_background);
		this->_data->window.draw(_title);
		this->_data->window.draw(_playButton);

		this->_data->window.display();
	}


}