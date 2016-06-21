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
    typedef struct NoName
    {
        int from;
        int to;
        GameBoard board;
        /*NoName();
        NoName (int f, int t, GameBoard b) : from(f), to(t), board(b) {}
        NoName(const NoName& other)
        {
            from = other.from;
            to = other.to;
            board = other.board;
        }*/
    } AlgoArgs;


    std::pair<int,int> getBestMove(GameBoard board, int from, int to);
    std::pair<int,int> getBestMove2(const AlgoArgs args);
}

#endif // ALGORITHMS_H
