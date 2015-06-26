/*
 * ScrabbleWord.h
 *
 *  Created on: 23 Mar, 2015
 *      Author: guillaume
 */

#ifndef SCRABBLE_CHEAT_SRC_SCRABBLEWORD_H_
#define SCRABBLE_CHEAT_SRC_SCRABBLEWORD_H_

#include <string>

class ScrabbleWord {
public:
	ScrabbleWord(std::string wordstr);
	virtual ~ScrabbleWord();

	int CalculateValue();

	int getValue() const {
		return value;
	}

	const std::string& getWord() const {
		return word;
	}

	const std::string& getWordstr() const {
		return wordstr;
	}

	void setWordstr(const std::string& wordstr) {
		this->wordstr = wordstr;
	}

	bool operator<(const ScrabbleWord& a) const { return value > a.value; }

private:
	std::string wordstr;
	std::string word;
	int value;
};

#endif /* SCRABBLE_CHEAT_SRC_SCRABBLEWORD_H_ */
