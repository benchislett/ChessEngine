#include <catch2/catch.hpp>
#include <vector>

#include "../src/move.h"
#include "../src/movegen.h"

TEST_CASE("No pawn captures from initial position", "[movegen]")
{
  Board board;
  board.reset();

  std::vector<Move> moves;

  REQUIRE(pawnCaptures(board, moves) == 0);
}

TEST_CASE("Correct amount of initial pawn moves for white", "[movegen]")
{
  Board board;
  board.reset();

  std::vector<Move> moves;

  REQUIRE(pawnPushes(board, moves) == 16);
}

TEST_CASE("Correct amount of initial pawn moves for black", "[movegen]")
{
  Board board;
  board.reset();
  board.side = 1;

  std::vector<Move> moves;

  REQUIRE(pawnPushes(board, moves) == 16);
}