// chessboard.cpp

#include "chessboard.h"

// define containers for color mappings (2 colors) and piece mappings (6 pieces)

ChessboardIterator Chessboard::begin() {
  return ChessboardIterator(*this, 0);
}

ChessboardIterator Chessboard::end() {
  return ChessboardIterator(*this, 64);
}

// print the chessboard with white at the bottom (traditional view)
void Chessboard::print() {
  
  int i = 0; // Track position for new line
  string board = ""; // Hold the string with the entire board
  string row = ""; // Hold the string for a given row

  // Iterate through the chess board using the iterator
  for(auto it = begin(); it != end(); ++it){
    // Check if a new line is required
    if(i%8 == 0 && i != 0){
      //Prepend to the board and clear the row
      board = row + "\n" + board;
      row = "";
    }
    int x, y; // x and y coordinates of a square
    
    // Use the xy function of the iterator to transform the position into coordinates
    it.xy(x,y);  

    string firstSymb = " "; // The first character of our symbol
    string secondSymb = " "; // The second character of our symbol
    string thirdSymb = " "; // The third character of our symbol

    //Set Color symbol
    if(chessboard[x][y].getColor() == White){
      firstSymb = "w";
    }
    else if(chessboard[x][y].getColor() == Black){
      firstSymb = "b";
    }
    else if(chessboard[x][y].getColor() == NoColor){
      firstSymb = " ";
    }

    //Set Piece symbol
    if(chessboard[x][y].getPiece() == Rook){
      secondSymb = "R";
    }
    if(chessboard[x][y].getPiece() == Knight){
      secondSymb = "N";
    }
    if(chessboard[x][y].getPiece() == Bishop){
      secondSymb = "B";
    }
    if(chessboard[x][y].getPiece() == Queen){
      secondSymb = "Q";
    }
    if(chessboard[x][y].getPiece() == King){
      secondSymb = "K";
    }
    if(chessboard[x][y].getPiece() == Pawn){
      secondSymb = "P";
    }
    if(chessboard[x][y].getPiece() == NoPiece){
      secondSymb = ".";
    }

    string symbol = firstSymb+secondSymb+thirdSymb; // Combine symbols into one symbol
    // Add symbol to the current row
    row = row + symbol;

    // Handle last row
    if(i == 63){ 
      board = row + "\n" + board;
    }

    // Increment the number of the row
    i++;
    
  }
  // After iteration is complete, print out the board
  cout << board;
}
