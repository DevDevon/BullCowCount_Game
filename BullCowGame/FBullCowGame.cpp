#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
FString FBullCowGame::GetChosenWord() const { return MyHiddenWord; }

void FBullCowGame::GetHiddenWord(int32 Difficulty) {
	TMap<int32, FString> HiddenWordList{ {1, "are"}, {2, "scale"}, {3, "planets"} };
	MyHiddenWord = HiddenWordList[Difficulty];

	return;
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{5,5},{7,6} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	//const FString HIDDEN_WORD = "planet";
	//MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsLowercase(FString Guess) const {
	for (auto& i : Guess) { //loop through Guess checking if lowercase
		if (!islower(i)) { //if current char is not a lowercase letter, break the loop and notify the player
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	//treat 0 and 1 letter words as isograms
	if (Guess.length() <= 1) { return true;	}

	//setup our map
	TMap<char, bool> LetterSeen;

	//loop through guess until we have reached guess word length
	for (auto Letter : Guess) //for all letters of the guess
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) //if the letter is in the map
		{
			return false; //we do NOT have an isogram
		} else 
		{
			LetterSeen[Letter] = true; //add the letter to the map as seen
		}
	}
	return true; //example: where \0 is entered
}
