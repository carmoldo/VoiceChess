#include "../Definitions/Definitions.IDE"
#include <iostream>
#include <string>
using namespace std;

// CREO LA ESTRUCTURA COMANDO
struct Comando {
    string piece;
    int numerodestino;
    char letradestino;
    int numeroinicio;
    char letrainicio;
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

bool Board::doMove() {
  using namespace std;
  Comando comando;

  bool stop = false;
  while (!stop)
  {
    //ACA SE SOLICITA AL USUARIO QUE INGRESE UN MOVIMIENTO
    (turn == WHITE) ? Serial.println("White's turn") : Serial.println("Black's turn");
    Serial.println("Enter your move using the format [col1][row1][col2][row2]: ");

    // Leer el comando directamente en la estructura Comando
    comando.letrainicio = Serial.read();
    comando.numeroinicio = Serial.read() - '0';
    comando.letradestino = Serial.read();
    comando.numerodestino = Serial.read() - '0';
    // Convertir letras de columnas a números (A == 1, B == 2, ..., H == 8)
    int x1 = comando.letrainicio - 'A' + 1;
    int y1 = comando.numeroinicio;
    int x2 = comando.letradestino - 'A' + 1;
    int y2 = comando.numerodestino;


    // Aquí se verifica si el color de la casilla de origen coincide con el turno actual del jugador. 
    // Si es así, se intenta realizar el movimiento utilizando la función makeMove(). Si el movimiento es inválido, se imprime un mensaje de error.
    // Si el movimiento es válido, se marca stop como true para salir del bucle y se procede al siguiente paso.
    if (getSquare(x1, y1)->getColor() == turn)
    {
      if (makeMove(x1, y1, x2, y2) == false)
      {
        Serial.println("Invalid move, try again.");
      }
      else
        stop = true;
    }
    else
      Serial.println("That's not your piece. Try again.");
  }
  
  if (getSquare(x2, y2)->getPiece() == KING)
  {
    if (getSquare(x1, y1)->getColor() == WHITE)
    {
      Serial.println("WHITE WINS");
      return false;
    }
    else
    {
      Serial.println("BLACK WINS");
      return false;
    }
  }

  if (turn == BLACK)
    turn = WHITE;
  else
    turn = BLACK;

  return true;
}

bool Board::makeMove(int x1, int y1, int x2, int y2) {
  //Checking for turns will be done previous to this
  using namespace std;
  if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>8)
  {
    std::cout << "One of your inputs was our of bounds" << std::endl;
    return false;
  }
  Square* src = getSquare(x1, y1);
  Square* dest = getSquare(x2, y2);

  if (src->getColor() == dest->getColor() && dest->getColor() != NONE)
  {
    std::cout << "Invalid move: cannot land on your own piece" << std::endl;
    return false;
  }

  switch (src->getPiece())
  {
  case KING: return moveKing(src, dest);
    break;
  case QUEEN: return moveQueen(src, dest);
    break;
  case BISHOP: return moveBishop(src, dest);
    break;
  case KNIGHT: return moveKnight(src, dest);
    break;
  case ROOK: return moveRook(src, dest);
    break;
  case PAWN: return movePawn(src, dest);
    break;
  case EMPTY: std::cout << "You do not have a piece there" << std::endl;  return false;
    break;
  default: std::cerr << "Something went wrong in the switch statement in makeMove()" << std::endl;
    break;
  }
  return false;
}

}
