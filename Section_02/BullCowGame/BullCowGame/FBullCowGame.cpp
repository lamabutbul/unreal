#pragma once

#include "FBullCowGame.h"
#include <math.h>
#include <map>
#include <iostream>

#define TMap std::map


using int32 = int;


FBullCowGame::FBullCowGame()
{
    Reset();
}


int32 FBullCowGame::GetMaxTries() const
{
    return MaxTries;
}


int32 FBullCowGame::GetCurrentTry() const
{
    return CurrentTry;
}


int32 FBullCowGame::GetHiddenWordLength() const
{
    return (int32)HiddenWord.length();
}


EWordStatus FBullCowGame::IsValidGuess(FString Guess) const
{
    if (Guess.length() != GetHiddenWordLength())
        return EWordStatus::Wrong_Length;
    
    if (!IsLowercase(Guess))
        return EWordStatus::Not_Lowercase;
    
    if (!IsInsogram(Guess))
        return EWordStatus::Not_Isogram;
    
    return EWordStatus::OK;
}


bool FBullCowGame::HasTriesLeft() const
{
    return CurrentTry <= MaxTries;
}


bool FBullCowGame::IsGameWon() const
{
    return bGameIsWon;
}


FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    FBullCowCount BullCowCount;
    int32 WordLength = GetHiddenWordLength();
    
    for (int32 i = 0; i < WordLength; i++)
    {
        for (int32 j = 0; j < WordLength; j++)
        {
            if (Guess[i] == HiddenWord[j])
            {
                if (i == j)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        CurrentTry++;
    }
    
    return BullCowCount;
}


void FBullCowGame::Reset()
{
    bGameIsWon = false;
    
    const FString HIDDEN_WORD = "planets";
    HiddenWord = HIDDEN_WORD;
    
    MaxTries = CalcMaxTries(HIDDEN_WORD);
    
    CurrentTry = 1;
}


int32 FBullCowGame::CalcMaxTries(FString Word) const
{
    double WordLength = (double)Word.length();
    return ceil(2.0 + ((1 + (WordLength + 1) / 2) * (WordLength + 1) / 2) / 2);
}


bool FBullCowGame::IsInsogram(FString Word) const
{
    TMap<char, bool> SeenLettersMap;
    
    for (char Letter : Word)
    {
        if (!isalpha(Letter))
        {
            return false;
        }
        
        Letter = tolower(Letter);
        
        if (SeenLettersMap[Letter])
        {
            return false;
        }
        else
        {
            SeenLettersMap[Letter] = true;
        }
    }
    
    return true;
}


bool FBullCowGame::IsLowercase(FString Word) const
{
    for (char Letter : Word)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }
    return true;
}
