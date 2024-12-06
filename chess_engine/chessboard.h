// see for background
//  https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html

#include <iostream>
#include <iterator>
using namespace std;

// define separate containers for Color, Piece (enums recommended)
enum Color { White, Black, NoColor };
enum Piece { King, Queen, Bishop, Knight, Rook, Pawn, NoPiece };
// a chessboard contains squares
class Square {
private:
  Color color;
  Piece piece;
  bool occupied;

public:
  Square() { // default, square unoccupied
    this->color = NoColor;
    this->piece = NoPiece;
    this->occupied = false;
  }
  Square(Color c, Piece p) { // an occupied square
    this->color = c;
    this->piece = p;
    this->occupied = true;
  }
  void get(bool &o, Color &c, Piece &p) {
    o = this->occupied;
    c = this->color;
    p = this->piece;
  }

  // Getters and Setters for the values of the squares
  bool getOccupied() {
    return this->occupied; 
  }
  void setOccupied(bool newOccupied) {
    this->occupied = newOccupied;
  }
  Color getColor() {
    return this->color;
  }
  void setColor(Color newColor) {
    this->color = newColor;
  }
  Piece getPiece() {
    return this->piece;
  }
  void setPiece(Piece newPiece) { 
    this->piece = newPiece; 
  }

  void print();
};

class ChessboardIterator;

class Chessboard {
  // make the container iterator friendly
  typedef ChessboardIterator iterator;

private:
  Square chessboard[8][8];

public:
  friend class ChessboardIterator;

  Chessboard() {} // Square does all the initialization

  // return an x,y square from chessboard
  Square square(int x, int y) {
    return chessboard[x][y]; 
  }

  ChessboardIterator begin();
  ChessboardIterator end();

  // place a piece on a x,y square in the chessboard
  int place(int x, int y, Color c, Piece p) {

    // Check if the coordinates are legal
    if (x < 0 || x > 7) {
      return -1;
    }
    if (y < 0 || y > 7) {
      return -2;
    }
    // Check if the square is occupied
    if (chessboard[x][y].getOccupied() == true) {
      return -3;
    }
    // Check if the color is valid
    if ((c != Black) && (c != White) && (c != NoColor)) {
      return -4;
    }
    // Check if the piece is valid
    if ((p != King && p != Queen && p != Knight && p != Bishop && p != Rook &&
         p != Pawn)) {
      return -5;
    }
    // Set the square values to the users values
    else {
      chessboard[x][y].setColor(c);
      chessboard[x][y].setPiece(p);
      chessboard[x][y].setOccupied(true);

      return 1;
    }
  }

  // Return color and type of specified space on chessboard
  int get(int x, int y, Color &c, Piece &p) {
    // Check if coordinates are legal
    if (x < 0 || x > 7) {
      return -1;
    }
    if (y < 0 || y > 7) {
      return -2;
    }
    // Check if the square is occupied
    if (chessboard[x][y].getOccupied() == false) {
      return -3;
    }

    // Get the information requested by the user
    c = chessboard[x][y].getColor();
    p = chessboard[x][y].getPiece();

    return 1;
  }

  // Move the white pawn
  int moveWhitePawn(int fromX, int fromY, int toX, int toY) {
    // Make sure the coordinates allow for the move to be made
    if ((fromY - toY != -1) || ((fromX - toX != 1 && fromX - toX != -1))) {
      if ((fromX - toX == (0)) && chessboard[toX][toY].getOccupied() == false) {
        // Move the pawn forward
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear the values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
    }
    // Make sure the coordinates allow for the move to be made
    if ((fromY - toY == -1) && ((fromX - toX == 1 || fromX - toX == -1))) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the pawn to attack
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear the values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
    }
    return -7;
  }

  // Move the black pawn
  int moveBlackPawn(int fromX, int fromY, int toX, int toY) {
    // Make sure the coordinates allow for the move to be made
    if ((fromY - toY != 1) || ((fromX - toX != 1 && fromX - toX != -1))) {
      if ((fromX - toX == (0)) && chessboard[toX][toY].getOccupied() == false) {
        // Move the pawn forward
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear the values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
    }
    // Make sure the coordinates allow for the move to be made
    if ((fromY - toY == 1) && ((fromX - toX == 1 || fromX - toX == -1))) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() !=
          chessboard[fromX][fromY].getColor()) {
        // Move the pawn to attack
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear the values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
    }
    return -7;
  }

  // Move the rook
  int moveRook(int fromX, int fromY, int toX, int toY) {
    // Check for piece in the way if moving down
    if ((fromY > toY) && (fromX == toX)) {
      int destination = toY;
      if (fromY - toY != 1) {
        for (int i = fromY; i > destination; i--) {
          if (chessboard[fromX][i].getOccupied() == true) {
            return -7;
          }
        }
      }

      // Check if color allows for move
      // Move the rook
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    // Check for piece in the way if moving up
    else if ((fromY < toY) && (fromX == toX)) {
      int destination = fromY;
      if (toY - fromY != 1) {
        for (int i = fromX; i < destination; i++) {
          if (chessboard[fromX][i].getOccupied() == true) {
            return -7;
          }
        }
      }

      // Check if color allows for move
      // Move the rook
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
      else {
        return -7;
      }
    }

    // Check for piece in the way if moving left
    else if ((fromX > toX) && (fromY == toY)) {
      int destination = toX;
      if (fromX - toX != 1) {
        for (int i = fromY; i > destination; i--) {
          if (chessboard[i][fromY].getOccupied() == true) {
            return -7;
          }
        }
      }

      // Check if color allows for move
      // Move the rook
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    // Check for piece in the way if moving left
    else if ((fromX < toX) && (fromY == toY)) {
      int destination = fromX;
      if (toX - fromX != 1) {
        for (int i = fromY; i < destination; i++) {
          if (chessboard[i][fromY].getOccupied() == true) {
            return -7;
          }
        }
      }

      // Check if color allows for move
      // Move the rook
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }

    else {
      return -7;
    }
  }

  // Handle moving the knight
  int moveKnight(int fromX, int fromY, int toX, int toY) {
    // Check if coordinates are legal
    if (((fromX - toX == 2) && ((fromY - toY == 1 || fromY - toY == -1)))) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    // Check if coordinates are legal
    else if (((fromX - toX == -2) && ((fromY - toY == 1 || fromY - toY == -1)))) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    // Check if coordinates are legal
    else if (((fromX - toX == 1 || fromX - toX == -1)) && ((fromY - toY == 2 || fromY - toY == -2))) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    // Check if coordinates are legal
    else if (((fromX - toX == -1)) && ((fromY - toY == 2 || fromY - toY == -2))) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
      else {
        return -7;
      }
    } 
    else {
      return -7;
    }
  }

  int moveBishop(int fromX, int fromY, int toX, int toY) {

    if (abs(toX - fromX) == abs(toY - fromY)) {

      if ((toX > fromX) && (toY > fromY)) {
        int i = fromX + 1;
        int j = fromY + 1;
        while ((i != toX) && (j != toY)) {
          if (chessboard[i][j].getOccupied() == true) {
            return -7;
          }
          i += 1;
          j += 1;
        }
      }

      else if ((toX > fromX) && (toY < fromY)) {
        int i = fromX + 1;
        int j = fromY - 1;
        while ((i != toX) && (j != toY)) {
          if (chessboard[i][j].getOccupied() == true) {
            return -7;
          }
          i += 1;
          j -= 1;
        }
      }

      else if ((toX < fromX) && (toY < fromY)) {
        int i = fromX - 1;
        int j = fromY - 1;
        while ((i != toX) && (j != toY)) {
          if (chessboard[i][j].getOccupied() == true) {
            return -7;
          }
          i -= 1;
          j -= 1;
        }
      }

      else if ((toX < fromX) && (toY > fromY)) {
        int i = fromX - 1;
        int j = fromY + 1;
        while ((i != toX) && (j != toY)) {
          if (chessboard[i][j].getOccupied() == true) {
            return -7;
          }
          i -= 1;
          j += 1;
        }
      }

      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
      else {
        return -7;
      }
    }
    return -7;
  }

  int moveKing(int fromX, int fromY, int toX, int toY) {
    if (((fromX - toX) == 1) && ((fromY - toY) == 0)) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
      else {
        return -7;
      }
    }
    if (((fromX - toX) == 1) && ((fromY - toY) == 1)) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);
        
        return 1;
        
      } 
      else {
        return -7;
      }
    }
    if (((fromX - toX) == 1) && ((fromY - toY) == -1)) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
      else {
        return -7;
      }
    }
    if (((fromX - toX) == 0) && ((fromY - toY) == 1)) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    if (((fromX - toX) == 0) && ((fromY - toY) == -1)) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    if (((fromX - toX) == -1) && ((fromY - toY) == 1)) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    if (((fromX - toX) == -1) && ((fromY - toY) == 0)) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    if (((fromX - toX) == -1) && ((fromY - toY) == -1)) {
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    return -7;
  }

  int moveQueen(int fromX, int fromY, int toX, int toY) {
    // Check for piece in the way
    if ((fromY > toY) && (fromX == toX)) {
      int destination = toY;
      if (fromY - toY != 1) {
        for (int i = fromY; i > destination; i--) {
          if (chessboard[fromX][i].getOccupied() == true) {
            return -7;
          }
        }
      }
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    } 
    // Check for piece in the way
    else if ((fromY < toY) && (fromX == toX)) {
      int destination = fromY;
      if (toY - fromY != 1) {
        for (int i = fromX; i < destination; i++) {
          if (chessboard[fromX][i].getOccupied() == true) {
            return -7;
          }
        }
      }

      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
      else {
        return -7;
      }
    } 
    // Check for piece in the way
    else if ((fromX > toX) && (fromY == toY)) {
      int destination = toX;
      if (fromX - toX != 1) {
        for (int i = fromY; i > destination; i--) {
          if (chessboard[i][fromY].getOccupied() == true) {
            return -7;
          }
        }
      }
      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      } 
      else {
        return -7;
      }
    }
    // Check for piece in the way
    else if ((fromX < toX) && (fromY == toY)) {
      int destination = fromX;
      if (toX - fromX != 1) {
        for (int i = fromY; i < destination; i++) {
          if (chessboard[i][fromY].getOccupied() == true) {
            return -7;
          }
        }
      }

      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
      else {
        return -7;
      }
    }

    // Check Queens Diagonal Moves
    else if (abs(toX - fromX) == abs(toY - fromY)) {
      // Check for piece in the way
      if ((toX > fromX) && (toY > fromY)) {
        int i = fromX + 1;
        int j = fromY + 1;
        while ((i != toX) && (j != toY)) {
          if (chessboard[i][j].getOccupied() == true) {
            return -7;
          }
          i += 1;
          j += 1;
        }
      }
      // Check for piece in the way
      else if ((toX > fromX) && (toY < fromY)) {
        int i = fromX + 1;
        int j = fromY - 1;
        while ((i != toX) && (j != toY)) {
          if (chessboard[i][j].getOccupied() == true) {
            return -7;
          }
          i += 1;
          j -= 1;
        }
      }
      // Check for piece in the way
      else if ((toX < fromX) && (toY < fromY)) {
        int i = fromX - 1;
        int j = fromY - 1;
        while ((i != toX) && (j != toY)) {
          if (chessboard[i][j].getOccupied() == true) {
            return -7;
          }
          i -= 1;
          j -= 1;
        }
      }
      // Check for piece in the way
      else if ((toX < fromX) && (toY > fromY)) {
        int i = fromX - 1;
        int j = fromY + 1;
        while ((i != toX) && (j != toY)) {
          if (chessboard[i][j].getOccupied() == true) {
            return -7;
          }
          i -= 1;
          j += 1;
        }
      }

      // Check if color allows for move
      if (chessboard[toX][toY].getColor() != chessboard[fromX][fromY].getColor()) {
        // Move the piece
        chessboard[toX][toY].setColor(chessboard[fromX][fromY].getColor());
        chessboard[toX][toY].setPiece(chessboard[fromX][fromY].getPiece());
        chessboard[toX][toY].setOccupied(chessboard[fromX][fromY].getOccupied());

        // Clear values of the from square
        chessboard[fromX][fromY].setColor(NoColor);
        chessboard[fromX][fromY].setPiece(NoPiece);
        chessboard[fromX][fromY].setOccupied(false);

        return 1;
      }
      else {
        return -7;
      }
    }
  }

  int move(int fromX, int fromY, int toX, int toY) {

    int returnCode; // The return value for the piece move functions

    // Make sure from coordinates are legal
    if (fromX < 0 || fromX > 7) {
      return -1;
    }
    if (fromY < 0 || fromY > 7) {
      return -2;
    }
    // Make sure to coordinates are legal
    if (toX < 0 || toX > 7) {
      return -3;
    }
    if (toY < 0 || toY > 7) {
      return -4;
    }
    // Make sure square is not occupied
    if (chessboard[fromX][fromY].getOccupied() == false) {
      return -5;
    }
    // Make sure you aren't moving to a square of the same color
    if (chessboard[fromX][fromY].getColor() == chessboard[toX][toY].getColor()) {
      return -6;
    }

    // Handle moves for pawns
    if (chessboard[fromX][fromY].getPiece() == Pawn) {
      // Black Pawn move
      if (chessboard[fromX][fromY].getColor() == Black) {
        returnCode = moveBlackPawn(fromX, fromY, toX, toY);
      }
      // White Pawn move
      if (chessboard[fromX][fromY].getColor() == White) {
        returnCode = moveWhitePawn(fromX, fromY, toX, toY);
      }
      return returnCode;
    }
    // Handles move for Rook
    else if (chessboard[fromX][fromY].getPiece() == Rook) {
      returnCode = moveRook(fromX, fromY, toX, toY);
      return returnCode;
    }
    // Handles move for Knight
    else if (chessboard[fromX][fromY].getPiece() == Knight) {
      returnCode = moveKnight(fromX, fromY, toX, toY);
      return returnCode;
    }
    // Handles move for Bishop
    else if (chessboard[fromX][fromY].getPiece() == Bishop) {
      returnCode = moveBishop(fromX, fromY, toX, toY);
      return returnCode;
    }
    // Handles move for King
    else if (chessboard[fromX][fromY].getPiece() == King) {
      returnCode = moveKing(fromX, fromY, toX, toY);
      return returnCode;
    }
    // Handles move for Queen
    else if (chessboard[fromX][fromY].getPiece() == Queen) {
      returnCode = moveQueen(fromX, fromY, toX, toY);
      return returnCode;
    }
    // Invalid Inputs
    else {
      return -7;
    }
  }
  void print();
};

class ChessboardIterator {
private:
  int position;          // a number in [0..63]
  Chessboard chessboard; // An 8x8 array

public:
  ChessboardIterator(Chessboard &board, int pos) { // start out with an empty board
    chessboard = board;
    position = pos;
  }

  void xy(int &x, int &y) { // break position down into x and y
    x = position % 8;
    y = position / 8;
  }

  // return the square
  Square operator*() {
    int x;
    int y;
    xy(x, y);
    return chessboard.square(x, y);
  }

  // pre-increment
  ChessboardIterator &operator++() {
    position++;
    return *this;
  }

  // needed to support foreach
  bool operator!=(const ChessboardIterator &a) {
    return a.position != this->position;
  }
};