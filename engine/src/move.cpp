#include "move.h"

Move::Move(Square from, Square dest, uint16_t special)
{
  data = (((uint16_t)from.location) << 8) |
         (((uint16_t)dest.location) << 2) |
         special;
}

Move::Move(const Board &b, const std::string &s)
{
  uint16_t fromFile = s.at(0) - 'a';
  uint16_t destFile = s.at(2) - 'a';

  uint16_t fromRank = s.at(1) - '1';
  uint16_t destRank = s.at(3) - '1';

  uint16_t special = 0x00;

  Square dest(destFile, destRank);
  if (b.occupancyBoards[2] & dest.bitboard())
  {
    special |= MOVE_CAPTURE_MASK;
  }

  if (s.length() > 4)
  {
    if (s.at(4) == 'q' || s.at(4) == 'Q')
    {
      special |= PROMOTE_QUEEN_MASK;
    }
    else if (s.at(4) == 'r' || s.at(4) == 'R')
    {
      special |= PROMOTE_ROOK_MASK;
    }
    else if (s.at(4) == 'b' || s.at(4) == 'B')
    {
      special |= PROMOTE_BISHOP_MASK;
    }
    else if (s.at(4) == 'n' || s.at(4) == 'N')
    {
      special |= PROMOTE_KNIGHT_MASK;
    }
  }

  data = ((fromFile & 0x07) << 13) |
         ((fromRank & 0x07) << 10) |
         ((destFile & 0x07) << 7) |
         ((destRank & 0x07) << 4) |
         (special & MOVE_SPECIAL_MASK);
}

Square Move::fromSquare() const
{
  uint8_t fromFile = (data & MOVE_FROM_FILE_MASK) >> 8;
  uint8_t fromRank = (data & MOVE_FROM_RANK_MASK) >> 11;
  return {(uint8_t)(fromFile | fromRank)};
}

Square Move::destSquare() const
{
  uint8_t destFile = (data & MOVE_DEST_FILE_MASK) >> 2;
  uint8_t destRank = (data & MOVE_DEST_RANK_MASK) << 1;
  return {(uint8_t)(destFile | destRank)};
}