// see for background
//  https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html

#include "chessboard.h"
#include <iostream>
using namespace std;

Color get_illegal_color(){
    Color cs[] = {Black, White};
    int min_c = (int)Black;
    for (Color j: cs)
        min_c = (min_c > (int)j) ? j:min_c;
    return (Color)(min_c-1);
}


int main() {
  // std::cout << "Hello World!\n";
  Chessboard chessboard;

  chessboard.place(0, 0, White, Rook);
  chessboard.place(1, 0, White, Knight);
  chessboard.place(2, 0, White, Bishop);
  chessboard.place(3, 0, White, Queen);
  chessboard.place(4, 0, White, King);
  chessboard.place(5, 0, White, Bishop);
  chessboard.place(6, 0, White, Knight);
  chessboard.place(7, 0, White, Rook);
  for (int i = 0; i < 8; i++) {
    chessboard.place(i, 1, White, Pawn);
  }
  chessboard.place(0, 7, Black, Rook);
  chessboard.place(1, 7, Black, Knight);
  chessboard.place(2, 7, Black, Bishop);
  chessboard.place(3, 7, Black, Queen);
  chessboard.place(4, 7, Black, King);
  chessboard.place(5, 7, Black, Bishop);
  chessboard.place(6, 7, Black, Knight);
  chessboard.place(7, 7, Black, Rook);
  for (int i = 0; i < 8; i++) {
    chessboard.place(i, 6, Black, Pawn);
  }
  chessboard.print();
  // cout << "***********Testing get************" << endl;
  // Color co;
  // Piece p;
  // cout << "Testing get illegal x cood: " << chessboard.get(8, 0, co, p) << endl;
  // cout << "Testing get illegal y cood: " << chessboard.get(0, 8, co, p) << endl;
  // cout << "Testing get occupied square: " << chessboard.get(3, 0, co, p)
  //      << endl;
  // cout << "Testing get unoccupied square: " << chessboard.get(0, 2, co, p)
  //      << endl;
  // cout << "***********Testing place************" << endl;
  // Color coPlace = (Color)3;
  // Piece piPlace = (Piece)6;
  // cout << "Testing place illegal x cood: "
  //      << chessboard.place(87, 8, coPlace, piPlace) << endl;
  // cout << "Testing place illegal y cood: "
  //      << chessboard.place(0, 8, coPlace, piPlace) << endl;
  // cout << "Testing place square occupied: "
  //      << chessboard.place(0, 0, coPlace, piPlace) << endl;
  // cout << "Testing place illegal color: "
  //      << chessboard.place(0, 2, coPlace, piPlace) << endl;
  // coPlace = (Color)0;
  // cout << "Testing place illegal piece: "
  //      << chessboard.place(0, 2, coPlace, piPlace) << endl;
  // piPlace = (Piece)3;
  // cout << "Testing place everything ok: "
  //      << chessboard.place(0, 2, coPlace, piPlace) << endl;
  // chessboard.print();

  // cout << "--------------------\n" << endl;
  //   Chessboard cb;
  //   int out = 1;
  //   Color illegal_col = get_illegal_color();
  //   cout << "\n<<< place() >>>\n\n";
  //   cout << cb.place(4, 5, White, Knight) << endl; // 1
  //   cout << cb.place(6, 7, Black, Rook) << endl; // 1
  //   cout << cb.place(3, 2, White, Knight) << endl; // 1
  //   cout << cb.place(-9, 0, White, Knight) << endl; // -1
  //   cout << cb.place(4, 6, Black, Pawn) << endl; // 1
  //   cout << cb.place(0, 1, illegal_col, Knight) << endl; // -4
  //   cout << cb.place(3, 2, Black, Queen) << endl; // -3

  //   // cb.print();

  //   Color c;
  //   Piece p;
    
  //   cout << "\n<<< get() >>>\n\n";
  //   cout << cb.get(3, 2, c, p) << endl; // 1
  //   cout << ((c==White) && (p==Knight)) << endl;
  //   cout << cb.get(33, 3, c, p) << endl; // -1
  //   cout << cb.get(1, 22, c, p) << endl; // -2
  //   cout << cb.get(4, 6, c, p) << endl; // 1
  //   cout << ((c==Black) && (p==Pawn)) << endl;

  //   // cb.print();


  //   cout << "\n<<< move() >>>\n\n" ;
  //   cout << cb.move(3, 2, 1, 3) << endl; // 1

  //   // cb.print();
    
  //   cout << cb.move(1, 3, 2, 5) << endl; // 1
    
  //   // cb.print();

  //   cout << cb.move(4, 6, 4, 7) << endl; // -7

  //   // cb.print();

  //   cout << cb.move(4, 5, 3, 7) << endl; // 1

  //   // cb.print();

  //   cout << cb.move(2, 5, 3, 7) << endl; // -6
    
  //   // cb.print();
  // cout << "-----------" << endl;
  // chessboard.move(0,1,0,2);
  
  // chessboard.print();

  // cout << "-----------" << endl;

  // chessboard.move(0,6,0,5);
  
  // chessboard.print();
  // cout << "-----------" << endl;

  // chessboard.place(2, 2, Black, Pawn);
  
  // chessboard.move(1,1,2,2);
  
  // chessboard.print();
  // cout << "-----------" << endl;
  
  // chessboard.place(4, 5, White, Pawn);
  
  // chessboard.move(3,6,4,5);

  // chessboard.print();
  
}

