#include <catch2/catch.hpp>
#include <sstream>

#include "../src/board.h"

TEST_CASE("Board has correct initial state", "[board]")
{
  Board board;
  board.reset();

  std::stringstream out;
  out << board;

  const char *initialBoard =
      "r n b q k b n r \n"
      "p p p p p p p p \n"
      ". . . . . . . . \n"
      ". . . . . . . . \n"
      ". . . . . . . . \n"
      ". . . . . . . . \n"
      "P P P P P P P P \n"
      "R N B Q K B N R \n";

  REQUIRE_THAT(out.str(), Catch::Matchers::Equals(initialBoard));
}
