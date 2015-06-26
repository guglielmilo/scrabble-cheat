/*
 * ScrabbleWord.cpp
 *
 *  Created on: 23 Mar, 2015
 *      Author: guillaume
 */

#include "ScrabbleWord.h"

ScrabbleWord::ScrabbleWord(std::string wordstr) {

	this->word = wordstr;
	this->value = CalculateValue();
}

ScrabbleWord::~ScrabbleWord() {

}

int ScrabbleWord::CalculateValue(){
		int points = 0;
		for (int i = 0; i < this->word.length(); i++)
			switch (this->word.at(i)) {
			case 'e':
			case 'a':
			case 'i':
			case 'n':
			case 'o':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'l':
				points += 1;
				break;
			case 'd':
			case 'm':
			case 'g':
				points += 2;
				break;
			case 'b':
			case 'c':
			case 'p':
				points += 3;
				break;
			case 'f':
			case 'h':
			case 'v':
				points += 4;
				break;
			case 'j':
			case 'q':
				points += 8;
				break;
			case 'k':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
				points += 10;
				break;
			}
		return points;
	}
