//#include <QtConcurrent/QtConcurrentRun>
#include <QtConcurrent>
#include <QtConcurrent/QtConcurrentMap>
#include <QFuture>
#include <QFutureWatcher>
#include <QDebug>
#include <utility>
#include <algorithm>

#include "worker.h"
#include "gameboard.h"
#include "algorithms.h"

void Worker::concurrentWrap(GameBoard& board)
{
    QVector<AlphaBeta::AlgoArgs> args;


    for(int i = 0; i < board.getRowNumber(); i += step)
    {
        AlphaBeta::AlgoArgs newArg;

        newArg.from = i;
        newArg.to = std::min(i + step, board.getRowNumber());
        newArg.board = board;

        args.push_back(newArg);
    }

    watcher->setFuture(QtConcurrent::mapped(args.begin(), args.end(), AlphaBeta::getBestMove2));
    watcher->waitForFinished();
}


void Worker::sequentialWrap1(GameBoard board)
{
    AlphaBeta::AlgoArgs newArg;
    std::pair<int, std::pair<int, int> > result;

    newArg.from = 0;
    newArg.to = board.getRowNumber();
    newArg.board = board;

    result = AlphaBeta::getBestMove2(newArg);

    qDebug() << "sequential result" << result.second.first << " " << result.second.second;
    emit newMove(result.second);
}

void Worker::sequentialWrap2(GameBoard &board)
{
    auto result = AlphaBeta::getBestMove(board, 0, board.getRowNumber());

    emit newMove(result);
}

/* slots */

void Worker::makeMove(GameBoard board)
{
    concurrentWrap(board);
    //sequentialWrap1(board);
    //sequentialWrap2(board);
}

void Worker::resultReady(int pos)
{
    std::pair<int, std::pair<int, int> > result = watcher->resultAt(pos);
    result_queue[pos] = result;
    qDebug() << "thread in position " << pos << "has finished" << result.second.first << " " << result.second.second;
}

bool compare(std::pair<int, std::pair<int, int> > a, std::pair<int, std::pair<int, int> > b)
{
    return a.first < b.first;
}

void Worker::watcherFinished()
{
    auto result = std::max_element(result_queue, result_queue + max_thread_num, compare);
    //qDebug() << "max val" << result->first << "at" << result->second.first << " " << result->second.second;

    emit newMove(result->second);
}
