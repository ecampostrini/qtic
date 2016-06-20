#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QDebug>
#include <utility>

#include "worker.h"
#include "gameboard.h"
#include "algorithms.h"

void Worker::concurrentWrap(GameBoard &board)
{
    std::pair<int, int> result;
    QFuture<std::pair<std::pair<int, int>, int > > f1 = QtConcurrent::run(AlphaBeta::getBestMove, board, 0, 1),
                                                   f2 = QtConcurrent::run(AlphaBeta::getBestMove, board, 1, 2),
                                                   f3 = QtConcurrent::run(AlphaBeta::getBestMove, board, 2, 3);
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

void Worker::sequentialWrap(GameBoard &board)
{
    auto result = AlphaBeta::getBestMove(board, 0, board.getRowNumber());

    emit newMove(result.first);

}

/* slots */

void Worker::makeMove(GameBoard board)
{
    concurrentWrap(board);
    //sequentialWrap(board);
}

