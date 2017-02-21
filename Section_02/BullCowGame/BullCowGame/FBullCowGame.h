#pragma once

#include <string>

using FString = std::string;
using int32 = int;


struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};


enum class EWordStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
};


class FBullCowGame
{
public:
    FBullCowGame();
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    EWordStatus IsValidGuess(FString Guess) const;
    bool IsGameWon() const;
    bool HasTriesLeft() const;
    
    void Reset();
    
    FBullCowCount SubmitValidGuess(FString Guess);
    
    
private:
    int32 MaxTries;
    int32 CurrentTry;
    FString HiddenWord;
    bool bGameIsWon;
    
    int32 CalcMaxTries(FString Word) const;
    bool IsInsogram(FString Word) const;
    bool IsLowercase(FString Word) const;
};
