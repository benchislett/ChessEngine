#pragma once

#include <cstdint>
#include <ostream>

#define MAX_PAWNS 8
#define MAX_KNIGHTS 10
#define MAX_BISHOPS 10
#define MAX_ROOKS 10
#define MAX_QUEENS 9
#define MAX_KINGS 2

#define INVALID_SQUARE ((uint8_t)0x03)

struct Square {
  // Leftmost 3 bits are file, next 3 are rank, and last 2 are validity bits
  // So, 0x03 is the invalid square (no piece)
  uint8_t location;

  Square() {}
  Square(uint8_t l) : location(l) {}
};

std::ostream& operator<<(std::ostream& os, const Square square);

struct Board
{
  // Bitboards
  // Each bit represents whether there is or is not a piece on that square
  // Squares are indexed such that 0x01 (0b00000001) is a8, 0x80 (0b10000000) is a1, and
  // Moving up one file is equivalent to shifting left 8 bits (one rank) 
  //
  // [ White, Black ]
  uint64_t pawnBoards[2];
  uint64_t knightBoards[2];
  uint64_t bishopBoards[2];
  uint64_t rookBoards[2];
  uint64_t queenBoards[2];
  uint64_t kingBoards[2];

  // Piece Lists
  // Hardcoded arrays of pieces by square
  // 
  // [ White, Black ]
  Square pawnSquares[MAX_PAWNS][2];
  Square knightSquares[MAX_KNIGHTS][2];
  Square bishopSquares[MAX_BISHOPS][2];
  Square rookSquares[MAX_ROOKS][2];
  Square queenSquares[MAX_QUEENS][2];
  Square kingSquares[MAX_KINGS][2];

  Board() {}

  void resetBoard();

  void computePieceLists();
};

std::ostream& operator<<(std::ostream& os, const Board board);