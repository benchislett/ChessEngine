#include "board.h"

template <int N>
void bitboardToPieceList(const uint64_t bitboard[2], uint8_t pieceList[N][2], int side)
{
  int counter = 0;
  for (int i = 0; i < 64; i++)
  {
    if (bitboard[side] & ((uint64_t)1 << i))
    {
      pieceList[counter++][side] = (uint8_t)(8 - i % 8) << 5 + (uint8_t)(i / 8) << 2;
    }
  }
  for (; counter < N; counter++)
  {
    pieceList[counter][side] = (uint8_t)0x03;
  }
}

void Board::resetBoard()
{
  pawnBoards[0] = (uint64_t)0xff << 8;
  pawnBoards[1] = (uint64_t)0xff << 48;

  knightBoards[0] = (uint64_t)0x42;
  knightBoards[1] = (uint64_t)0x42 << 56;

  bishopBoards[0] = (uint64_t)0x28;
  bishopBoards[1] = (uint64_t)0x28 << 56;

  rookBoards[0] = (uint64_t)0x81;
  rookBoards[1] = (uint64_t)0x81 << 56;

  queenBoards[0] = (uint64_t)0x10;
  queenBoards[1] = (uint64_t)0x10 << 56;

  kingBoards[0] = (uint64_t)0x8;
  kingBoards[1] = (uint64_t)0x8 << 56;

  computePieceLists();
}

void Board::computePieceLists()
{
  for (int side = 0; side < 2; side++)
  {
    bitboardToPieceList<MAX_PAWNS>(pawnBoards, pawnSquares, side);
    bitboardToPieceList<MAX_KNIGHTS>(knightBoards, knightSquares, side);
    bitboardToPieceList<MAX_BISHOPS>(bishopBoards, bishopSquares, side);
    bitboardToPieceList<MAX_ROOKS>(rookBoards, rookSquares, side);
    bitboardToPieceList<MAX_QUEENS>(queenBoards, queenSquares, side);
    bitboardToPieceList<MAX_KINGS>(kingBoards, kingSquares, side);
  }
}