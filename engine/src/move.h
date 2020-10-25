#pragma once

#include <cstdint>
#include <ostream>
#include <string>

#include "board.h"

#define MOVE_FROM_FILE_MASK 0xE000
#define MOVE_FROM_RANK_MASK 0x1C00
#define MOVE_DEST_FILE_MASK 0x0380
#define MOVE_DEST_RANK_MASK 0x0070

#define PROMOTE_KNIGHT_MASK 0x0004
#define PROMOTE_BISHOP_MASK 0x0005
#define PROMOTE_ROOK_MASK 0x0006
#define PROMOTE_QUEEN_MASK 0x0007

#define MOVE_CAPTURE_MASK 0x0008
#define MOVE_SPECIAL_MASK 0x000F

struct Move
{
  // First 6 bits are source square (first 3 are file, next 3 are rank)
  // Next 6 bits are destination square (same layout)
  // Next 2 bits are special move type bits. First indicates a capture, second is a pawn promotion
  // Last 2 bits are promotion type bits
  // 00: promote to knight, 01: promote to bishop, 10: promote to rook, 11: promote to queen
  uint16_t data;

  Move() {}
  Move(uint16_t d) : data(d) {}
  Move(Square from, Square dest, uint16_t special);
  Move(const Board &b, const std::string &s);

  Square fromSquare() const;
  Square destSquare() const;
};