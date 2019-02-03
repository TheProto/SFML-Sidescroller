#include "FlipBook.h"

namespace ProtoEngine {


	FlipBook::FlipBook(int rows) {
		_spArray.resize(rows);
		_currentSpriteIndex = 0;
		_currentRow = 0;
		_maxRows = rows;
	}
	
	FlipBook::~FlipBook() {
	
	}

	/*
	int FlipBook::addSpriteRow() {
		
	}
	*/

	int FlipBook::addSpriteToRow(int row_id, sf::Sprite sp) {
		printf("addingSpritetoRow = %d\n", row_id);
		_spArray[row_id].push_back(sp);
		return 0;
	}

	sf::Sprite FlipBook::requestSpriteByRow(int row_id) {

		if (row_id > _maxRows) {
			printf("requested an invalid sprite row = %d\n", row_id);
		}

		if (_currentSpriteIndex < _spArray[row_id].size() - 1) {
			return _spArray[row_id][_currentSpriteIndex++];
		}
		else {
			_currentSpriteIndex = 0;
			return _spArray[row_id][_currentSpriteIndex++];
		}

		/*
		if (row_id = _currentRow) {
			if (_currentSpriteIndex < _spArray.size() - 1) {
				return _spArray[row_id][_currentSpriteIndex++];
				//_currentSpriteIndex++;
			}
			else {
				_currentSpriteIndex = 0;
				return _spArray[row_id][_currentSpriteIndex++];
				
				printf("Requested out of bound sprite - 1 \n");
			}
		}
		else {
			_currentSpriteIndex = 0;
			_currentRow = row_id;
			if (_currentSpriteIndex < _spArray.size() - 1) {
				return _spArray[_currentRow][_currentSpriteIndex++];
			}
			else {
				printf("Requested out of bound sprite - 2 \n");
			}
		}
		*/
	}

}