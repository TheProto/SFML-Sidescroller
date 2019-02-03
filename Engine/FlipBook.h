#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>

namespace ProtoEngine {
	class FlipBook
	{
	public:
		FlipBook(int rows);
		~FlipBook();

		//int addSpriteRow();
		int addSpriteToRow(int row_id, sf::Sprite sp);
		
		sf::Sprite requestSpriteByRow(int row_id);

	 private:

		int _currentRow;
		int _currentSpriteIndex;

		int _rowCount;
		int _maxRows;

		std::vector<std::vector<sf::Sprite>> _spArray;
	};
}

