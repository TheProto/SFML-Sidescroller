#include "InputManager.h"

namespace ProtoEngine
{
	InputManager::InputManager() {
	}
	
	InputManager::~InputManager() {
	}

	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window) {

		if (sf::Mouse::isButtonPressed(button)) {
			sf::IntRect tempRect(object.getPosition().x, object.getPosition().y,
				object.getGlobalBounds().width, object.getGlobalBounds().height);
			
			//Used to make the function work with views!!!!
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			if (tempRect.contains(worldPos.x, worldPos.y)) {
				return true;
			}	
		}
		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window) {
		return sf::Mouse::getPosition( window );
	}
}
