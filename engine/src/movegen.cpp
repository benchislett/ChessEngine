#include "movegen.h"

int allMoves(const Board &b, std::vector<Move> &moves)
{
}

int pawnMoves(const Board &b, std::vector<Move> &moves)
{
  return pawnPushesForSide(b, 0, moves) + pawnPushesForSide(b, 1, moves) + pawnCapturesForSide(b, 0, moves) + pawnCapturesForSide(b, 1, moves);
}

int pawnPushesForSide(const Board &b, int side, std::vector<Move> &moves)
{
  int moveCount = 0;
  Square pawn = b.pawnSquares[0][side];
  for (int i = 0; i < MAX_PAWNS && pawn.isValid(); i++, pawn = b.pawnSquares[i][side])
  {
    uint8_t file = pawn.file();
    uint8_t rank = pawn.rank();
    if (rank == 1)
    {
      Square dest(file, rank + 2);
      if (!(b.occupancyBoards[2] & dest.bitboard()))
      {
        moves.emplace_back(pawn, dest, 0x00);
        moveCount++;
      }
    }

    if (rank < 6)
    {
      Square dest(file, rank + 1);
      if (!(b.occupancyBoards[2] & dest.bitboard()))
      {
        moves.emplace_back(pawn, dest, 0x00);
        moveCount++;
      }
    }
    else if (rank == 6)
    {
      Square dest(file, rank + 1);
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

int pawnCapturesForSide(const Board &b, int side, std::vector<Move> &moves)
{
  int moveCount = 0;
  Square pawn = b.pawnSquares[0][side];
  for (int i = 0; i < MAX_PAWNS && pawn.isValid(); i++, b.pawnSquares[i][side])
  {
    uint8_t file = pawn.file();
    uint8_t rank = pawn.rank();
    uint8_t attackFile;
    for (int direction = -1; direction < 2; direction += 2)
    {
      if (file + direction < 0 || file + direction > 7)
      {
        continue;
      }
      Square attack(file + direction, rank);
      if (b.occupancyBoards[1 - side] & attack.bitboard())
      {
        if (rank < 6)
        {
          moves.emplace_back(pawn, attack, 0x00);
          moveCount++;
        }
        else if (rank == 6)
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