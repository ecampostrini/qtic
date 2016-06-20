#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <utility>

#include "gameboard.h"

namespace Minimax
{
    std::pair<std::pair<int,int>, int> getBestMove(GameBoard board, int from, int to);
}

namespace AlphaBeta
{
    std::pair<std::pair<int,int>, int> getBestMove(GameBoard board, int from, int to);
}

#endif // ALGORITHMS_H
