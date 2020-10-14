#pragma once

#include <cstdint>
#include <ostream>

struct Move
{
  uint16_t data;

  Move() {}
  Move(uint16_t d) : data(d) {}
};