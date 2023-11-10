// ARCHIVO DEFINITIONS
#pragma once
#include <iostream>
#include <cmath>
#include <string>

enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
enum Color { WHITE, BLACK, NONE };

class Square
{
  Piece piece;
  Color color;
  bool mano;
  int x, y;

public:
void setMano(bool value) { mano = value; } 
// Método público para establecer 'mano'
bool getMano() const { return mano; } 
// Método público para obtener el valor de 'mano'

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
  Color turn=WHITE;
  bool moveKing(Square* thisKing, Square* thatSpace);
  bool moveQueen(Square* thisQueen, Square* thatSpace);
  bool moveBishop(Square* thisBishop, Square* thatSpace);
  bool moveKnight(Square* thisKnight, Square* thatSpace);
  bool moveRook(Square* thisRook, Square* thatSpace);
  bool movePawn(Square* thisPawn, Square* thatSpace);
  bool makeMove(int x1, int y1, int x2, int y2);
  void printBoard();
public:

void MovimientoIRL(Square* src, Square* dest);

void setFichasMuertas(Square* src, Square* dest);
  Square* getSquare(int x, int y) {
    return &square[x][y];
  }
  void setSquare(Square * s, int x, int y){
    square[x][y]=*s;
  }
  bool doMove();
  
  void setBoard();
  bool playGame();
};
