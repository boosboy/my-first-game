#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char playerMarker, computerMarker;
int currentPlayer;

void drawBoard() {
    cout << "Player (X) - Computer (O)" << endl;
    cout << "     |     |     \n";
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "  \n";
    cout << "     |     |     \n";
}

bool placeMarker(int slot, char marker) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = marker;
        return true;
    }
    return false;
}

int winner() {
    // Rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return currentPlayer;
        }
    }

    // Columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return currentPlayer;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return currentPlayer;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return currentPlayer;
    }

    return 0;
}

void computerMove() {
    srand(time(0)); // Seed for random number generation

    int slot;
    bool validMove = false;

    while (!validMove) {
        slot = rand() % 9 + 1; // Generate random number between 1 and 9
        validMove = placeMarker(slot, computerMarker);
    }

    cout << "Computer placed marker at slot " << slot << endl;
}

void game() {
    cout << "You are Player X. The computer is Player O." << endl;

    playerMarker = 'X';
    computerMarker = 'O';
    currentPlayer = 1;

    drawBoard();
    int playerWon;

    for (int i = 0; i < 9; i++) {
        if (currentPlayer == 1) {
            cout << "It's your turn. Enter a slot: ";
            int slot;
            cin >> slot;

            if (slot < 1 || slot > 9) {
                cout << "Invalid slot! Try again.\n";
                i--;
                continue;
            }

            if (!placeMarker(slot, playerMarker)) {
                cout << "Slot already taken! Try again.\n";
                i--;
                continue;
            }
        } else {
            computerMove();
        }

        drawBoard();

        playerWon = winner();

        if (playerWon == 1) {
            cout << "Congratulations! You won!\n";
            break;
        } else if (playerWon == 2) {
            cout << "Computer won! Better luck next time!\n";
            break;
        
        }

        // Swap turns between player and computer
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

    if (playerWon == 0) {
        cout << "It's a tie!\n";
    }
}

int main() {
    game();
    return 0;
}
