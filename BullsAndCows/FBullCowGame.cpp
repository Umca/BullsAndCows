#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <math.h> 

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

int FBullCowGame::GetMaxTries() const { 
	//TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,5}, {5,5}, {6, 5} };
	//return WordLengthToMaxTries[MyHiddenWord.length()]; 
	return (int)ceil(MyHiddenWordLength * 1.5);
}

int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWordLength; }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

// receives valided guess, increments current guess and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	for (int32 i = 0; i < MyHiddenWordLength; i++) {
		for (int32 j = 0; j < MyHiddenWordLength; j++) {
			if (MyHiddenWord[i] == Guess[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == MyHiddenWordLength) {
		bGameIsWon = true;
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{

	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess ) {
		Letter = tolower(Letter);
		if (!LetterSeen[Letter]) {
			LetterSeen[Letter] = true;
		} else {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	if (!Guess.length()) return false;
	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

void FBullCowGame::SetHiddenWord()
{
	const FString HIDDEN_WORD = MyDictionary[MyHiddenWordLength];
	MyHiddenWord = HIDDEN_WORD;
	//MyHiddenWord = (char *)std::malloc(sizeof(char) * MyHiddenWordLength + 1);
	//strcpy_s(MyHiddenWord, MyHiddenWordLength + 1, MyDictionary[MyHiddenWordLength]);
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogramm;
	}
	if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

void FBullCowGame::SelectWordLength(void) {
	FString sLen = "";
	do {
		std::cout << "Please, select the length of hidden word from the range of 3 to 7. ";
		std::getline(std::cin, sLen);
	} while (std::stoi(sLen) > 7 || std::stoi(sLen)< 3);
	
	MyHiddenWordLength = std::stoi(sLen);
}
