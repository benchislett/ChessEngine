#pragma once

#include <vector>

#include "move.h"
#include "board.h"

int pawnCaptures(const Board &b, std::vector<Move> &moves);
int pawnPushes(const Board &b, std::vector<Move> &moves);
int bishopMoves(const Board &b, std::vector<Move> &moves);
int knightMoves(const Board &b, std::vector<Move> &moves);
int rookMoves(const Board &b, std::vector<Move> &moves);
int queenMoves(const Board &b, std::vector<Move> &moves);
int kingMoves(const Board &b, std::vector<Move> &moves);
int allMoves(const Board &b, std::vector<Move> &moves);
