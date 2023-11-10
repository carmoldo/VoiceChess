
// ARCHIVO CHESS.H
#include "definitions.cpp"

// -------- estructura square
Square::Square() {
  piece = EMPTY;
  color = NONE;

  // bool mano
  bool mano = false;
}

// -------- funcion setSpace de Square
void Square::setSpace(Square *space) {
  // ESTA FUNCION SE USA CUANDO QUIERO PASAR EL VALOR DEL COLOR Y LA PIECE A
  // OTRA CASILLA
  color = space->getColor(); // Copia el color del objeto 'space' al color de
                             // esta instancia
  piece = space->getPiece(); // Copia la pieza del objeto 'space' a la pieza de
                             // esta instancia
}

// -------- funcion getPiece de Piece Square
Piece Square::getPiece() { return piece; }

// -------- funcion getColor
Color Square::getColor() { return color; }

// -------- funcion setEmpty de Square
void Square::setEmpty() {
  color = NONE;
  piece = EMPTY;
}

// -------- funcion setSPieceAndColor
void Square::setPieceAndColor(Piece p, Color c) {
  piece = p;
  color = c;
}

// ------- funcion printBoard
void Board::printBoard() {
  using namespace std;
  cout << "   y: x  x  2  3  4  5  6  7 8 9 x x" << endl << "x:" << endl;
  for (int i = 0; i < 8; i++) {
    cout << " " << i << "   ";
    for (int j = 0; j < 12; j++) {
      Piece p = square[i][j].getPiece();
      Color c = square[i][j].getColor();

      switch (p)
      {
      case KING: (c == WHITE) ? cout << " K " : cout << " k ";
        break;
      case QUEEN: (c == WHITE) ? cout << " Q " : cout << " q ";
        break;
      case BISHOP:(c == WHITE) ? cout << " B " : cout << " b ";
        break;
      case KNIGHT:(c == WHITE) ? cout << " H " : cout << " h ";
        break;
      case ROOK: (c == WHITE) ? cout << " R " : cout << " r ";
        break;
      case PAWN: (c == WHITE) ? cout << " P " : cout << " p ";
        break;
      case EMPTY: cout << " " << "\21" << " ";
        break;
      default: cout << "XXX";
        break;
      }

    }
    cout << endl;
  }
}

// -------- funcion doMove
bool Board::doMove() {
  using namespace std;
  int x1, x2, y1, y2;
  string move;
  bool stop = false;

  while (!stop) {
    (turn == WHITE) ? cout << "White's turn" << endl
                    : cout << "Black's turn" << endl;
    cout << "Type in your move as a single four character string. Use "
            "x-coordinates first in each pair."
         << endl;
    cin >> move;

    cout << move;
    
    x1 = move[0] - 48;
    y1 = move[1] - 48;
    x2 = move[2] - 48;
    y2 = move[3] - 48;
    // si color x2 == turno.
    // Si si, realizar el move (funcion makeMove). Si move es invalid, "error".
    // Si move es válido, stop = true.
    // Tambien verifica que x2 y y2 sean distintos a 1, 2, 10 y 11
    if (y2 == 2 || y2 == 3 || y2 == 4 || y2 == 5 || y2 == 6 || y2 == 7 ||
        y2 == 8) {
      if (getSquare(x1, y1)->getColor() == turn) {
        if (makeMove(x1, y1, x2, y2) == false) {
          // Movimeinto invalido (moviste al caballo como peon, etc).
          cout << "Invalid move, try again (errormakeMove)." << endl;
        } else {
          stop = true;
        }
      } else {
        cout << "That's not your piece. Try again." << endl;
        // Cuando GetColor() != turn, no es tu pieza
      }
    } else {
      // y2 = 1, 2, 10 o 11.
      cout << "Invalid move, try again (Dead zone)." << endl;
    }

    if (getSquare(x2, y2)->getPiece() == KING)
    // If se muere KING
    {
      if (getSquare(x1, y1)->getColor() == WHITE) {
        cout << "WHITE WINS" << endl;
        return false;
        // Gana WHITE y se reinicia el juego
      } else {
        cout << "BLACK WINS" << endl;
        return false;
        // Gana BLACK y se reinicia el juego
      }
    }
  }

  if (turn == BLACK)
  // CAMBIA DE QUIEN ES EL TURNO
  {
    turn = WHITE;
  } else {
    turn = BLACK;
  }

  return true;
}

// -------- funcion setBoard
void Board::setBoard() {
  for (int i = 0; i < 12; i++)
    for (int j = 0; j < 12; j++) {
      square[i][j].setX(i);
      square[i][j].setY(j);
    }

  for (int i = 2; i < 8; i++) {
    for (int j = 0; j < 12; j++)
      square[j][i].setPieceAndColor(EMPTY, NONE);
  }

  square[0][2].setPieceAndColor(ROOK, WHITE);
  square[1][2].setPieceAndColor(KNIGHT, WHITE);
  square[2][2].setPieceAndColor(BISHOP, WHITE);
  square[3][2].setPieceAndColor(QUEEN, WHITE);
  square[4][2].setPieceAndColor(KING, WHITE);
  square[5][2].setPieceAndColor(BISHOP, WHITE);
  square[6][2].setPieceAndColor(KNIGHT, WHITE);
  square[7][2].setPieceAndColor(ROOK, WHITE);
  square[2][2].setMano(true); // Establece 'mano' en true
  
  square[0][9].setPieceAndColor(ROOK, BLACK);
  square[1][9].setPieceAndColor(KNIGHT, BLACK);
  square[2][9].setPieceAndColor(BISHOP, BLACK);
  square[3][9].setPieceAndColor(QUEEN, BLACK);
  square[4][9].setPieceAndColor(KING, BLACK);
  square[5][9].setPieceAndColor(BISHOP, BLACK);
  square[6][9].setPieceAndColor(KNIGHT, BLACK);
  square[7][9].setPieceAndColor(ROOK, BLACK);

  for (int i = 0; i < 8; i++) {
    square[i][3].setPieceAndColor(PAWN, WHITE);
    square[i][8].setPieceAndColor(PAWN, BLACK);
  }
}

// ----- funcion playGame
bool Board::playGame() {
  system("cls");
  printBoard();
  return doMove();
}

//----- funcion moveKing
bool Board:: moveKing(Square* thisKing, Square* thatSpace)
{
  // Esta función verifica si un rey puede moverse desde la casilla 'thisKing' a
  // la casilla 'thatSpace'. Comprueba si la diferencia absoluta en las
  // coordenadas X y Y entre thatSpace y thisKing es igual a 1
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

//----- funcion moveQueen
bool Board::moveQueen(Square *thisQueen, Square *thatSpace) {
  // there might be problems with numbers of brackets
  // off board inputs should be handled elsewhere (before this)
  // squares with same color should be handled elsewhere (before this)

  int queenX = thisQueen->getX();
  int queenY = thisQueen->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  std::cout << "this";
  int yIncrement;
  int xIncrement;
  bool invalid = false;
  
  if (queenX != thatX || queenY != thatY) {
    if (queenX == thatX) {
      yIncrement = (thatY - queenY) / (abs(thatY - queenY));
      for (int i = queenY + yIncrement; i != thatY; i += yIncrement) {
        if (square[thatX][i].getColor() != NONE)
          return false;
      }
    } else if (queenY == thatY) {
      xIncrement = (thatX - queenX) / (abs(thatX - queenX));
      for (int i = queenX + xIncrement; i != thatX; i += xIncrement) {
        if (square[i][thatY].getColor() != NONE)
          return false;
      }
    } else if (abs(queenX - thatX) == abs(queenY - thatY)) {
      xIncrement = (thatX - queenX) / (abs(thatX - queenX));
      yIncrement = (thatY - queenY) / (abs(thatY - queenY));

      for (int i = 1; i < abs(queenX - thatX); i++) {
        std::cout << "It got here somehow";
        if (square[queenX + xIncrement * i][queenY + yIncrement * i]
                .getColor() != NONE)
            return false;
      }
    } else
      return false;
    // if()
  }

  if (invalid == false) {
    thatSpace->setSpace(thisQueen);
    thisQueen->setEmpty();

    // ACA CAMBIO SET FICHAS MUERTAS
    setFichasMuertas(thatSpace, thisQueen); 

    return true;
  } else {
    return false;
  }
}

//----- funcion moveBishop
bool Board::moveBishop(
    Square *thisBishop,
    Square *thatSpace) { // there might be problems with number of brackets
  int bishopX = thisBishop->getX();
  int bishopY = thisBishop->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  bool invalid = false;
  Square *s;
  
  if (abs(bishopX - thatX) == abs(bishopY - thatY)) {
    int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
    int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

    for (int i = 1; i < abs(bishopX - thatX); i++) {
      std::cout << "It got here somehow";
      if (square[bishopX + xIncrement * i][bishopY + yIncrement * i]
              .getColor() != NONE)
        return false;
    }
  } else
    return false;

  if (invalid == false) {
    // AGREGUE ESTE IF
    if (thatSpace->getColor() != NONE && thatSpace->getColor() != thisBishop->getColor()) {
      setFichasMuertas(thatSpace, thisBishop);
    }
    
    thatSpace->setSpace(thisBishop);
    thisBishop->setEmpty();
    return true;
  } else {
    return false;
  }
}

//----- funcion moveKnight
bool Board::moveKnight(Square *thisKnight, Square *thatSpace) {
  // off board inputs should be handled elsewhere (before this)
  // squares with same color should be handled elsewhere (before this)
  int knightX = thisKnight->getX();
  int knightY = thisKnight->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();

  if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) ||
      (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2)) {
    thatSpace->setSpace(thisKnight);
    thisKnight->setEmpty();
    //ACA EL CAMBIO SET FICHAS MUERTAS
    setFichasMuertas(thatSpace, thisKnight);
    return true;
  } else {
    return false;
  }
}

//----- funcion moveRook
bool Board::moveRook(Square *thisRook, Square *thatSpace) {
  // off board inputs should be handled elsewhere (before this)
  // squares with same color should be handled elsewhere (before this)
  int rookX = thisRook->getX();
  int rookY = thisRook->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();
  bool invalid = false;
  if (rookX != thatX || rookY != thatY) {

    if (rookX == thatX) {
      int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
      for (int i = rookY + yIncrement; i != thatY; i += yIncrement) {

        if (square[thatX][i].getColor() != NONE)
          return false;
      }
    } else if (rookY == thatY) {

      int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
      for (int i = rookX + xIncrement; i != thatX; i += xIncrement) {
        if (square[i][thatY].getColor() != NONE)
          return false;
      }
    } else
      return false;
  }
  if (invalid == false) {
// ACA
    if (thatSpace->getColor() != NONE && thatSpace->getColor() != thisRook->getColor()) {
      setFichasMuertas(thatSpace, thisRook);
    }
    thatSpace->setSpace(thisRook);
    thisRook->setEmpty();
    return true;
  } else { // Return some erorr or something. Probably return false;
    std::cout << "That is an invalid move for rook";
    return false;
  }
}

//----- funcion movePawn
bool Board::movePawn(Square *thisPawn, Square *thatSpace) {
  // off board inputs should be handled elsewhere (before this)
  // squares with same color should be handled elsewhere (before this)
  using namespace std;
  bool invalid = false;
  int pawnX = thisPawn->getX();
  int pawnY = thisPawn->getY();
  int thatX = thatSpace->getX();
  int thatY = thatSpace->getY();

  if (thisPawn->getColor() == WHITE) {

    if (pawnX == thatX && thatY == pawnY + 1 && thatSpace->getColor() == NONE) {
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      return true;
    } else if ((pawnX + 1 == thatX || pawnX - 1 == thatX) &&
               pawnY + 1 == thatY && thatSpace->getColor() == BLACK) {
      // ACA LLAMO SETFICHASMUERTAS
      setFichasMuertas(thatSpace, thisPawn);
      
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      return true;
    } else
      return false;
  } else if (thisPawn->getColor() == BLACK) {
    if (pawnX == thatX && thatY == pawnY - 1 && thatSpace->getColor() == NONE) {
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      return true;
    } else if ((pawnX + 1 == thatX || pawnX - 1 == thatX) &&
               pawnY - 1 == thatY && thatSpace->getColor() == WHITE) {
      // ACA LLAMO SETFICHASMUERTAS
      setFichasMuertas(thatSpace, thisPawn);
      
      thatSpace->setSpace(thisPawn);
      thisPawn->setEmpty();
      return true;
    } else
      return false;
  } else
    return false;
}

bool Board::makeMove(int x1, int y1, int x2, int y2) {
  // Checking for turns will be done previous to this
  using namespace std;
  if (x1 < 0 || x1 > 8 || y1 < 0 || y1 > 8 || x2 < 0 || x2 > 8 || y2 < 0 ||
      y2 > 8) {
    std::cout << "One of your inputs was our of bounds" << std::endl;
    // Verifica que las coordenadas esten bien.
    return false;
  }
  // SRC es el lugar de inicio, dest es coordenadas de destino.
  Square *src = getSquare(x1, y1);
  Square *dest = getSquare(x2, y2);

  if (src->getColor() == dest->getColor() && dest->getColor() != NONE) {
    std::cout << "Invalid move: cannot land on your own piece" << std::endl;
    // ya hay una ficha de tu color en el square dest.
    return false;
  }

  switch (src->getPiece()) {
  case KING:
    return moveKing(src, dest);
    break;
  case QUEEN:
    return moveQueen(src, dest);
    break;
  case BISHOP:
    return moveBishop(src, dest);
    break;
  case KNIGHT:
    return moveKnight(src, dest);
    break;
  case ROOK:
    return moveRook(src, dest);
    break;
  case PAWN:
    return movePawn(src, dest);
    break;
  // ACA ES CUANDO NO HAY NINGUNA CASILLA ALLI
  case EMPTY:
    std::cout << "You do not have a piece there" << std::endl;
    return false;
    break;
  // ACA ES CUANDO... NO ES CASE NINGUNA DE LAS ANTERIORES
  default:
    std::cerr << "Something went wrong in the switch statement in makeMove()"
              << std::endl;
    break;
  }
  return false;
}

void Board::setFichasMuertas(Square *src, Square *dest) {
  if (dest->getColor() == WHITE) {
    // Busca una casilla vacía en la deadzone blanca (fila 9) y mueve la ficha a esa casilla.
    for (int x = 0; x < 8; x++) {
      Square *deadzoneSquare = &square[x][10];
      if (deadzoneSquare->getPiece() == EMPTY) {
        deadzoneSquare->setPieceAndColor(src->getPiece(), src->getColor()); // Configura el color correctamente
        src->setEmpty(); // Establece la casilla de origen como vacía
        break;
      }
    }

    for (int x = 0; x < 8; x++) {
      Square *deadzoneSquare = &square[x][11];
      if (deadzoneSquare->getPiece() == EMPTY) {
        deadzoneSquare->setPieceAndColor(src->getPiece(), src->getColor()); // Configura el color correctamente
        src->setEmpty(); // Establece la casilla de origen como vacía
        break;
      }
    }
  } else if (dest->getColor() == BLACK) {
    // Busca una casilla vacía en la deadzone negra (fila 2) y mueve la ficha a esa casilla.
    for (int x = 0; x < 8; x++) {
      Square *deadzoneSquare = &square[x][1];
      if (deadzoneSquare->getPiece() == EMPTY) {
        deadzoneSquare->setPieceAndColor(src->getPiece(), src->getColor()); // Configura el color correctamente
        src->setEmpty(); // Establece la casilla de origen como vacía
        break;
      }
    }

    for (int x = 0; x < 8; x++) {
      Square *deadzoneSquare = &square[x][0];
      if (deadzoneSquare->getPiece() == EMPTY) {
        deadzoneSquare->setPieceAndColor(src->getPiece(), src->getColor()); // Configura el color correctamente
        src->setEmpty(); // Establece la casilla de origen como vacía
        break;
      }
    }
  }
}

/*
Posibles errores piezas:
  - en passant
  - coronar (a cualquier ficha).
  - peon primer movimiento
  - enroque
Posibles errores generales:
  - entre el movimiento de la ficha y de la ficha muerta.
  - (primero tendria que ser el de la ficha muerta y despues el de la otra).

  
// Función para calcular cuántos casilleros debe mover la "mano".
void Board::MovimientoIRL(Square *src, Square *dest){
//  - variable de donde [x][x] esta la "mano".
//  - funciones del Movimiento (calcular el movimiento por hacer).
  // En chess.cpp
  void Board::MovimientoIRL(Square* src, Square* dest) {
      // Paso 2: Marcar el bool de mano en el origen (SRC)
      src->mano = true;

      // Paso 3: Determinar las funciones de mover un casillero y cuántas veces llamarlas
      int x_diff = dest->getX() - src->getX();
      int y_diff = dest->getY() - src->getY();

      // Llama a las funciones de mover casilleros según la diferencia en x e y
      for (int i = 0; i < abs(x_diff); i++) {
          if (x_diff > 0) {
              moverUnaCasillaDerecha();
          } else {
              moverUnaCasillaIzquierda();
          }
      }

      for (int i = 0; i < abs(y_diff); i++) {
          if (y_diff > 0) {
              moverUnaCasillaArriba();
          } else {
              moverUnaCasillaAbajo();
          }
      }

      // Paso 4: Desmarcar el bool de mano en todos los square y marcarlo como true en DEST
      for (int i = 0; i < 8; i++) {
          for (int j = 0; j < 12; j++) {
              square[i][j].mano = false;
          }
      }
      dest->mano = true;
  }
}
*/
