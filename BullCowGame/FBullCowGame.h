/*
The game logic (no view code or direct user interaction).
The game is a simple gues the word game based on Mastermind.
*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

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

enum class ELengthStatus
{
	Invalid_Status,
	OK,
	Not_Int,
	Not_In_Range
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	ELengthStatus CheckLengthValidity(int32) const;

	void Reset();
	void SetHiddenWord(int32);
	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
};