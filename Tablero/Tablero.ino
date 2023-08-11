
#include chess.h /es decir, donde estan las definiciones de el square
#include <iostream>
#include <string>
using namespace std;

// CREO LA ESTRUCTURA COMANDO
struct Comando {
    string piece;
    int numero;
    char letra;
};

// CREO LA ESTRUCTURA SQUARE (CON PIECE Y COLOR)
Square::Square()
{
  piece = EMPTY;
  color = NONE;
}

// COPIA EL VALOR COLOR Y PIECE DE SPACE AL DE ESTA INSTANCIA
Piece Square::getPiece(){  return piece;}
Color Square::getColor(){  return color;}
void Square::setSpace(Square* space)
{
  color = space->getColor(); // Copia el color del objeto 'space' al color de esta instancia
  piece = space->getPiece(); // Copia la pieza del objeto 'space' a la pieza de esta instancia
}

void Square::setEmpty()
{
  color = NONE;
  piece = EMPTY;
}

//PARA ESTABLECER LUEGO LOS VALORES DE LAS FICHAS
void Square::setPieceAndColor(Piece p, Color c)
{
  piece = p;
  color = c;
}

// ESTABLECE LOS VALORES DE LAS FICHAS EN CADA CUADRADO
void Board::setBoard()
{
  square[0][0].setPieceAndColor(TORRE, WHITE);
  square[1][0].setPieceAndColor(CABALLO, WHITE);
  square[2][0].setPieceAndColor(ALFIL, WHITE);
  square[3][0].setPieceAndColor(REINA, WHITE);
  square[4][0].setPieceAndColor(REY, WHITE);
  square[5][0].setPieceAndColor(ALFIL, WHITE);
  square[6][0].setPieceAndColor(CABALLO, WHITE);
  square[7][0].setPieceAndColor(TORRE, WHITE);

  square[0][7].setPieceAndColor(TORRE, BLACK);
  square[1][7].setPieceAndColor(CABALLO, BLACK);
  square[2][7].setPieceAndColor(ALFIL, BLACK);
  square[3][7].setPieceAndColor(REINA, BLACK);
  square[4][7].setPieceAndColor(REY, BLACK);
  square[5][7].setPieceAndColor(ALFIL, BLACK);
  square[6][7].setPieceAndColor(CABALLO, BLACK);
  square[7][7].setPieceAndColor(TORRE, BLACK);

  for (int i = 0; i < 8; i++)
  {
    square[i][1].setPieceAndColor(PEON, WHITE);
    square[i][6].setPieceAndColor(PEON, BLACK);
  }

  for (int i = 2; i < 6; i++)
  {
    for (int j = 0; j < 8; j++)
      square[j][i].setPieceAndColor(EMPTY, NONE);

  }
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
      square[i][j].setX(i);
      square[i][j].setY(j);
    }

}

}
