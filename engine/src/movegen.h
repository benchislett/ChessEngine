#pragma once

#include <vector>

#include "move.h"
#include "board.h"

int pawnCaptures(const Board &b, std::vector<Move> &moves);
int pawnPushes(const Board &b, std::vector<Move> &moves);
int legalMoves(const Board &b, std::vector<Move> &moves);
int allMoves(const Board &b, std::vector<Move> &moves);
