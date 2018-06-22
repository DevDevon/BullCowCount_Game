#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values intialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetChosenWord() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void GetHiddenWord(int32);
	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
};