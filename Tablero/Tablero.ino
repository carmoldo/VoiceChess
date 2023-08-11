
#include chess.h

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
  string move;
  
  char col1, col2;  // Nuevas variables para las letras de las columnas
  int x1, y1, x2, y2;  // Variables para las coordenadas
  
  bool stop = false;
  while (!stop)
  {
    (turn == WHITE) ? cout << "White's turn" << endl : cout << "Black's turn" << endl;
    cout << "Enter your move using the format [col1][row1][col2][row2]: ";
    cin >> move;
    
    // Extraer las coordenadas de origen y destino (columnas y filas)
    col1 = move[0];
    y1 = move[1] - '0';
    col2 = move[2];
    y2 = move[3] - '0';
    
    // Convertir letras de columnas a números (A == 1, B == 2, ..., H == 8)
    x1 = col1 - 'A' + 1;
    x2 = col2 - 'A' + 1;
    
    if (getSquare(x1, y1)->getColor() == turn)
    {
      if (makeMove(x1, y1, x2, y2) == false)
      {
        cout << "Invalid move, try again." << endl;
      }
      else
        stop = true;
    }
    else
      cout << "That's not your piece. Try again." << endl;
  }
  
  if (getSquare(x2, y2)->getPiece() == KING)
    if (getSquare(x1, y1)->getColor() == WHITE)
    {
      cout << "WHITE WINS" << endl;
      return false;
    }
    else

    {
      cout << "BLACK WINS" << endl;
      return false;
    }


  if (turn == BLACK)
    turn = WHITE;
  else
    turn = BLACK;

  return true;
}


bool Board::playGame()
{
  system("cls");
  printBoard();
  return doMove();

}

bool Board::moveKing(Square* thisKing, Square* thatSpace) {
  //off board inputs should be handled elsewhere (before this)
  //squares with same color should be handled elsewhere (before this)
  if (abs(thatSpace->getX() - thisKing->getX()) == 1)
    if (abs(thatSpace->getY() - thisKing->getY()) == 1)
    {
      thatSpace->setSpace(thisKing);
      thisKing->setEmpty();
      return true;
    }
    else return false;
  else return false;
}
bool Board::moveQueen(Square* thisQueen, Square* thatSpace) { //there might be problems with numbers of brackets
                             //off board inputs should be handled elsewhere (before this)
                             //squares with same color should be handled elsewhere (before this)

  int queenX = thisQueen->getX();
  int queenY = thisQueen->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  std::cout << "this";
  int yIncrement;
  int xIncrement;

  bool invalid = false;
  if (queenX != thatX || queenY != thatY)
  {

    if (queenX == thatX)
    {
      yIncrement = (thatY - queenY) / (abs(thatY - queenY));
      for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
      {

        if (square[thatX][i].getColor() != NONE)
          return false;

      }
    }
    else
      if (queenY == thatY)
      {

        xIncrement = (thatX - queenX) / (abs(thatX - queenX));
        for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
        {
          if (square[i][thatY].getColor() != NONE)
            return false;
        }
      }
      else
        if (abs(queenX - thatX) == abs(queenY - thatY))
        {
          xIncrement = (thatX - queenX) / (abs(thatX - queenX));
          yIncrement = (thatY - queenY) / (abs(thatY - queenY));

          for (int i = 1; i < abs(queenX - thatX); i++)
          {
            std::cout << "It got here somehow";
            if (square[queenX + xIncrement*i][queenY + yIncrement*i].getColor() != NONE)
              return false;

          }
        }
        else
          return false;
    //if()
  }



  if (invalid == false)
  {
    thatSpace->setSpace(thisQueen);
    thisQueen->setEmpty();
    return true;
  }
  else
  {
    return false;
  }
}

bool Board::moveBishop(Square* thisBishop, Square* thatSpace) { //there might be problems with number of brackets
  int bishopX = thisBishop->getX();
  int bishopY = thisBishop->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  bool invalid = false;
  Square *s;
  if (abs(bishopX - thatX) == abs(bishopY - thatY))
  {
    int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
    int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

    for (int i = 1; i < abs(bishopX - thatX); i++)
    {
      std::cout << "It got here somehow";
      if (square[bishopX + xIncrement*i][bishopY + yIncrement*i].getColor() != NONE)
        return false;

    }
  }
  else
    return false;

  if (invalid == false)
  {
    thatSpace->setSpace(thisBishop);
    thisBishop->setEmpty();
    return true;
  }
  else
  {
    return false;
  }
}
bool Board::moveKnight(Square* thisKnight, Square* thatSpace)
{
  //off board inputs should be handled elsewhere (before this)
  //squares with same color should be handled elsewhere (before this)
  int knightX = thisKnight->getX();
  int knightY = thisKnight->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();

  if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
  {
    thatSpace->setSpace(thisKnight);
    thisKnight->setEmpty();
    return true;
  }
  else
  {
    return false;
  }
}

bool Board::moveRook(Square* thisRook, Square* thatSpace)
{
  //off board inputs should be handled elsewhere (before this)
  //squares with same color should be handled elsewhere (before this)
  int rookX = thisRook->getX();
  int rookY = thisRook->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  bool invalid = false;
  if (rookX != thatX || rookY != thatY)
  {

    if (rookX == thatX)
    {
      int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
      for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
      {

        if (square[thatX][i].getColor() != NONE)
          return false;

      }
    }
    else
      if (rookY == thatY)
      {

        int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
        for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
        {
          if (square[i][thatY].getColor() != NONE)
            return false;
        }
      }
      else
        return false;
  }
  if (invalid == false)
  {
    thatSpace->setSpace(thisRook);
    thisRook->setEmpty();
    return true;
  }
  else
  {//Return some erorr or something. Probably return false;
    std::cout << "That is an invalid move for rook";
    return false;
  }
}

bool Board::movePawn(Square* thisPawn, Square* thatSpace) {
  //off board inputs should be handled elsewhere (before this)
  //squares with same color should be handled elsewhere (before this)
  using namespace std;
  bool invalid = false;
  int pawnX = thisPawn->getX();
  int pawnY = thisPawn->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();


  if (thisPawn->getColor() == WHITE)
  {

    if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE)
    {
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      return true;
    }
    else
      if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY + 1 == thatY  && thatSpace->getColor() == BLACK)
      {
        thatSpace->setSpace(thisPawn);
        thisPawn->setEmpty();
        return true;
      }
      else
        return false;
  }
  else
    if (thisPawn->getColor() == BLACK)
    {
      if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE)
      {
        thatSpace->setSpace(thisPawn);
        thisPawn->setEmpty();
        return true;
      }
      else
        if ((pawnX + 1 == thatX || pawnX - 1 == thatX) && pawnY - 1 == thatY  && thatSpace->getColor() == WHITE)
        {
          thatSpace->setSpace(thisPawn);
          thisPawn->setEmpty();
          return true;
        }
        else
          return false;
    }
    else
      return false;
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
