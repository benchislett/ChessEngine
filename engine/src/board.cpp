#include "board.h"

Square::Square(uint8_t file, uint8_t rank)
{
  location = (file << 5) | (rank << 2);
}

bool Square::isValid() const
{
  return location != INVALID_SQUARE;
}

uint8_t Square::file() const
{
  return (location & SQUARE_FILE_MASK) >> 5;
}

uint8_t Square::rank() const
{
  return (location & SQUARE_RANK_MASK) >> 2;
}

uint64_t Square::bitboard() const
{
  return (uint64_t)1 << (7 - file() + 8 * rank());
}

std::ostream &operator<<(std::ostream &os, const Square square)
{
  uint8_t file = (square.location & ((uint8_t)0xE0)) >> 5;
  uint8_t rank = (square.location & ((uint8_t)0x1C)) >> 2;

  if (square.location == INVALID_SQUARE)
  {
    os << "00";
  }
  else
  {
    os.put('a' + (char)file);
    os << (int)rank + 1;
  }

  return os;
}

template <int N>
void bitboardToPieceList(const uint64_t bitboard[2], Square pieceList[N][2], int side)
{
  int counter = 0;
  for (int i = 0; i < 64; i++)
  {
    if (bitboard[side] & ((uint64_t)1 << i))
    {
      pieceList[counter++][side] = {(uint8_t)((uint8_t)((uint8_t)(7 - i % 8) << 5) | (uint8_t)((uint8_t)(i / 8) << 2))};
    }
  }
  for (; counter < N; counter++)
  {
    pieceList[counter][side] = {INVALID_SQUARE};
  }
}

void Board::reset()
{
  pawnBoards[0] = (uint64_t)0xff << 8;
  pawnBoards[1] = (uint64_t)0xff << 48;

  knightBoards[0] = (uint64_t)0x42;
  knightBoards[1] = (uint64_t)0x42 << 56;

  bishopBoards[0] = (uint64_t)0x24;
  bishopBoards[1] = (uint64_t)0x24 << 56;

  rookBoards[0] = (uint64_t)0x81;
  rookBoards[1] = (uint64_t)0x81 << 56;

  queenBoards[0] = (uint64_t)0x10;
  queenBoards[1] = (uint64_t)0x10 << 56;

  kingBoards[0] = (uint64_t)0x8;
  kingBoards[1] = (uint64_t)0x8 << 56;

  occupancyBoards[0] = pawnBoards[0] | knightBoards[0] | bishopBoards[0] | rookBoards[0] | queenBoards[0] | kingBoards[0];
  occupancyBoards[1] = pawnBoards[1] | knightBoards[1] | bishopBoards[1] | rookBoards[1] | queenBoards[1] | kingBoards[1];
  occupancyBoards[2] = occupancyBoards[0] | occupancyBoards[1];

  computePieceLists();

  side = 0;
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

std::ostream &operator<<(std::ostream &os, const Board board)
{
  for (int rank = 7; rank >= 0; rank--)
  {
    for (int file = 0; file < 8; file++)
    {
      uint64_t mask = ((uint64_t)1 << (7 - file)) << (8 * rank);
      if (board.pawnBoards[0] & mask)
      {
        os << "P ";
      }
      else if (board.pawnBoards[1] & mask)
      {
        os << "p ";
      }
      else if (board.knightBoards[0] & mask)
      {
        os << "N ";
      }
      else if (board.knightBoards[1] & mask)
      {
        os << "n ";
      }
      else if (board.bishopBoards[0] & mask)
      {
        os << "B ";
      }
      else if (board.bishopBoards[1] & mask)
      {
        os << "b ";
      }
      else if (board.rookBoards[0] & mask)
      {
        os << "R ";
      }
      else if (board.rookBoards[1] & mask)
      {
        os << "r ";
      }
      else if (board.queenBoards[0] & mask)
      {
        os << "Q ";
      }
      else if (board.queenBoards[1] & mask)
      {
        os << "q ";
      }
      else if (board.kingBoards[0] & mask)
      {
        os << "K ";
      }
      else if (board.kingBoards[1] & mask)
      {
        os << "k ";
      }
      else
      {
        os << ". ";
      }
    }
    os << "\n";
  }
  return os;
}
