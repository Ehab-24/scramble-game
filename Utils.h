#pragma once

#include<fstream>
#include<iostream>
#include<string>
#include"StretchyArray.h"
#include<Windows.h>

#define BLACK 0
#define BROWN 6
#define GREY 7
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9
#define BLUE 1


using namespace std;

enum {
	LEFT = 'K',
	TOP = 'H',
	RIGHT = 'M',
	BOTTOM = 'P'
};


void setColor(int tcl, int bcl = 0)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}


void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}


void cursurPos(int x, int y)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = x;
	scrn.Y = y;
	SetConsoleCursorPosition(hOuput, scrn);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

StretchyArray<string> loadDictionary(ifstream& fin) {

	int size;
	fin >> size;

	StretchyArray<string> dictionary(size);

	for (int i = 0; i < size; i++) {
		fin >> dictionary[i];
	}

	return dictionary;
}

///////////////////////////////////////////////////////////////////////////////////////////


void printWords(StretchyArray<string>& words, bool* isVisible) {

	cursurPos(0, 5);
	for (int i = 0; i < words.size(); i++) {
		cout << i + 1 << "\t";
		if (isVisible[i]) {
			cout << words[i];
		}
		else {
			for (int j = 0; j < words[i].size(); j++) {
				cout << "*";
			}
		}
		cout << "\n";
	}
}

void printGuess() {
	cursurPos(90, 5);
	cout << "Guess:\n";
	cursurPos(90, 6);
}

void displayScore(int score) {

	setColor(WHITE);
	cursurPos(90, 2);
	cout << "Score: " << score;
	setColor(GREY);
}

void header() {

	cout << "\t\t\t\t\t\t  welcome to\n\t\t\t\t\t\tWORD SCRAMBLE\n";
}

void refreshScreen(StretchyArray<string>&words, bool*isVisible, bool &onLeft, int score) {

	onLeft = false;
	
	system("cls");

	printWords(words, isVisible);

	displayScore(score);

	printGuess();

}

/*	~	~	~	~	~	~	~	~	~	~	~	~	~	*/

void topHandler(bool onLeft, int &cursurY) {
	if (onLeft) {
		if (cursurY > 5) {
			cursurY--;
			cursurPos(0, cursurY);
		}
	}
}
void bottomHandler(bool onLeft, int& cursurY, int noOfWords) {
	if (onLeft) {
		if (cursurY < 5 + noOfWords) {
			cursurY++;
			cursurPos(0, cursurY);
		}
	}
}
void leftHandler(bool &onLeft, int &yPos) {
	if (!onLeft) {
		onLeft = true;
		yPos = 5;
		cursurPos(0, yPos);
	}
}
void rightHandler(bool& onLeft, int &yPos) {
	if (onLeft) {
		onLeft = false;
		yPos = 6;
		cursurPos(90, yPos);
	}
}

//Returns whether the guess was correct or not.
int onEnter(StretchyArray<string>& words, string& currentWord, bool* isVisible, int &remaingWords, int& score, int yPos, bool onLeft) {

	if (onLeft) {
		if (isVisible[yPos - 5]) {
			return 2;
		}
		isVisible[yPos - 5] = true;
		remaingWords--;
		score += -2;
	}
	else {
		for (int i = 0; i < words.size(); i++) {
			
			if (currentWord == words[i]) {
				if (isVisible[i]) {
					currentWord = "";
					return 2;
				}
				isVisible[i] = true;
				currentWord = "";
				remaingWords--;
				score += 5;
				return 3;
			}
		}
		currentWord = "";
		return 1;
	}

	return 0;
}

void showMessage(int validity) {

	string _message = "";

	if (validity == 3) {
		setColor(GREEN);
		_message = "Correct!";
	}
	else if(validity == 2){
		setColor(LBLUE);
		_message = "Already Guessed!";

	}
	else if (validity == 1) {
		setColor(RED);
		_message = "Wrong Guess!";
	}
	else {
		setColor(BROWN);
		_message = "Try Harder!";
	}

	cursurPos(90, 15);
	cout << _message;

	cursurPos(90, 6);

	setColor(GREY);
}