/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
MASTER */

#pragma once

#include <iostream>
#include <string>	
#include "FBullCowGame.h"


// to make syntax unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
int32 GetUWordLength();

FBullCowGame BCGame;

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);

	return 0; // exit the application
}
 
void PrintIntro()
{
	//ASCII art would go here if I could do it or cared...

	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n\n";
	//std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	//std::cout << " letter isogram that I'm thinking of?\n";
	std::cout << "First we will ask for your preferred difficulty!\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();

	int32 uWordLength = GetUWordLength();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
				
		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary(); 
	

	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You won in " << BCGame.GetCurrentTry() - 1 << " tries with the guess \"" << BCGame.GetHiddenWord() << "\".\n";
	} else
	{
		std::cout << "Wah Wah. Better luck next time. ; _ ;\n";
	}

	return;
}

int32 GetUWordLength() {
	int32 uWordLength;
	ELengthStatus LengthStatus = ELengthStatus::Invalid_Status;
	std::cout << "Please enter a number between, and including, 3 to 7 to pick word length and difficulty: ";
	do {
		std::cin >> uWordLength;
		LengthStatus = BCGame.CheckLengthValidity(uWordLength);
		if (LengthStatus == ELengthStatus::Not_In_Range) {
			std::cout << "Please try again. The number must be either 3, 4, 5, 6, or 7: ";
		}
	} while (LengthStatus != ELengthStatus::OK);
	BCGame.SetHiddenWord(uWordLength);

	std::cout << std::endl << "Thank you! You have " << BCGame.GetMaxTries() << " tries!" << "\n\n";

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return uWordLength;
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
