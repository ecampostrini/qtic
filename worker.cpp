#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QDebug>
#include <utility>

#include "worker.h"
#include "gameboard.h"

namespace
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

std::pair<std::pair<int,int>, int> getBestMove(GameBoard &board, int from, int to)
{
    int result = -2;
    std::pair<int, int> best_move;

    for(int i = from; i < to; i++)
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

    //emit newMove(best_move);
    //return best_move;
    return std::make_pair(best_move, result);
}
}

void Worker::concurrentWrap(GameBoard &board)
{
    QFuture<std::pair<std::pair<int, int>, int > >f1 = QtConcurrent::run(getBestMove, board, 0, 1),
                                  f2 = QtConcurrent::run(getBestMove, board, 1, 2),
                                  f3 = QtConcurrent::run(getBestMove, board, 2, 3);
    std::pair<int, int> result;
    auto r1 = f1.result(),
         r2 = f2.result(),
         r3 = f3.result();

    if(r1.second > r2.second)
        if(r1.second > r3.second)
            result = r1.first;
        else
            result = r3.first;
    else if(r2.second > r3.second)
        result = r2.first;
    else
        result = r3.first;


    emit newMove(result);
}

/* slots */

void Worker::makeMove(GameBoard board)
{
    concurrentWrap(board);
}

