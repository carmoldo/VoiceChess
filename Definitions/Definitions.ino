#pragma once
#include <Arduino.h> // Agrega la biblioteca de Arduino

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

class Square
{
  bool muerta;
  Piece piece;
  Color color;
  int x, y;

public:
  void setSpace(Square*);
  void setEmpty();
  void setPieceAndColor(Piece, Color);
  Piece getPiece();
  Color getColor();
  void setX(int ex) { x = ex; }
  void setY(int why) { y = why; }
  int getX() { return x; }
  int getY() { return y; }
  Square();
};

class Board
{
  Square square[8][12];
  Color turn = WHITE;
  bool moveKing(Square* thisKing, Square* thatSpace);
  bool moveQueen(Square* thisQueen, Square* thatSpace);
  bool moveBishop(Square* thisBishop, Square* thatSpace);
  bool moveKnight(Square* thisKnight, Square* thatSpace);
  bool moveRook(Square* thisRook, Square* thatSpace);
  bool movePawn(Square* thisPawn, Square* thatSpace);
  bool makeMove(int x1, int y1, int x2, int y2);

public:
  Square* getSquare(int x, int y);
  void setSquare(Square* s, int x, int y);
  bool doMove();
  void setBoard();
  bool playGame();
};
