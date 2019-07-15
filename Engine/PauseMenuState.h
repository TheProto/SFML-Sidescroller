#pragma once
#include "State.h"
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Rect.hpp>
#include "State.h"
#include "Game.h"
#include "DEFINITIONS.h"


namespace ProtoEngine {
	class PauseMenuState : public State
	{
	public:
		PauseMenuState(GameDataRef data);

		void Init();
		void HandleInput(float dt);
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;
		sf::Sprite _pauseMenuBack;

		sf::Text _gameOverTitle;
		sf::Font _font;
//		sf::Sprite _background;
//		sf::Sprite _title;
//		sf::Sprite _playButton;
	};
}

/*
class PauseMenuState :
	public State
{
public:
	PauseMenuState();
	~PauseMenuState();
};
*/

