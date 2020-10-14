#pragma once

#include <cstdint>
#include <ostream>

struct Move
{
  // First 6 bits are source square (first 3 are file, next 3 are rank)
  // Next 6 bits are destination square (same layout)
  // Next 2 bits are unused move type bits, last 2 are promotion bits:
  // 00: promote to knight, 01: promote to bishop, 10: promote to rook, 11: promote to queen
  uint16_t data;

  Move() {}
  Move(uint16_t d) : data(d) {}
};