#include <iostream>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBullsAndCows(FBullCowCount BullCowCount);
void PrintSummary();
bool AskToPlayAgain();


FBullCowGame BCGame;


int main()
{
    do
    {
        PrintIntro();
        PlayGame();
    }
    while (AskToPlayAgain());
    return 0;
}


void PrintIntro()
{
    std::cout << "    ,           ,                               " << std::endl;
    std::cout << "   /             \\           ,/         \\,    " << std::endl;
    std::cout << "  ((__-^^-,-^^-__))         ((__,-\"\"\"-,__))  " << std::endl;
    std::cout << "   `-_---' `---_-'           `--)~   ~(--`      " << std::endl;
    std::cout << "    <__|o` 'o|__>           .-'(       )`-,     " << std::endl;
    std::cout << "       \\  `  /              `~~`d\\   /b`~~`   " << std::endl;
    std::cout << "        ): :(                   |     |         " << std::endl;
    std::cout << "        :o_o:                   (6___6)         " << std::endl;
    std::cout << "         \"-\"      Welcome to     `---`        " << std::endl;
    std::cout << "                                                " << std::endl;
    std::cout << "             BULLS   and   COWS                 " << std::endl;
    
    std::cout << "\nCan you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
}


void PlayGame()
{
    BCGame.Reset();
    
    FText Guess;
    FBullCowCount BullCowCount;
    
    do
    {
        Guess = GetValidGuess();
        BullCowCount = BCGame.SubmitValidGuess(Guess);
        PrintBullsAndCows(BullCowCount);
        
        std::cout << std::endl;
    } while (!BCGame.IsGameWon() && BCGame.HasTriesLeft());
    
    PrintSummary();
}


FText GetValidGuess()
{
    FText Guess = "";
    EWordStatus WordStatus = EWordStatus::Invalid_Status;
    int32 MaxTries = BCGame.GetMaxTries();
    
    do
    {
        std::cout << "Try " << BCGame.GetCurrentTry() << " of " << MaxTries << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        WordStatus = BCGame.IsValidGuess(Guess);
        
        switch (WordStatus)
        {
            case EWordStatus::Wrong_Length:
                std::cout << "The guess is not " << BCGame.GetHiddenWordLength() << " characters long." << std::endl;
                break;
                
            case EWordStatus::Not_Isogram:
                std::cout << "The guess is not an insogram." << std::endl;
                break;
                
            case EWordStatus::Not_Lowercase:
                std::cout << "The guess is not in lower case." << std::endl;
                break;
                
            default:
                break;
        }
    }
    while (WordStatus != EWordStatus::OK);
    
    return Guess;
}


void PrintBullsAndCows(FBullCowCount BullCowCount)
{
    std::cout << "Bulls: " << BullCowCount.Bulls << std::endl;
    std::cout << "Cows:  " << BullCowCount.Cows << std::endl;
}


void PrintSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "You won in " << BCGame.GetCurrentTry() << " tries!";
    }
    else
    {
        std::cout << "You lost :( Better luck next time!";
    }
    
    std::cout << std::endl << std::endl;
}


bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word (y/n)? ";
    FText Response;
    getline(std::cin, Response);
    std::cout << std::endl;
    return (Response[0] == 'y' || Response[0] == 'Y');
}
