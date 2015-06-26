//============================================================================
// Name        : scrabble_cheater.cpp
// Author      : Guillaume Militello
// Description : Scrabble Cheat in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>

#include "ScrabbleWord.h"

using namespace std;

struct wordscr
{
	string wordstr;
	int points;
};

bool createDic(string dicname, vector<ScrabbleWord> *dicvect)
{
	try
	{
		ifstream dicfile;
		string word_tmp;
		clock_t start = clock();

		cout << "Creating dic... ";
		dicfile.open(dicname);

		if (dicfile.is_open())
		{

			while (getline(dicfile, word_tmp))
			{
				// fill the vector
				dicvect->push_back(ScrabbleWord(word_tmp));
			}
		}
		dicfile.close();
		cout << "done [" << (clock() - start)/ (double) CLOCKS_PER_SEC*1000 << "ms]" << endl;
		return true;

	}
	catch (exception const& e)
	{
		cout << "Unable to open the dic file " << dicname << endl;
		return false;
	}
}

bool checkCharacters(string str)
{

	for (string::iterator it = str.begin(); it < str.end(); ++it)
	{

		if (*it < 'A' || *it > 'z' || (*it > 'Z' && *it < 'a'))
			return false;
	}
	return true;
}
bool checkCharactersFitting(string str)
{

	for (string::iterator it = str.begin(); it < str.end(); ++it)
	{

		if (*it == '$' || *it == '.')
			continue;
		if (*it < 'A' || *it > 'z' || (*it > 'Z' && *it < 'a'))
			return false;
	}
	return true;
}

void syntaxCharactersFitting(string *pstr)
{

	size_t start_pos = 0;
	while ((start_pos = pstr->find("$", start_pos)) != string::npos)
	{
		pstr->replace(start_pos, 1, ".*");
		start_pos += 2;
	}
}

bool AnalyseWord(string word, string inputchar)
{

	if (word.length() > inputchar.length())
		return false;

	// parsing word letters
	for (int k = 0; k < word.length(); k++)
	{

		bool contain = false;

		// analyzing letter one by one
		for (int c = 0; c < inputchar.length(); c++)
		{

			if (word.at(k) == inputchar.at(c))
			{
				contain = true;
				inputchar.erase(c, 1);
				break;
			}
		}
		if (!contain)
			return false;
	}
	return true;
}

vector<ScrabbleWord> AnalyseDic(vector<ScrabbleWord> diclist, string inputchar, string inputfit)
{
	vector<ScrabbleWord> wordlist;

	for (int i = 0; i < diclist.size(); i++)
	{
		// analyzing word one by one
		if (AnalyseWord(diclist.at(i).getWord(), inputchar) &&
				regex_match(diclist.at(i).getWord(), (regex) inputfit))
		{
			wordlist.push_back(diclist.at(i));
		}
	}
	return wordlist;
}

void showConsole(vector<ScrabbleWord> wordlist)
{
	if (wordlist.size() == 0)
		cout << "No results" << endl;
	else
	{
		int index = 0;
		for (int i = 0; i < wordlist.size(); i++)
		{
			if (i == 0 || wordlist.at(i).getValue() != wordlist.at(i - 1).getValue())
			{
				cout << "[" << wordlist.at(i).getValue() << "]";
			}
			if (i != wordlist.size() - 1 && wordlist.at(i).getValue() == wordlist.at(i + 1).getValue())
			{
				cout << "[" << wordlist.at(i).getWord() << "]";
			}
			else
			{
				cout << "[" << wordlist.at(i).getWord() << "]" << endl;
				index++;
			}
			if (index == 10)
				break;
		}
	}
}

int main(int argc, char *argv[])
{
	string dicname = "./dic/french.txt";

	vector<ScrabbleWord> dicvect;
	vector<ScrabbleWord> wordvect;

	string inputchar, inputfit;

	if(argc >= 2)
		dicname = argv[1];

	// run loop control
	int run = 1;

		while (!createDic(dicname, &dicvect))
		{
			// catch user input
			cout << "Dic file : ";
			cin >> dicname;
		}

	// run
	while (run == 1)
	{

		// catch user input
		cout << "Available Letters [a-z] : ";
		cin >> inputchar;
		while (!checkCharacters(inputchar))
		{
			cout << "Possible characters [a-z/A-Z] : ";
			cin >> inputchar;
		}
		cout << "Special Fitting [$/.] : ";
		cin >> inputfit;
		while (!checkCharactersFitting(inputfit))
		{
			cout << "Possible characters [a-z/A-Z/$/.] : ";
			cin >> inputchar;
		}

		// syntax '$' = '.*'
		syntaxCharactersFitting(&inputfit);

		// analyze word
		wordvect = AnalyseDic(dicvect, inputchar, inputfit);

		// sort the results
		sort(wordvect.begin(), wordvect.end());

		// print the results
		showConsole(wordvect);

		// search done
		run = -1;
		wordvect.erase(wordvect.begin(), wordvect.end());

		// runtime continue
		while (run == -1)
		{
			cout << "Continue [Y/N] : ";
			cin >> inputchar;
			if (!inputchar.compare("Y"))
				run = 1;
			else if (!inputchar.compare("N"))
				run = 0;
			else
				run = -1;
		}
	}
	return 0;
}
