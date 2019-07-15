#include "PauseMenuState.h"

//void MainMenuState::HandleInput(float dt) {
namespace ProtoEngine {

	PauseMenuState::PauseMenuState(GameDataRef data) : _data(data) {
		this->set_name("PauseMenuState");
	}

	void PauseMenuState::Init() {
		//_pauseMenuBack.setColor(sf::Color::Black);
		_font = _data->assets.GetFont("Atarian");

		/*Game Over Title*/
		
		_gameOverTitle.setString("Pause");
		_gameOverTitle.setFont(_font);
		_gameOverTitle.setCharacterSize(56);
		_gameOverTitle.setFillColor(sf::Color::White);
	
		sf::Vector2f viewCenter;
		viewCenter = _data->window.getView().getCenter();

		std::cout<<"Character size = "<<_gameOverTitle.getCharacterSize()<<";"<<std::endl;
		_gameOverTitle.setPosition(
			sf::Vector2f(
				viewCenter.x,
				viewCenter.y - 16
			)
		);
		

		//_data->window.get
	}
	
	void PauseMenuState::HandleInput(float dt) {

		sf::Event event;

		while (_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					_data->machine.RemoveState();
				}
			}
			/*
			if (this->_data->input.IsSpriteClicked(this->_playButton, sf::Mouse::Left, this->_data->window))
			{
				std::cout << "Goto gamescreen" << std::endl;
				_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
			*/
		}
	}

	void PauseMenuState::Update(float dt) {

	}

	void PauseMenuState::Draw(float dt) {
		_data->window.draw(_gameOverTitle);
		_data->window.display();
	}
}