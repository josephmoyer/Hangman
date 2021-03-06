#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <ctime>


const int NUMBEROFWORDS = 32153;
void print(std::string, int);
int main()
{

	//Set seed
	srand(time(NULL));
	//Populate word list
	std::string wordList[NUMBEROFWORDS];
	std::ifstream File;
	File.open("wordlist.dat");
	if (File.is_open())
	{
		for (int count = 0; count < NUMBEROFWORDS; count++)
		{
			std::getline(File, wordList[count]);
		}
	}
	File.close();
	char sentinel;

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
			word = wordList[index];
		}
		size = word.length();
		//Start Game
		std::string guesses = "";
		for (int count = 0; count < size; count++)
		{
			std::string temp1;
			if (word[count] != ' ')
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

		if (error < 6)
		{
			print(guesses, error);

			std::cout << "\nYou Won!\n";
		}
		else
		{
			print(word.c_str(), error);
			std::cout << "\nYou Lost!\n";
		}

		std::cout << "Do you wish to continue? Y or N?\n";
		std::cin >> sentinel;

	} while (sentinel == 'y' || sentinel == 'Y');


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
