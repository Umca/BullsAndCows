/*The game logic.*/

#pragma once
#include <map>
#include <string>

// to make syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows  = 0;
};

enum class EGuessStatus{
	Invalid_Status,
	OK,
	Not_Isogramm,
	Wrong_Length,
	Not_Lowercase,
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor
	void Reset();
	int32 GetHiddenWordLength() const;
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;
	void SelectWordLength(void) ;
	FBullCowCount SubmitValidGuess(FString Guess);
	void SetHiddenWord();

private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	int32 MyHiddenWordLength;
	//char* MyHiddenWord;
	FString MyHiddenWord; // MUST be an isogram
	bool bGameIsWon;

	bool IsIsogram(FString Guess) const;
	bool IsLowerCase(FString Guess) const;

	//TMap<int32, const char *> MyDictionary{ {3,"ant"},{4,"plan"}, {5,"dragon"}, {6, "elevate"} };
	TMap<int32, FString> MyDictionary{ {3,"ant"},{4,"plan"}, {5,"dragon"}, {6, "elevate"} };
};