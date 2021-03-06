#pragma once
#include <memory>
#include <string>
#include <SFML\Graphics.hpp>

#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace ProtoEngine
{
	struct GameData {
		StateMachine  machine;
		sf::RenderWindow window;
		sf::View playerView;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		//Updates run at 60fps.
		const float dt = 1.0f / 60.0f;
		sf::Clock _clock;
		GameDataRef _data = std::make_shared<GameData>();
		
		void Run();
	};
}

