#pragma once
#include <SFML\Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace ProtoEngine {
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();

		void HandleInput(float dt);
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Sprite _background;
		sf::Sprite _title;
		sf::Sprite _playButton;
	};
}

