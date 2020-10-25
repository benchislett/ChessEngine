#include "movegen.h"
#include <iostream>

int pawnPushes(const Board &b, std::vector<Move> &moves)
{
  int moveCount = 0;
  for (int i = 0; i < MAX_PAWNS; i++)
  {
    Square pawn = b.pawnSquares[i][b.side];
    if (!pawn.isValid())
    {
      break;
    }

    uint8_t file = pawn.file();
    uint8_t rank = pawn.rank();

    if (rank == (b.side ? 6 : 1))
    {
      Square dest(file, rank + (b.side ? -2 : 2));
      if (!(b.occupancyBoards[2] & dest.bitboard()))
      {
        moves.emplace_back(pawn, dest, 0x00);
        moveCount++;
      }
    }

    if (b.side ? (rank > 1) : (rank < 6))
    {
      Square dest(file, rank + (b.side ? -1 : 1));
      if (!(b.occupancyBoards[2] & dest.bitboard()))
      {
        moves.emplace_back(pawn, dest, 0x00);
        moveCount++;
      }
    }
    else if (rank == (b.side ? 1 : 6))
    {
      Square dest(file, rank + (b.side
                                    ? -1
                                    : 1));
      if (!(b.occupancyBoards[2] & dest.bitboard()))
      {
        moves.emplace_back(pawn, dest, PROMOTE_KNIGHT_MASK);
        moves.emplace_back(pawn, dest, PROMOTE_BISHOP_MASK);
        moves.emplace_back(pawn, dest, PROMOTE_ROOK_MASK);
        moves.emplace_back(pawn, dest, PROMOTE_QUEEN_MASK);
        moveCount += 4;
      }
    }
  }
  return moveCount;
}

int pawnCaptures(const Board &b, std::vector<Move> &moves)
{
  int moveCount = 0;
  for (int i = 0; i < MAX_PAWNS; i++)
  {
    Square pawn = b.pawnSquares[i][b.side];
    if (!pawn.isValid())
    {
      break;
    }
    uint8_t file = pawn.file();
    uint8_t rank = pawn.rank();
    uint8_t attackFile;
    for (int direction = -1; direction < 2; direction += 2)
    {
      attackFile = file + direction;
      if (attackFile < 0 || attackFile > 7)
      {
        continue;
      }
      Square attack(attackFile, rank + (b.side ? 1 : -1));
      if (b.occupancyBoards[1 - b.side] & attack.bitboard())
      {
        if (b.side ? (rank > 1) : (rank < 6))
        {
          moves.emplace_back(pawn, attack, 0x00);
          moveCount++;
        }
        else if (b.side ? (rank == 1) : (rank == 6))
        {
          moves.emplace_back(pawn, attack, PROMOTE_KNIGHT_MASK);
          moves.emplace_back(pawn, attack, PROMOTE_BISHOP_MASK);
          moves.emplace_back(pawn, attack, PROMOTE_ROOK_MASK);
          moves.emplace_back(pawn, attack, PROMOTE_QUEEN_MASK);
          moveCount += 4;
        }
      }
    }
  }
  return moveCount;
}

int pawnMoves(const Board &b, std::vector<Move> &moves)
{
  return pawnPushes(b, moves) + pawnCaptures(b, moves);
}

int allMoves(const Board &b, std::vector<Move> &moves)
{
  return 0;
}
