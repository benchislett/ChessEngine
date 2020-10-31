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
          moves.emplace_back(pawn, attack, MOVE_CAPTURE_MASK);
          moveCount++;
        }
        else if (b.side ? (rank == 1) : (rank == 6))
        {
          moves.emplace_back(pawn, attack, MOVE_CAPTURE_MASK | PROMOTE_KNIGHT_MASK);
          moves.emplace_back(pawn, attack, MOVE_CAPTURE_MASK | PROMOTE_BISHOP_MASK);
          moves.emplace_back(pawn, attack, MOVE_CAPTURE_MASK | PROMOTE_ROOK_MASK);
          moves.emplace_back(pawn, attack, MOVE_CAPTURE_MASK | PROMOTE_QUEEN_MASK);
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

int knightMoves(const Board &b, std::vector<Move> &moves)
{
  constexpr uint8_t diffs[][2] = {{1, 2}, {1, -2}, {2, 1}, {-2, 1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}};

  int moveCount = 0;
  for (int i = 0; i < MAX_KNIGHTS; i++)
  {
    Square knight = b.knightSquares[i][b.side];
    if (!knight.isValid())
    {
      break;
    }
    for (auto &pair : diffs)
    {
      uint8_t file = knight.file() + pair[0];
      uint8_t rank = knight.rank() + pair[1];
      if (file < 0 || file > 7 || rank < 0 || rank > 7)
      {
        continue;
      }
      Square dest(file, rank);
      if (b.occupancyBoards[1 - b.side] & dest.bitboard())
      {
        moves.emplace_back(knight, dest, MOVE_CAPTURE_MASK);
      }
      else if (!(b.occupancyBoards[b.side] & dest.bitboard()))
      {
        moves.emplace_back(knight, dest, 0x00);
      }
    }
  }
}

int bishopMoves(const Board &b, std::vector<Move> &moves)
{
  constexpr uint8_t diffs[][2] = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}, {-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}, {-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}};

  int moveCount = 0;
  for (int i = 0; i < MAX_BISHOPS; i++)
  {
    Square bishop = b.bishopSquares[i][b.side];
    if (!bishop.isValid())
    {
      break;
    }
    for (auto &pair : diffs)
    {
      uint8_t file = bishop.file() + pair[0];
      uint8_t rank = bishop.rank() + pair[1];
      if (file < 0 || file > 7 || rank < 0 || rank > 7)
      {
        continue;
      }
      Square dest(file, rank);
      if (b.occupancyBoards[1 - b.side] & dest.bitboard())
      {
        moves.emplace_back(bishop, dest, MOVE_CAPTURE_MASK);
      }
      else if (!(b.occupancyBoards[b.side] & dest.bitboard()))
      {
        moves.emplace_back(bishop, dest, 0x00);
      }
    }
  }
}

int rookMoves(const Board &b, std::vector<Move> &moves)
{
  constexpr uint8_t diffs[][2] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}, {-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}};

  int moveCount = 0;
  for (int i = 0; i < MAX_ROOKS; i++)
  {
    Square rook = b.rookSquares[i][b.side];
    if (!rook.isValid())
    {
      break;
    }
    for (auto &pair : diffs)
    {
      uint8_t file = rook.file() + pair[0];
      uint8_t rank = rook.rank() + pair[1];
      if (file < 0 || file > 7 || rank < 0 || rank > 7)
      {
        continue;
      }
      Square dest(file, rank);
      if (b.occupancyBoards[1 - b.side] & dest.bitboard())
      {
        moves.emplace_back(rook, dest, MOVE_CAPTURE_MASK);
      }
      else if (!(b.occupancyBoards[b.side] & dest.bitboard()))
      {
        moves.emplace_back(rook, dest, 0x00);
      }
    }
  }
}

int queenMoves(const Board &b, std::vector<Move> &moves)
{
  constexpr uint8_t diffs[][2] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}, {0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}, {-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}, {1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}, {-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}, {-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}};

  int moveCount = 0;
  for (int i = 0; i < MAX_QUEENS; i++)
  {
    Square queen = b.queenSquares[i][b.side];
    if (!queen.isValid())
    {
      break;
    }
    for (auto &pair : diffs)
    {
      uint8_t file = queen.file() + pair[0];
      uint8_t rank = queen.rank() + pair[1];
      if (file < 0 || file > 7 || rank < 0 || rank > 7)
      {
        continue;
      }
      Square dest(file, rank);
      if (b.occupancyBoards[1 - b.side] & dest.bitboard())
      {
        moves.emplace_back(queen, dest, MOVE_CAPTURE_MASK);
      }
      else if (!(b.occupancyBoards[b.side] & dest.bitboard()))
      {
        moves.emplace_back(queen, dest, 0x00);
      }
    }
  }
}

int kingMoves(const Board &b, std::vector<Move> &moves)
{
  constexpr uint8_t diffs[][2] = {{1, 1}, {1, 0}, {1, -1}, {0, -1}, {0, 1}, {-1, -1}, {-1, 0}, {-1, 1}};

  int moveCount = 0;
  for (int i = 0; i < MAX_KINGS; i++)
  {
    Square king = b.kingSquares[i][b.side];
    if (!king.isValid())
    {
      break;
    }
    for (auto &pair : diffs)
    {
      uint8_t file = king.file() + pair[0];
      uint8_t rank = king.rank() + pair[1];
      if (file < 0 || file > 7 || rank < 0 || rank > 7)
      {
        continue;
      }
      Square dest(file, rank);
      if (b.occupancyBoards[1 - b.side] & dest.bitboard())
      {
        moves.emplace_back(king, dest, MOVE_CAPTURE_MASK);
      }
      else if (!(b.occupancyBoards[b.side] & dest.bitboard()))
      {
        moves.emplace_back(king, dest, 0x00);
      }
    }
  }
}

int allMoves(const Board &b, std::vector<Move> &moves)
{
  return pawnMoves(b, moves) + knightMoves(b, moves) + bishopMoves(b, moves) + rookMoves(b, moves) + queenMoves(b, moves) + kingMoves(b, moves);
}
