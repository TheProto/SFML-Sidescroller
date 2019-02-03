#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Audio.hpp>
#include "SpriteIndex.h"
#include "LevelManager.h"
#include "MovementManager.h"
#include "State.h"
#include "Game.h"
#include "FlipBook.h"

namespace ProtoEngine {
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput(float dt);
		void Update(float dt);
		void Draw(float dt);

	private:
		int animCounter;
		bool _goingRight;
		bool _gotInput;
		GameDataRef _data;

		sf::Clock _clock;

		sf::Sprite _background;
		sf::Sprite _levelBackground;
		SpriteIndex _spriteSheet;
		SpriteIndex _heroSpriteSheet;
		LevelManager _level;
		MovementManager *_hero;

		sf::SoundBuffer _soundBuffer;
		sf::Sound _sound;
		sf::Music _music;

		FlipBook *_heroAnim;
	};
}

