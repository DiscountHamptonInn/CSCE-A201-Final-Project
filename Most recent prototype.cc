#include <iostream>
#include "getinput.h"
using namespace std;

void viewOptions(){
  cout << "Enter the number associated with the desired option:\n\n"
       << "1    View Options\n"
       << "2    Play Game\n"
       << "3    Learn How to Play Sudoku\n"
       << "4    Credits\n"
       << "5    Quit\n\n";
};

void playGame(int preFill){
  srand(time(0)); // Seeds rand() based on system time.
  int symbolBuffer, playerBuffer; // Used to prevent loss of information during shuffles.
  bool blankBuffer; // Ditto.
  
  int templateGrid[9][9] = { // A sudoku grid from online that is shuffled to make a new grid.
    {2, 3, 7, 8, 4, 1, 5, 6, 9},
    {1, 8, 6, 7, 9, 5, 2, 4, 3},
    {5, 9, 4, 3, 2, 6, 7, 1, 8},
    {3, 1, 5, 6, 7, 4, 8, 9, 2},
    {4, 6, 9, 5, 8, 2, 1, 3, 7},
    {7, 2, 8, 1, 3, 9, 4, 5, 6},
    {6, 4, 2, 9, 1, 8, 3, 7, 5},
    {8, 5, 3, 4, 6, 7, 9, 2, 1},
    {9, 7, 1, 2, 5, 3, 6, 8, 4}
  };
  bool templateVis[9][9] = { // Blank template cells. These are also shuffled.
    {0, 0, 0, 1, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0, 0}
  };
  int playerGrid[9][9] = { // The grid that the player is allowed to write on, also shuffled.
    {0, 0, 0, 8, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 4, 3},
    {5, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 7, 0, 8, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 2, 0, 0, 3, 0, 0, 0, 0},
    {6, 0, 0, 0, 0, 0, 0, 7, 5},
    {0, 0, 3, 4, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 0, 6, 0, 0}
  };
  
  int row, col;
  while(preFill != 0){
    row = rand() % 9;
    col = rand() % 9;
    if(templateVis[row][col] == false){
      templateVis[row][col] = true;
      playerGrid[row][col] = templateGrid[row][col];
      preFill--;
    }
  }
  
  for(int symbol = 1; symbol <= 9; symbol++){ // Shuffles grid symbols, without blanks.
    int swapSymbol = rand() % 9 + 1;
    for(int row = 0; row < 9; row++)
      for(int col = 0; col < 9; col++)
        if(templateGrid[row][col] == symbol){
          templateGrid[row][col] = swapSymbol;
          if(templateVis[row][col] == true)
            playerGrid[row][col] = swapSymbol;
        }
        else if(templateGrid[row][col] == swapSymbol){
          templateGrid[row][col] = symbol;
          if(templateVis[row][col] == true)
            playerGrid[row][col] = symbol;
        }
  }
  
  for(int row = 0; row < 3; row++){ // Shuffles rows of 3x3 blocks, with blanks.
    int swapRow = rand() % 3;
    for(int subRow = 0; subRow < 3; subRow++)
      for(int cell = 0; cell < 9; cell++){
        symbolBuffer = templateGrid[3 * row + subRow][cell];
        blankBuffer = templateVis[3 * row + subRow][cell];
        playerBuffer = playerGrid[3 * row + subRow][cell];
        templateGrid[3 * row + subRow][cell] = templateGrid[3 * swapRow + subRow][cell];
        templateVis[3 * row + subRow][cell] = templateVis[3 * swapRow + subRow][cell];
        playerGrid[3 * row + subRow][cell] = playerGrid[3 * swapRow + subRow][cell];
        templateGrid[3 * swapRow + subRow][cell] = symbolBuffer;
        templateVis[3 * swapRow + subRow][cell] = blankBuffer;
        playerGrid[3 * swapRow + subRow][cell] = playerBuffer;
      }
  }
  
  for(int col = 0; col < 3; col++){ // Shuffles cols of 3x3 blocks, with blanks.
    int swapCol = rand() % 3;
    for(int subCol = 0; subCol < 3; subCol++)
      for(int cell = 0; cell < 9; cell++){
        symbolBuffer = templateGrid[cell][3 * col + subCol];
        blankBuffer = templateVis[cell][3 * col + subCol];
        playerBuffer = playerGrid[cell][3 * col + subCol];
        templateGrid[cell][3 * col + subCol] = templateGrid[cell][3 * swapCol + subCol];
        templateVis[cell][3 * col + subCol] = templateVis[cell][3 * swapCol + subCol];
        playerGrid[cell][3 * col + subCol] = playerGrid[cell][3 * swapCol + subCol];
        templateGrid[cell][3 * swapCol + subCol] = symbolBuffer;
        templateVis[cell][3 * swapCol + subCol] = blankBuffer;
        playerGrid[cell][3 * swapCol + subCol] = playerBuffer;
      }
  }
  
  for(int bigRow = 0; bigRow < 3; bigRow++) // Shuffles rows within 3x9 areas, with blanks.
    for(int row = 0; row < 3; row++){
      int swapRow = rand() % 3;
      for(int cell = 0; cell < 9; cell++){
        symbolBuffer = templateGrid[3 * bigRow + row][cell];
        blankBuffer = templateVis[3 * bigRow + row][cell];
        playerBuffer = playerGrid[3 * bigRow + row][cell];
        templateGrid[3 * bigRow + row][cell] = templateGrid[3 * bigRow + swapRow][cell];
        templateVis[3 * bigRow + row][cell] = templateVis[3 * bigRow + swapRow][cell];
        playerGrid[3 * bigRow + row][cell] = playerGrid[3 * bigRow + swapRow][cell];
        templateGrid[3 * bigRow + swapRow][cell] = symbolBuffer;
        templateVis[3 * bigRow + swapRow][cell] = blankBuffer;
        playerGrid[3 * bigRow + swapRow][cell] = playerBuffer;
      }
    }
  
  for(int bigCol = 0; bigCol < 3; bigCol++) // Shuffles cols within 9x3 areas, with blanks.
    for(int col = 0; col < 3; col++){
      int swapCol = rand() % 3;
      for(int cell = 0; cell < 9; cell++){
        symbolBuffer = templateGrid[cell][3 * bigCol + col];
        blankBuffer = templateVis[cell][3 * bigCol + col];
        playerBuffer = playerGrid[cell][3 * bigCol + col];
        templateGrid[cell][3 * bigCol + col] = templateGrid[cell][3 * bigCol + swapCol];
        templateVis[cell][3 * bigCol + col] = templateVis[cell][3 * bigCol + swapCol];
        playerGrid[cell][3 * bigCol + col] = playerGrid[cell][3 * bigCol + swapCol];
        templateGrid[cell][3 * bigCol + swapCol] = symbolBuffer;
        templateVis[cell][3 * bigCol + swapCol] = blankBuffer;
        playerGrid[cell][3 * bigCol + swapCol] = playerBuffer;
      }
    }
  
  string answer;
  bool solved = false;
  while(!solved){ // Loops until playerGrid matches templateGrid or "quit" is entered.
    // TODO Make puzzle hints visually distinct from player answers.
    cout << "\n   1 2 3  4 5 6  7 8 9"
         << "\n  ----------------------\n";
    for(int row = 0; row < 9; row++){
      cout << row + 1 << " |";
      for(int col = 0; col < 9; col++){
        cout << playerGrid[row][col] << " ";
        if((col + 1) % 3 == 0)
          cout << "|";
      }
      cout << "\n";
      if((row + 1) % 3 == 0)
        cout << "  ----------------------\n";
    }
    cout << "\n";
    answer = getString("Fill in a cell in the form row,col=symbol or type \"quit\": ", 4, 5);
    if(
      answer.size() == 5 and
      answer[0] > 48 and
      answer[0] < 58 and
      answer[1] == ',' and
      answer[2] > 48 and
      answer[2] < 58 and
      answer[3] == '=' and
      answer[4] > 47 and
      answer[4] < 58 and
      templateVis[stoi(answer.substr(0, 1)) - 1][stoi(answer.substr(2, 1)) - 1] == false
    )
      playerGrid[stoi(answer.substr(0, 1)) - 1][stoi(answer.substr(2, 1)) - 1] =
        stoi(answer.substr(4, 1));
    else if(
      answer.size() == 5 and
      answer[0] > 48 and
      answer[0] < 58 and
      answer[1] == ',' and
      answer[2] > 48 and
      answer[2] < 58 and
      answer[3] == '=' and
      answer[4] > 47 and
      answer[4] < 58 and
      templateVis[stoi(answer.substr(0, 1)) - 1][stoi(answer.substr(2, 1)) - 1] == true
    )
      cout << "That is a prefilled puzzle hint. Try again.\n";
    else if(answer == "quit"){
      viewOptions();
      break;
    }
    else
      cout << "Invalid input. Try again.\n";
    for(int cell = 0; cell < 81; cell++) // Need to go by cell to use the "break" operation.
      if(playerGrid[cell / 9][cell % 9] != templateGrid[cell / 9][cell % 9])
        break;
      else if(cell == 80){
        cout << "You win!\n";
        solved = true;
      }
  }
};

void howToPlay(){
  cout << "The grid must be filled so that the numbers 1 to 9 appear in every row, column, "
       << "and 3x3 block exactly once.\n\n";
};

void credits(){
  cout << "Created by Joseph Lee and Benjamin Hampton. All rights reserved.\n\n";
};

int main(){ // Used as a menu to access the other functions.
  viewOptions();
  bool quit = false;
  
  while(!quit){
    switch(getChar("")){
      case '1':
        viewOptions();
        break;
      case '2':
        playGame(getInt("Enter the number of puzzle hints (17-40): ", 17, 40) - 17);
        break;
      case '3':
        howToPlay();
        break;
      case '4':
        credits();
        break;
      case '5':
        quit = true;
        break;
      default:
        cout << "Input can only be integers 1 to 5 inclusive. Please try again.\n";
        break;
    }
  }
  
  return 0;
}
