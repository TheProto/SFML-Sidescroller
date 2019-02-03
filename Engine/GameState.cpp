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

		_level.setSize(sf::Vector2i(20, 30));

		_heroAnim = new FlipBook(10);



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

		printf("SpriteSheet size = %d", _heroSpriteSheet.getSpriteCount());

		//(void)_heroSpriteSheet.getSpriteId(0);

		//LOADING HERO ANIMATIONS
		_heroAnim->addSpriteToRow(0, _heroSpriteSheet.getSpriteId(0));
		_heroAnim->addSpriteToRow(0, _heroSpriteSheet.getSpriteId(1));

		_heroAnim->addSpriteToRow(1, _heroSpriteSheet.getSpriteId(2));
		_heroAnim->addSpriteToRow(1, _heroSpriteSheet.getSpriteId(3));

		_heroAnim->addSpriteToRow(2, _heroSpriteSheet.getSpriteId(4));
		_heroAnim->addSpriteToRow(2, _heroSpriteSheet.getSpriteId(5));
		_heroAnim->addSpriteToRow(2, _heroSpriteSheet.getSpriteId(6));
		_heroAnim->addSpriteToRow(2, _heroSpriteSheet.getSpriteId(7));

		_heroAnim->addSpriteToRow(3, _heroSpriteSheet.getSpriteId(8));
		_heroAnim->addSpriteToRow(3, _heroSpriteSheet.getSpriteId(9));
		_heroAnim->addSpriteToRow(3, _heroSpriteSheet.getSpriteId(10));
		_heroAnim->addSpriteToRow(3, _heroSpriteSheet.getSpriteId(11));

		_heroAnim->addSpriteToRow(4, _heroSpriteSheet.getSpriteId(12));

		_heroAnim->addSpriteToRow(5, _heroSpriteSheet.getSpriteId(13));

		_level.loadFromFile(LEVEL_FILE1, _spriteSheet);

		//_background.setTexture(this->_data->assets.GetTexture("Game Background"));
		_levelBackground.setTexture(this->_data->assets.GetTexture("GameLevelBackground1"));
		_levelBackground.setScale(sf::Vector2f(2, 2));

		_hero = new MovementManager(20.0f, -3.0f, sf::Vector2f(2.0f, 2.0f), _heroSpriteSheet.getSpriteId(0), &_level);

		//_soundBuffer.loadFromFile(GAME_AMBIENT_SOUND);
		//_sound.setBuffer(_soundBuffer);
		//_sound.play();

		_music.openFromFile(GAME_AMBIENT_SOUND);
		_music.setVolume(GAME_VOLUME);
		_music.play();

	}

	void GameState::HandleInput(float dt) {
		printf("Frame Time = %f\n", dt);
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
					_gotInput = 1;
					_hero->addEntityVelocity_X(45 * dt);
					_goingRight = 1;
					if (animCounter == 5) {
						_hero->setSprite(_heroAnim->requestSpriteByRow(2));
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				{
					_gotInput = 1;
					_hero->addEntityVelocity_X(-45 * dt);
					_goingRight = 0;
					if (animCounter == 5) {
						_hero->setSprite(_heroAnim->requestSpriteByRow(3));
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				{
					_gotInput = 1;
					_hero->setEntityVelocity_Y(-6.0f);
					if (animCounter == 5) {
						if (_goingRight) {
							_hero->setSprite(_heroAnim->requestSpriteByRow(4));
							animCounter = 1;
						}
						else {
							_hero->setSprite(_heroAnim->requestSpriteByRow(5));
							animCounter = 1;
						}
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				{
					_gotInput = 1;
					_hero->setEntityVelocity_Y(6.0f);
					if (animCounter == 5) {
						if (_goingRight) {
							_hero->setSprite(_heroAnim->requestSpriteByRow(0));
						}
						else {
							_hero->setSprite(_heroAnim->requestSpriteByRow(1));
						}
					}
				}

			}
		}
	}

	void GameState::Update(float dt) {
		_hero->updatePosition(dt);

	}

	void GameState::Draw(float dt) {

		this->_data->window.clear();

		this->_data->playerView.setCenter(sf::Vector2f(_hero->getSprite().getPosition().x, 195));
		this->_data->window.setView(_data->playerView);

		//sf::Sprite tempSprite;
		sf::Vector2f tempVec;
		tempVec.x = 0;
		tempVec.y = 0;
		for (int i = 0; i < 2; i++) {
			_levelBackground.setPosition(tempVec);
			this->_data->window.draw(_levelBackground);
			tempVec.x += _levelBackground.getGlobalBounds().width;
		}

		//this->_data->window.draw(_background);
		
		//tempSprite = _spriteSheet.getSpriteId(0);
		//tempSprite.setPosition(sf::Vector2f(20,20));
		_level.DrawLevel(this->_data->window, sf::Vector2i(PLAYER_VIEW_HEIGHT, PLAYER_VIEW_WIDTH));
		this->_hero->DrawEntity(this->_data->window);
		
		//this->_data->window.draw(tempSprite);
		this->_data->window.display();
	}


}