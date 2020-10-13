#pragma once

#include <cstdint>

#define MAX_PAWNS 8
#define MAX_KNIGHTS 10
#define MAX_BISHOPS 10
#define MAX_ROOKS 10
#define MAX_QUEENS 9
#define MAX_KINGS 2

struct Move
{
  uint16_t data;
};

struct Board
{
  // Bitboards
  //
  // [ White, Black ]
  uint64_t pawnBoards[2];
  uint64_t knightBoards[2];
  uint64_t bishopBoards[2];
  uint64_t rookBoards[2];
  uint64_t queenBoards[2];
  uint64_t kingBoards[2];

  // Piece Lists
  uint8_t pawnSquares[MAX_PAWNS][2];
  uint8_t knightSquares[MAX_KNIGHTS][2];
  uint8_t bishopSquares[MAX_BISHOPS][2];
  uint8_t rookSquares[MAX_ROOKS][2];
  uint8_t queenSquares[MAX_QUEENS][2];
  uint8_t kingSquares[MAX_KINGS][2];

  Board() {}

  void resetBoard();

  void computePieceLists();
};
