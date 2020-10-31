#include "make.h"

Board make(const Board &board, const Move move)
{
  Board newBoard = board;

  uint64_t fromBitboard = move.fromSquare().bitboard();
  uint64_t destBitboard = move.destSquare().bitboard();

  newBoard.pawnBoards[1 - board.side] &= ~destBitboard;
  newBoard.knightBoards[1 - board.side] &= ~destBitboard;
  newBoard.bishopBoards[1 - board.side] &= ~destBitboard;
  newBoard.rookBoards[1 - board.side] &= ~destBitboard;
  newBoard.queenBoards[1 - board.side] &= ~destBitboard;
  newBoard.kingBoards[1 - board.side] &= ~destBitboard;

  if (board.pawnBoards[board.side] & fromBitboard)
  {
    newBoard.pawnBoards[board.side] &= ~fromBitboard;
    if (move.data & PROMOTE_KNIGHT_MASK)
    {
      newBoard.knightBoards[board.side] |= destBitboard;
    }
    else if (move.data & PROMOTE_BISHOP_MASK)
    {
      newBoard.bishopBoards[board.side] |= destBitboard;
    }
    else if (move.data & PROMOTE_ROOK_MASK)
    {
      newBoard.rookBoards[board.side] |= destBitboard;
    }
    else if (move.data & PROMOTE_QUEEN_MASK)
    {
      newBoard.queenBoards[board.side] |= destBitboard;
    }
    else
    {
      newBoard.pawnBoards[board.side] |= destBitboard;
    }
  }
  else if (board.knightBoards[board.side] & fromBitboard)
  {
    newBoard.knightBoards[board.side] &= ~fromBitboard;
    newBoard.knightBoards[board.side] |= destBitboard;
  }
  else if (board.bishopBoards[board.side] & fromBitboard)
  {
    newBoard.bishopBoards[board.side] &= ~fromBitboard;
    newBoard.bishopBoards[board.side] |= destBitboard;
  }
  else if (board.rookBoards[board.side] & fromBitboard)
  {
    newBoard.rookBoards[board.side] &= ~fromBitboard;
    newBoard.rookBoards[board.side] |= destBitboard;
  }
  else if (board.queenBoards[board.side] & fromBitboard)
  {
    newBoard.queenBoards[board.side] &= ~fromBitboard;
    newBoard.queenBoards[board.side] |= destBitboard;
  }
  else if (board.kingBoards[board.side] & fromBitboard)
  {
    newBoard.kingBoards[board.side] &= ~fromBitboard;
    newBoard.kingBoards[board.side] |= destBitboard;
  }

  newBoard.computePieceLists();
}