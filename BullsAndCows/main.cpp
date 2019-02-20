/* This is the console executable, that makes use of the BullCoq class.
For game logic see FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using int32 = int;
using FText = std::string;

void PrintIntro(void);
void PlayGame(void);
FText GetValidGuess(void);
bool AskToPlayAgain(void);
void PrintGameSummary(void);

FBullCowGame BCGame; // instantiate a new game

int main(void)
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0;
}

void PrintIntro(void) {
	std::cout << "\nWelcome to Bulls and Cows - a fun word game." << std::endl;
	BCGame.SelectWordLength();
	BCGame.SetHiddenWord();
	std::cout << "Can u guess " << BCGame.GetHiddenWordLength() << " letter isogram I`m thinking of?\n";
	std::cout << "\n";
	return;
}

void PlayGame(void){
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while ((BCGame.GetCurrentTry() <= MaxTries) && !BCGame.IsGameWon()) {
		FText Guess = "";
		Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls << " Cows: " << BullCowCount.Cows << "\n\n";
	};
	PrintGameSummary();
	return;
}

FText GetValidGuess(void) {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry <<" of " <<BCGame.GetMaxTries() <<". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Pease enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogramm:
			std::cout << "Pease enter a world without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Pease enter all lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status != EGuessStatus::OK);
	
	return Guess;
}

bool AskToPlayAgain(void) {
	FText Response = "";

	std::cout << "Do u want to play again with the same word? (y/n)";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary(void) {
	if (BCGame.IsGameWon()) {
		std::cout << "Congrats! U won!\n";
	}
	else {
		std::cout << "Do not be sad! Try your luck next time. :)\n";
	}
}
