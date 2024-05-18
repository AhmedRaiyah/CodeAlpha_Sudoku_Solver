#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

const int boardSize = 9;

// number of hints based on difficulty
const int easy = 15;
const int normal = 10;
const int hard = 5;



void topScreen() {
    for (int i = 0; i < 120; i++) {
        cout << "~";
    }
    cout << endl;
}

void mainScreen() {
    topScreen();
    cout << "\t\t\t\t\t  " << "=========================================" << endl
        << "\t\t\t\t\t\t\t" << "Sudoku Solver" << endl
        << "\t\t\t\t\t  " << "=========================================" << endl;
}

bool checkNumEntered(int sudokuBoard[boardSize][boardSize], int row, int col, int userEntry) {
    for (int i = 0; i < boardSize; i++) {
        if (sudokuBoard[row][i] == userEntry) return false;
    }

    for (int i = 0; i < boardSize; i++) {
        if (sudokuBoard[i][col] == userEntry) return false;
    }

    int boxRowStart = row - row % 3;
    int boxColStart = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudokuBoard[i + boxRowStart][j + boxColStart] == userEntry) return false;
        }
    }

    return true;
}

void printSudoku(int singleBox[boardSize][boardSize]) {
    system("cls");
    mainScreen();

    cout << "\n\n" << "\t\t\t\t\t   " << "=========================================" << endl;
    for (int i = 0; i < boardSize; i++) { // loop for rows
        if (i == 0)
            cout << "\t\t\t\t\t   ";
        for (int j = 0; j < boardSize; j++) { // loop for columns
            if (j == 3 || j == 6)
                cout << "  ||   ";
            cout << " " << singleBox[i][j] << " ";
        }

        if (i == 2 || i == 5) {
            cout << endl << "\t\t\t\t\t   ";
            for (int k = 0; k < boardSize; k++) {
                cout << "====";
            }
            cout << "=====";
        }
        cout << endl << "\t\t\t\t\t   ";
    }
    cout << "=========================================" << endl;
}

void fillBoard(int sudokuBoard[boardSize][boardSize], int given) {
    srand(time(0));

    for (int i = 0; i < given; i++)
    {
        int row = rand() % boardSize;
        int column = rand() % boardSize;
        int num = rand() % boardSize + 1;

        while (sudokuBoard[row][column] != 0 || !checkNumEntered(sudokuBoard, row, column, num)) {
            row = rand() % boardSize;
            column = rand() % boardSize;
            num = rand() % boardSize + 1;
        }

        sudokuBoard[row][column] = num;
    }
}

bool solveBoard(int sudokuBoard[boardSize][boardSize], int row, int column) {
    if (row == boardSize - 1 && column == boardSize) return true;
    if (column == boardSize) {
        row++;
        column = 0;
    }

    if (sudokuBoard[row][column] != 0) return solveBoard(sudokuBoard, row, column + 1);

    for (int i = 1; i <= boardSize; i++) {
        if (checkNumEntered(sudokuBoard, row, column, i)) {
            sudokuBoard[row][column] = i;

            if (solveBoard(sudokuBoard, row, column + 1)) return true;

            sudokuBoard[row][column] = 0;
        }
    }

    return false;
}

bool isSolved(int sudokuBoard[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (sudokuBoard[i][j] == 0) return false;
        }
    }

    return true;
}

void gamePlay(int sudokuBoard[boardSize][boardSize]) {
    int row, column, num;

    while (true) {
        printSudoku(sudokuBoard); // to update values entered by the user

        cout << "\n\n" << "\t\t\t\t\t " << "|Enter -1 for row to end game." << endl // to terminate the game and show solved board
            << "\t\t\t\t\t " << "|Row: ";
        cin >> row;

        // the condition to solve the board
        if (row == -1) {
            solveBoard(sudokuBoard, 0, 0);
            printSudoku(sudokuBoard);
            cout << endl;
            cout << "\t\t\t\t\t " << "**Hard Luck!**" << endl << "\t\t\t\t\t |";
            system("pause");
            return;
        }
        else {
            cout << "\t\t\t\t\t " << "|Column: ";
            cin >> column;
            cout << "\t\t\t\t\t " << "|Number: ";
            cin >> num;
        }

        if (isSolved(sudokuBoard))break;

        row--;
        column--;

        if (!checkNumEntered(sudokuBoard, row, column, num)) {
            cout << "\t\t\t\t  " << "|Invalid entry, try again." << endl << "\t\t\t\t  |";
            system("pause");
            continue;
        }
        sudokuBoard[row][column] = num;
    }

    bool solved = isSolved(sudokuBoard);

    if (solved) {
        cout << "Well done!" << endl;
        printSudoku(sudokuBoard);
    }
}

int main()
{
    int sudokuBoard[boardSize][boardSize], givenNumbers;
    bool newRound = true;

    memset(sudokuBoard, 0, sizeof(sudokuBoard));

    while (newRound) {
        mainScreen();
        cout << endl << "\t\t\t\t\t   " << "**Fill in numbers initialized as '0'.**";
        memset(sudokuBoard, 0, sizeof(sudokuBoard));
        char choice;
        cout << "\n\n" << "\t\t\t\t\t  |" << "1) Start Game"
            << endl << "\t\t\t\t\t  |" << "2) Exit"
            << endl << "\t\t\t\t\t  |"
            << endl << "\t\t\t\t\t  |" << "Choice: ";
        cin >> choice;

        system("cls");
        mainScreen();

        switch (choice) {
            // Start The Game
        case '1':
            cout << endl << "\t\t\t\t\t  |" << "1) Easy" << endl
                << "\t\t\t\t\t  |" << "2) Normal" << endl
                << "\t\t\t\t\t  |" << "3) Hard" << endl
                << "\t\t\t\t\t  |" << endl
                << "\t\t\t\t\t  |" << "Choice: ";
            cin >> choice;

            switch (choice) {
            case '1':
                givenNumbers = easy;
                break;

            case '2':
                givenNumbers = normal;
                break;
            case '3':
                givenNumbers = hard;
                break;
            default:
                cout << "Invalid Entry";
                choice = 'x';
                break;
            }
            if (choice == 'x') continue;

            fillBoard(sudokuBoard, givenNumbers);
            gamePlay(sudokuBoard);
            break;

        case '2':
            choice = 'x';
            break;

        default:
            cout << "Invalid Input" << endl;
        }
        if (choice == 'x') break;
        system("cls");

        mainScreen();
        cout << "\n\n" << "\t\t\t\t\t  " << "New round?(y/n): ";
        cin >> choice;
        if (choice != 'y') newRound = false;
    }

    // Program Termination
    system("cls");
    cout << "\n\n\n\n\n"
        << "\t\t\t\t\t" << "====================================" << endl
        << "\t\t\t\t\t\t  " << "Program Executed" << endl
        << "\t\t\t\t\t" << "===================================="
        << "\n\n\n\n";

    return 0;
}

