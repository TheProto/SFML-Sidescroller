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
		//this->_data->assets.LoadTexture("GameTitle", GAME_TITLE_FILEPATH);
		this->_data->assets.LoadTexture("PlayButton", PLAY_BUTTON_FILEPATH);
		//this->_data->playerView.zoom(10);

		_background.setTexture(this->_data->assets.GetTexture("MainMenu Background"));
		//_title.setTexture(this->_data->assets.GetTexture("GameTitle"));
		_playButton.setTexture(this->_data->assets.GetTexture("PlayButton"));

		this->_data->playerView.setSize(MENU_VIEW_WIDTH, MENU_VIEW_HEIGHT);
		this->_data->playerView.setCenter(sf::Vector2f(690, 640));
		this->_data->playerView.zoom(1.3);
		this->_data->window.setView(this->_data->playerView);


//	Positioning Spirites;
/*
		_title.setPosition( (SCREEN_WIDTH / 2) - (_title.getGlobalBounds().width/2),  
			(_title.getGlobalBounds().height / 2));

		_playButton.setPosition((SCREEN_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2),
			(SCREEN_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));

			*/
		/*
		_title.setPosition((MENU_VIEW_WIDTH / 2) - (_title.getGlobalBounds().width / 2),
			(_title.getGlobalBounds().height / 2));
			*/
			
		_playButton.setPosition((MENU_VIEW_WIDTH / 2) - (_playButton.getGlobalBounds().width / 2) + 350,
			(MENU_VIEW_HEIGHT / 2) - (_playButton.getGlobalBounds().height / 2));

	}

	void MainMenuState::HandleInput(float dt) {

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
		//_background.set
		this->_data->window.draw(_background);
		//this->_data->window.draw(_title);
		this->_data->window.draw(_playButton);

		this->_data->window.display();
	}


}