#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <ctime>
#include <sstream>


const int NUMBEROFWORDS = 3;
void print(std::string, int);

template <typename T>
T StringToNumber(const std::string &Text)//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	std::stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}


int main()
{

	//Set seed
	srand(time(NULL));
	//Populate word list
	std::string wordList[NUMBEROFWORDS];
	std::ifstream File;
	try
	{
		File.open("wordlist.dat");
		if (File.is_open())
		{
			for (int count = 0; count < NUMBEROFWORDS; count++)
			{
				std::getline(File, wordList[count]);
			}
		}
		File.close();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << "\n";
	}
	char sentinel;

	int score=0;
	int compscore=0;
	int savesize = 0;
	std::string* oldwords= NULL;
	//Load game
	std::ifstream SavedGame;
	SavedGame.open("save.dat");
	try
	{
		if (SavedGame.is_open())
		{
			std::string input;

			std::getline(SavedGame, input);
			score = StringToNumber<int>(input);

			std::getline(SavedGame, input);
			compscore = StringToNumber<int>(input);

			std::getline(SavedGame, input);

			savesize = StringToNumber<int>(input);
			oldwords = new std::string[savesize];

			//Fill array;
			for (int count = 0; count < savesize; count++)
			{
				std::getline(SavedGame, oldwords[count]);
			}
		}

		SavedGame.close();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << "\n";
	}



	std::cout << "**************\n   Hangman\n**************\n";
	//Start Menu
	do
	{
		//Pick word
		std::string word = "";
		int index;
		int size;
		while (word == "")
		{
			index = rand() % NUMBEROFWORDS;
			bool newword=true;
			for (int count = 0; count < savesize; count++)
			{
				if (wordList[index] == oldwords[count])
					newword = false;
			}
			if (newword)
				word = wordList[index];
		}
		size = word.length();
		//Start Game
		std::string guesses = "";
		for (int count = 0; count < size; count++)
		{
			std::string temp1;
			if (word[count] != ' '||word[count] != '-')
			{
				temp1 = "_";
				guesses += temp1;
			}
			else
			{
				temp1 = " ";
				guesses += temp1;
			}
				
		}

		int error = 0;
		bool gameover = false;
		while (error<6&&!gameover)
		{
			gameover = true;
			print(guesses, error);
			std::cout << "Make a guess: ";
			char guess;
			std::cin >> guess;


			bool errorflag = true;
			for (int count = 0; count < size; count++)
			{
					if (guess == word[count])
					{
						guesses[count] = guess;
						errorflag = false;
					}
			}
			if (errorflag == true)
				error++;
			for (int count = 0; count < guesses.length(); count++)
			{
				if (guesses[count] == '_')
					gameover = false;
			}
		}
		savesize++;
		//Add word to old words
		std::string* temp = oldwords;
		delete oldwords;
		std::string* oldwords = new std::string[savesize];
		for (int count = 0; count < savesize - 1; count++)
		{
			oldwords[count] = temp[count];
		}
		oldwords[savesize-1] = word;

		if (error < 6)
		{
			print(guesses, error);

			std::cout << "\nYou Won!\n";
			score++;
		}
		else
		{
			print(word.c_str(), error);
			std::cout << "\nYou Lost!\n";
			compscore++;
		}

		std::cout << "Score (You|Comp): " << score << "|" << compscore << "\n";

		//Save game
		std::ofstream SaveGame;
		SaveGame.open("save.dat");

		SaveGame << score << "\n" << compscore << "\n" << (savesize) << "\n";
		for (int count = 0; count < savesize; count++)
		{
			SaveGame << oldwords[count] << "\n";
		}
		SaveGame.close();

		std::cout << "\nDo you wish to continue? Y or N?\n";
		std::cin >> sentinel;

	} while (sentinel == 'y' || sentinel == 'Y');

	delete[] oldwords;
	char tmpe_input;
	std::cout << "\nPress any key and enter to exit.\n";
	std::cin >> tmpe_input;
	return 0;
}

void print( std::string word, int errors=0)
{
	switch (errors)
	{
	case 0:
		std::cout << "\n    _______\n";
		std::cout << "   |/      |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "___|___\n";
		break;
	case 1:
		std::cout << "\n    _______\n";
		std::cout << "   |/      |\n";
		std::cout << "   |      (_)\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "___|___\n";
		break;
	case 2:
		std::cout << "\n    _______\n";
		std::cout << "   |/      |\n";
		std::cout << "   |      (_)\n";
		std::cout << "   |       |\n";
		std::cout << "   |       |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "___|___\n";
		break;
	case 3:
		std::cout << "\n    _______\n";
		std::cout << "   |/      |\n";
		std::cout << "   |      (_)\n";
		std::cout << "   |      \\|\n";
		std::cout << "   |       |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "___|___\n";
		break;
	case 4:
		std::cout << "\n    _______\n";
		std::cout << "   |/      |\n";
		std::cout << "   |      (_)\n";
		std::cout << "   |      \\|/\n";
		std::cout << "   |       |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "___|___\n";
		break;
	case 5:
		std::cout << "\n    _______\n";
		std::cout << "   |/      |\n";
		std::cout << "   |      (_)\n";
		std::cout << "   |      \\|/\n";
		std::cout << "   |       |\n";
		std::cout << "   |      /\n";
		std::cout << "   |\n";
		std::cout << "___|___\n";
		break;
	case 6:
		std::cout << "\n    _______\n";
		std::cout << "   |/      |\n";
		std::cout << "   |      (_)\n";
		std::cout << "   |      \\|/\n";
		std::cout << "   |       |\n";
		std::cout << "   |      / \\\n";
		std::cout << "   |\n";
		std::cout << "___|___\n";
		break;
	default:
		std::cout << "\n    _______\n";
		std::cout << "   |/      |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "   |\n";
		std::cout << "___|___\n";
		break;
	}

	std::cout << "\n";
		
	for (int count = 0; count < word.length(); count++)
	{
		std::cout << word[count] << " ";
	}
	std::cout << "\n";

}