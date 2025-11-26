#include <iostream>
#include "getinput.h"
using namespace std;

void viewOptions(){
  cout << "Enter the number associated with the desired option:\n\n"
       << "1    View Options\n"
       << "2    Generate Sudoku Grid\n"
       << "3    Learn How to Play Sudoku\n"
       << "4    Credits\n"
       << "5    Quit\n\n";
};

void generateGrid(){
  srand(time(0)); // Seeds rand() based on system time.
  int symbolBuffer; // Used to prevent loss of information during shuffles.
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
  
  
  
  for(int symbol = 1; symbol <= 9; symbol++){ // Shuffles grid symbols, without blanks.
    int swapSymbol = rand() % 9 + 1;
    for(int row = 0; row < 9; row++)
      for(int col = 0; col < 9; col++)
        if(templateGrid[row][col] == symbol)
          templateGrid[row][col] = swapSymbol;
        else if(templateGrid[row][col] == swapSymbol)
          templateGrid[row][col] = symbol;
  }
  
  for(int row = 0; row < 3; row++){ // Shuffles rows of 3x3 blocks, with blanks.
    int swapRow = rand() % 3;
    for(int subRow = 0; subRow < 3; subRow++)
      for(int cell = 0; cell < 9; cell++){
        symbolBuffer = templateGrid[3 * row + subRow][cell];
        blankBuffer = templateVis[3 * row + subRow][cell];
        templateGrid[3 * row + subRow][cell] = templateGrid[3 * swapRow + subRow][cell];
        templateVis[3 * row + subRow][cell] = templateVis[3 * swapRow + subRow][cell];
        templateGrid[3 * swapRow + subRow][cell] = symbolBuffer;
        templateVis[3 * swapRow + subRow][cell] = blankBuffer;
      }
  }
  
  for(int col = 0; col < 3; col++){ // Shuffles cols of 3x3 blocks, with blanks.
    int swapCol = rand() % 3;
    for(int subCol = 0; subCol < 3; subCol++)
      for(int cell = 0; cell < 9; cell++){
        symbolBuffer = templateGrid[cell][3 * col + subCol];
        blankBuffer = templateVis[cell][3 * col + subCol];
        templateGrid[cell][3 * col + subCol] = templateGrid[cell][3 * swapCol + subCol];
        templateVis[cell][3 * col + subCol] = templateVis[cell][3 * swapCol + subCol];
        templateGrid[cell][3 * swapCol + subCol] = symbolBuffer;
        templateVis[cell][3 * swapCol + subCol] = blankBuffer;
      }
  }
  
  for(int bigRow = 0; bigRow < 3; bigRow++) // Shuffles rows within 3x9 areas, with blanks.
    for(int row = 0; row < 3; row++){
      int swapRow = rand() % 3;
      for(int cell = 0; cell < 9; cell++){
        symbolBuffer = templateGrid[3 * bigRow + row][cell];
        blankBuffer = templateVis[3 * bigRow + row][cell];
        templateGrid[3 * bigRow + row][cell] = templateGrid[3 * bigRow + swapRow][cell];
        templateVis[3 * bigRow + row][cell] = templateVis[3 * bigRow + swapRow][cell];
        templateGrid[3 * bigRow + swapRow][cell] = symbolBuffer;
        templateVis[3 * bigRow + swapRow][cell] = blankBuffer;
      }
    }
  
  for(int bigCol = 0; bigCol < 3; bigCol++) // Shuffles cols within 3x9 areas, with blanks.
    for(int col = 0; col < 3; col++){
      int swapCol = rand() % 3;
      for(int cell = 0; cell < 9; cell++){
        symbolBuffer = templateGrid[cell][3 * bigCol + col];
        blankBuffer = templateVis[cell][3 * bigCol + col];
        templateGrid[cell][3 * bigCol + col] = templateGrid[cell][3 * bigCol + swapCol];
        templateVis[cell][3 * bigCol + col] = templateVis[cell][3 * bigCol + swapCol];
        templateGrid[cell][3 * bigCol + swapCol] = symbolBuffer;
        templateVis[cell][3 * bigCol + swapCol] = blankBuffer;
      }
    }
  
  // TODO Create a preFill parameter to randomly set 0s in templateVis to 1s.

  for (int row = 0; row < 9; row++)
  {
      for (int col = 0; col < 9; col++)
      {
          int swapTo1 = rand() % 4;   //1 in 4 chance to swap a 0 to 1

          if ((swapTo1 == 0) && (templateVis[row][col] == 0))
          {
              templateVis[row][col] = 1;
          }
      }

  }
  // Completed a prefill parameter that randomly sets 0s in templateVis to 1s with a 1/4 chance.



  // TODO Print the sudoku grid.
  
  cout << "\n\n------------------------\n\n";
  for (int row = 0; row < 9; row++)
  {
      for (int col = 0; col < 9; col++)
      {
          if (templateVis[row][col] == 0)
          {
              templateGrid[row][col] = 0;
          }

          cout << templateGrid[row][col] << " ";
          if ((col + 1) % 3 == 0)
          {
              cout << "|";
          }
      }
      cout << endl;
      if ((row + 1) % 3 == 0)
      {
          cout << "---------------------\n";
      }
      
  }
  
  //Completed printing of the 9x9 grid

};

void howToPlay(){
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
        generateGrid(); // TODO Need to ask user for preFill parameter.
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
