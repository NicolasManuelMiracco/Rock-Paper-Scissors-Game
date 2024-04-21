#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>

// Define highlighting function for different platforms
#if defined(_WIN32)
#include <windows.h>
void highlightText(const std::string& text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    std::cout << text;
    SetConsoleTextAttribute(hConsole, 7); // Reset color
}
#else
// For other platforms, you might need to use escape sequences or libraries like ncurses
void highlightText(const std::string& text) {
    std::cout << "\033[1;32m" << text << "\033[0m";
}
#endif

using namespace std;

// Function to get user's choice
int getUserChoice() {
    int userChoice;
    while (true) {
        cout << "1) Rock\n2) Paper\n3) Scissors\n";
        cin >> userChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number (1-3).\n";
        } else if (userChoice >= 1 && userChoice <= 3) {
            return userChoice;
        } else {
            cout << "Invalid choice. Enter 1, 2, or 3.\n";
        }
    }
}

// Function to get computer's choice
int getComputerChoice() {
    return rand() % 3 + 1;
}

// Function to determine the winner
string determineWinner(int userChoice, int computerChoice) {
    if (userChoice == computerChoice) {
        return "Tie";
    } else if ((userChoice == 1 && computerChoice == 3) ||
               (userChoice == 2 && computerChoice == 1) ||
               (userChoice == 3 && computerChoice == 2)) {
        return "User";
    } else {
        return "Computer";
    }
}

int main() {
    srand(time(NULL));
    int rounds, userScore, computerScore;

    while (true) {
        cout << "Welcome to Rock Paper Scissors!\n";
  
        // Validate number of rounds
        while (true) {
            cout << "Enter number of rounds (1-9): ";
            if (cin >> rounds && rounds > 0 && rounds < 10) {
                break;
            } else {
                cout << "Invalid input. Please enter a number between 1 and 9.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
      
        userScore = 0;
        computerScore = 0;
        
        for (int i = 0; i < rounds; i++) {
            cout << "\nRound " << i + 1 << ":\n";
            int userChoice = getUserChoice();
            int computerChoice = getComputerChoice();
            string result = determineWinner(userChoice, computerChoice);
        
            // Keep playing and updating the score until there's a winner in the round
            while (result == "Tie") {
                cout << "It's a tie! Replay the round.\n";
                userChoice = getUserChoice();
                computerChoice = getComputerChoice();
                result = determineWinner(userChoice, computerChoice);
            }
        
            // Now that we're out of the tie, update the score
            if (result == "User") {
                userScore++;
            } else if (result == "Computer") {
                computerScore++;
            }
        
            cout << "Result: " << result << endl;
            cout << "Current Score: User - " << userScore << " | Computer - " << computerScore << endl;
        }

        // Handle ties for even number of rounds
        while (userScore == computerScore && rounds % 2 == 0) {
            do {
                cout << "\nIt's a tie overall! Playing an extra round to determine the winner:\n";
                rounds++; // Increment rounds count to reflect the extra round
  
                // Play an extra round and update scores within this loop
                cout << "\nRound " << rounds << ":\n";
                int userChoice = getUserChoice();
                int computerChoice = getComputerChoice();
                string result = determineWinner(userChoice, computerChoice);
  
                if (result == "User") {
                    userScore++;
                } else if (result == "Computer") {
                    computerScore++;
                }
  
                cout << "Result: " << result << endl;
                cout << "Current Score: User - " << userScore << " | Computer - " << computerScore << endl;
            } while (userScore == computerScore); // Keep looping while scores are tied
        }

        cout << "\nFinal Score: User - " << userScore << " | Computer - " << computerScore << endl;
  
        if (userScore > computerScore) {
            // Special message for the user winning
            highlightText("Congratulations! ");
            cout << "You've outplayed the computer and won the game!\n";
        } else {
            highlightText("Computer wins the game!\n");
        }
  
        // Validate play again input
        while (true) {
            char playAgain;
            cout << "Play again? (y/n): ";
            cin >> playAgain;
            if (tolower(playAgain) == 'y') {
                break;
            } else if (tolower(playAgain) == 'n') {
                return 0; // Exit the game
            } else {
                cout << "Invalid input. Please enter 'y' or 'n'.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    return 0;
}