#pragma once
#include "GameState.h"
#include "DEFINITIONS.h"
#include <sstream>
#include <iostream>
#include "MovementManager.h"

namespace ProtoEngine {
	GameState::GameState(GameDataRef data) : _data(data) {
		//_data->machine.GetActiveState()->set_name("GameState");
		this->set_name("GameState");
	}

	void GameState::Init() {
		//this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("TestSpritesheet", GAME_TEST_SPRITESHEET);
		this->_data->assets.LoadTexture("HeroSpriteSheet", HERO_SPRITESHEET);
		this->_data->assets.LoadTexture("GameLevelBackground1", GAME_LEVEL_BACKGROUND1);
		this->_data->assets.LoadTexture("Enemy1", GAME_ENEMY_1);
		this->_data->assets.LoadFont("Atarian", GAME_FONT_ATARIAN);
		this->_data->assets.LoadFont("Arial", GAME_FONT_DEFAULT);
		this->_data->assets.GetFont("Atarian");

		//_level.setSize(sf::Vector2i(20, 30));
		//_heroAnim = new FlipBook(10);
		//this->_data->playerView.setCenter(sf::Vector2f(PLAYER_VIEW_WIDTH/2, PLAYER_VIEW_HEIGHT/2));
		//this->_data->playerView.zoom(0.5);

		this->_data->playerView.setSize(PLAYER_VIEW_WIDTH, PLAYER_VIEW_HEIGHT);
		//this->_data->playerView.zoom();
		sf::Vector2f playerViewCentre = _data->playerView.getCenter();
		printf("Player View Centre - x[%f] y[%f]!\n", playerViewCentre.x, playerViewCentre.y);
		//system("PAUSE");
		//this->_data->playerView.setCenter(sf::Vector2f((20*16) / 2, (30 * 16) / 2));
		this->_data->playerView.setCenter(sf::Vector2f(240, 240));
		this->_data->window.setView(this->_data->playerView);
		//this->_data->playerView.setCenter(sf::Vector2f( 0, 0));


		_spriteSheet.IndexSpritesheet(this->_data->assets.GetTexture("TestSpritesheet"),
			0, 16);

		_heroSpriteSheet.IndexSpritesheet(this->_data->assets.GetTexture("HeroSpriteSheet"),
			0, 16);

		_enemy1SpriteSheet.IndexSpritesheet(this->_data->assets.GetTexture("Enemy1"), 0, 16);

		printf("SpriteSheet size = %d", _heroSpriteSheet.getSpriteCount());

		//(void)_heroSpriteSheet.getSpriteId(0);

		_level.loadFromFile(LEVEL_FILE1, _spriteSheet);

		//_background.setTexture(this->_data->assets.GetTexture("Game Background"));
		_levelBackground.setTexture(this->_data->assets.GetTexture("GameLevelBackground1"));
		_levelBackground.setScale(sf::Vector2f(2, 2));

		//_hero = new MovementManager(20.0f, -3.0f, sf::Vector2f(2.0f, 2.0f), _heroSpriteSheet.getSpriteId(0), &_level);

		_playerHero = new SpawnableEntity(20.0f, -3.0f, sf::Vector2f(2.0f, 2.0f), &_level, 10, 3);

		FlipBook *tempHeroFlipBook;
		tempHeroFlipBook = _playerHero->getFlipBook();
		//LOADING HERO ANIMATIONS

		tempHeroFlipBook->addSpriteToRow(0, _heroSpriteSheet.getSpriteId(4));
		tempHeroFlipBook->addSpriteToRow(0, _heroSpriteSheet.getSpriteId(5));
		tempHeroFlipBook->addSpriteToRow(0, _heroSpriteSheet.getSpriteId(6));
		tempHeroFlipBook->addSpriteToRow(0, _heroSpriteSheet.getSpriteId(7));

		tempHeroFlipBook->addSpriteToRow(1, _heroSpriteSheet.getSpriteId(8));
		tempHeroFlipBook->addSpriteToRow(1, _heroSpriteSheet.getSpriteId(9));
		tempHeroFlipBook->addSpriteToRow(1, _heroSpriteSheet.getSpriteId(10));
		tempHeroFlipBook->addSpriteToRow(1, _heroSpriteSheet.getSpriteId(11));

		tempHeroFlipBook->addSpriteToRow(2, _heroSpriteSheet.getSpriteId(12));

		tempHeroFlipBook->addSpriteToRow(3, _heroSpriteSheet.getSpriteId(13));

		tempHeroFlipBook->addSpriteToRow(4, _heroSpriteSheet.getSpriteId(0));
		tempHeroFlipBook->addSpriteToRow(4, _heroSpriteSheet.getSpriteId(1));

		tempHeroFlipBook->addSpriteToRow(5, _heroSpriteSheet.getSpriteId(2));
		tempHeroFlipBook->addSpriteToRow(5, _heroSpriteSheet.getSpriteId(3));

		_enemy1 = new SpawnableEntity(20.0f, -3.0f, sf::Vector2f(5.0f, 2.0f), &_level, 10, 6);

		tempHeroFlipBook = _enemy1->getFlipBook();

		for (int i = 0; i < 6; ++i) {
			tempHeroFlipBook->addSpriteToRow(i, _enemy1SpriteSheet.getSpriteId(0));
			tempHeroFlipBook->addSpriteToRow(i, _enemy1SpriteSheet.getSpriteId(1));
			tempHeroFlipBook->addSpriteToRow(i, _enemy1SpriteSheet.getSpriteId(2));
		}	
		
		//_soundBuffer.loadFromFile(GAME_AMBIENT_SOUND);
		//_sound.setBuffer(_soundBuffer);
		//_sound.play();

		_music.openFromFile(GAME_AMBIENT_SOUND);
		_music.setVolume(GAME_VOLUME);
		_music.play();

		_entityMovement = new MovementManager(&_level);
		//_entityMovement->addEntity(20.0f, -3.0f, sf::Vector2f(2.0f, 2.0f), &_level, 10, 3);
		_entityMovement->addEntity(_playerHero);
		_entityMovement->addEntity(_enemy1);
	}

	void GameState::HandleInput(float dt) {
		//printf("Frame Time = %f\n", dt);
		_gotInput = 0;

		if (++animCounter == 6) animCounter = 1;
		//animCounter;

		sf::Event event;

		while (this->_data->window.pollEvent(event)) {

			if (sf::Event::Closed == event.type) {
				this->_data->window.close();
			}
			else if (sf::Event::KeyPressed == event.type) {

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				{
					_playerHero->addEntityVelocity_X(45 * dt);
					//tempMovement->addEntityVelocity_X(1);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					_playerHero->addEntityVelocity_X(-45 * dt);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					if (_playerHero->isOnGronund()) {
						_playerHero->setEntityVelocity_Y(-11.0f);
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					_playerHero->setEntityVelocity_Y(6.0f);
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					//_data->machine.AddState(StateRef(new GameState(_data)), true);
					_data->machine.AddState(StateRef(new PauseMenuState(_data)), false);
					break;
					//_data->machine.ProcessStateChanges();
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
				{
					_playerHero->setEntityVelocity_Y(0.0f);
					_playerHero->setEntityVelocity_X(0.0f);
					_playerHero->setPosition(sf::Vector2f(5.0f, 5.0f));
				}
			}
		}
	}

	void GameState::Update(float dt) {
		//_hero->updatePosition(dt);
		//_playerHero->UpdateEntity(dt);
		//_enemy1->UpdateEntity(dt);
		_entityMovement->updateEntities(dt);

	}

	void GameState::Draw(float dt) {

		this->_data->window.clear();

		/*
		this->_data->playerView.setCenter(sf::Vector2f(_playerHero->getEntitySprite().getPosition().x, 230));
		
		*/
		float pposx = _playerHero->getEntitySprite().getPosition().x;

		if ((pposx - _level.getOrigin().x) < PLAYER_VIEW_WIDTH / 2) {
			this->_data->playerView.setCenter(sf::Vector2f(((PLAYER_VIEW_WIDTH / 2) + _level.getOrigin().x ), 230));
		} else if(((pposx + PLAYER_VIEW_WIDTH / 2) > ( _level.getOrigin().x + _level.getMapSize().x * 16))){
			this->_data->playerView.setCenter(sf::Vector2f(((_level.getOrigin().x + _level.getMapSize().x * 16) - PLAYER_VIEW_WIDTH / 2), 230));
		} else {
			this->_data->playerView.setCenter(sf::Vector2f(_playerHero->getEntitySprite().getPosition().x, 230));
			float pposx = _playerHero->getEntitySprite().getPosition().x;
		}
		
		this->_data->window.setView(_data->playerView);

		//sf::Sprite tempSprite;
		sf::Vector2f tempVec;
		tempVec.x = 0;
		tempVec.y = 0;
		for (int i = 0; i < 14; i++) {
			_levelBackground.setPosition(tempVec);
			this->_data->window.draw(_levelBackground);
			tempVec.x += _levelBackground.getGlobalBounds().width;
		}

		//this->_data->window.draw(_background);
		
		//tempSprite = _spriteSheet.getSpriteId(0);
		//tempSprite.setPosition(sf::Vector2f(20,20));
		_level.DrawLevel(this->_data->window, sf::Vector2i(PLAYER_VIEW_HEIGHT, PLAYER_VIEW_WIDTH));
		//this->_hero->DrawEntity(this->_data->window);
		//this->_playerHero->DrawEntity(this->_data->window);
		//this->_enemy1->DrawEntity(this->_data->window);
		_entityMovement->drawEntities(this->_data->window);
		
		//this->_data->window.draw(tempSprite);
		this->_data->window.display();
	}


}