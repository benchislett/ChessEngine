#pragma once

#include <cstdint>
#include <ostream>
#include <string>

#include "board.h"

#define PROMOTE_KNIGHT_MASK 0x00
#define PROMOTE_BISHOP_MASK 0x01
#define PROMOTE_ROOK_MASK 0x02
#define PROMOTE_QUEEN_MASK 0x03

#define MOVE_FROM_FILE_MASK 0xE000
#define MOVE_FROM_RANK_MASK 0x1C00
#define MOVE_DEST_FILE_MASK 0x0380
#define MOVE_DEST_RANK_MASK 0x0070
#define MOVE_SPECIAL_MASK 0x000F

struct Move
{
  // First 6 bits are source square (first 3 are file, next 3 are rank)
  // Next 6 bits are destination square (same layout)
  // Next 2 bits are unused move type bits, last 2 are promotion bits:
  // 00: promote to knight, 01: promote to bishop, 10: promote to rook, 11: promote to queen
  uint16_t data;

  Move() {}
  Move(uint16_t d) : data(d) {}
  Move(Square from, Square dest, uint16_t special);
  Move(const std::string &s);

  Square fromSquare() const;
  Square destSquare() const;
};