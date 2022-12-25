
#include<conio.h>
#include<iostream>
#include<fstream>
#include<string>


#include "StringHelperMethods.h"
#include "MergeSort.h"
#include "StretchyArray.h"

using namespace std;


int main() {

	StretchyArray<string> _words = inputWordAndReturnCombos();

	bool _onLeft = false,
		* _isVisible = new bool[_words.size()]{ false };

	int _score = 0,
		_correctness = 0,
		_remainingWords = _words.size(),
		_cursurY = 6;
	
	string _currentWord = "";

	refreshScreen(_words, _isVisible, _onLeft, _score);

	while (_remainingWords > 0) {

		int _key = _getch();

		if (_key == 224) {
			char c = _getch();
			switch (c) {
			case LEFT:
				leftHandler(_onLeft, _cursurY);
				break;
			case TOP:
				topHandler(_onLeft, _cursurY);
				break;
			case RIGHT:
				rightHandler(_onLeft, _cursurY);
				break;
			case BOTTOM:
				bottomHandler(_onLeft, _cursurY, _words.size());
				break;

			}
		}
		else if (_key >= 'a' && _key <= 'z' || _key >= 'A' && _key <= 'Z'){
			cout << char(_key);
			_currentWord += char(_key);
		}
		else if (_key == 13) {
			_correctness = onEnter(_words, _currentWord, _isVisible, _remainingWords,_score, _cursurY, _onLeft);
			refreshScreen(_words, _isVisible, _onLeft, _score);
			showMessage(_correctness);
		}
	}


	return 0;
}