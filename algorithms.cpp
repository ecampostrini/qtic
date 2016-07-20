#include <QtDebug>
#include <utility>
#include <algorithm>

#include "gameboard.h"
#include "algorithms.h"

namespace Minimax
{

int minimax(GameBoard &board, const GameBoard::Player &currentPlayer)
{
    int result = (currentPlayer == GameBoard::Player::Human) ? 2 : -2;
    int score;

    if(board.score(score))
        return score;

    for(int i = 0; i < board.getRowNumber(); i++)
    {
        for(int j = 0; j < board.getColNumber(); j++)
        {
            int local_result;

            if(!board.isEmpty(i, j))
                continue;

            board.setSquare(i, j, currentPlayer);
            local_result = minimax(board, board.nextToPlay());
            board.clearSquare(i, j);

            if(currentPlayer == GameBoard::Player::Human)
            {
                if(local_result < result)
                    result = local_result;
            }
            else
            {
                if(local_result > result)
                    result = local_result;
            }
        }
    }

    return result;
}


auto getBestMove(GameBoard& board) -> std::pair<int, int>
{
    int result = -2;
    std::pair<int, int> best_move;

    for(int i = 0; i < board.getRowNumber(); i++)
        for(int j = 0; j < board.getColNumber(); j++)
        {
            int local_result;

            if(!board.isEmpty(i, j))
                continue;

            board.setSquare(i, j, GameBoard::Player::Machine);
            local_result = minimax(board, GameBoard::Player::Human);
            board.clearSquare(i, j);

            if(local_result > result)
            {
                result = local_result;
                best_move.first = i;
                best_move.second = j;
            }

        }

    return best_move;
}
}

namespace AlphaBeta
{

int minimax(GameBoard &board, const GameBoard::Player &currentPlayer, int min, int max)
{
    int result = (currentPlayer == GameBoard::Player::Human) ? 2 : -2;
    int score;

    if(board.score(score))
        return score;

    if(currentPlayer == GameBoard::Player::Human)
    {
        int local_result = 100;

        result = std::min(result, max);
        for(int i = 0; i < board.getRowNumber(); i++)
        {
            for(int j = 0; j < board.getColNumber(); j++)
            {
                if(!board.isEmpty(i, j))
                    continue;

                board.setSquare(i, j, currentPlayer);
                local_result = minimax(board, board.nextToPlay(), min, result);
                board.clearSquare(i, j);

                if(local_result < result) result = local_result;

                if(result > max) return max;


            }
        }
    }
    else
    {
        int local_result = -100;

        result = std::max(result, min);
        for(int i = 0; i < board.getRowNumber(); i++)
        {
            for(int j = 0; j < board.getColNumber(); j++)
            {
                if(!board.isEmpty(i, j))
                    continue;

                board.setSquare(i, j, currentPlayer);
                local_result = minimax(board, board.nextToPlay(), result, max);
                board.clearSquare(i, j);

                if(local_result > result) result = local_result;

                if(result < min) return min;

            }
        }
    }

    return result;
}

std::pair<int,int> getBestMove2(const AlgoArgs args)
{
    //we create local variables for the arguments
    GameBoard board = args.board;
    int from = args.from, to = args.to;
    int result = -2;
    std::pair<int, int> best_move;


    for(int i = from; i < to; i++)
        for(int j = 0; j < board.getColNumber(); j++)
        {
            int local_result;

            if(!board.isEmpty(i, j))
                continue;

            board.setSquare(i, j, GameBoard::Player::Machine);
            local_result = minimax(board, GameBoard::Player::Human, result, 100);
            board.clearSquare(i, j);

            if(local_result > result)
            {
                result = local_result;
                best_move.first = i;
                best_move.second = j;
            }

        }

    //emit newMove(best_move);
    return best_move;
    //return std::make_pair(best_move, result);
}

std::pair<int,int> getBestMove(GameBoard board, int from, int to)
{
    //we create local variables for the arguments
    int result = -2;
    std::pair<int, int> best_move;


    for(int i = from; i < to; i++)
        for(int j = 0; j < board.getColNumber(); j++)
        {
            int local_result;

            if(!board.isEmpty(i, j))
                continue;

            board.setSquare(i, j, GameBoard::Player::Machine);
            local_result = minimax(board, GameBoard::Player::Human, result, 100);
            board.clearSquare(i, j);

            if(local_result > result)
            {
                result = local_result;
                best_move.first = i;
                best_move.second = j;
            }

        }

    //emit newMove(best_move);
    return best_move;
    //return std::make_pair(best_move, result);
}

}
