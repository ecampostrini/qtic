//#include <QtConcurrent/qtconcurrentthreadengine.h>
//#include <QtConcurrent/QtConcurrent>
//#include <QtConcurrent/QtConcurrentRun>
#include <QtConcurrent/QtConcurrentMap>
#include <QFuture>
#include <QFutureWatcher>
#include <QDebug>
#include <utility>

#include "worker.h"
#include "gameboard.h"
#include "algorithms.h"

void Worker::concurrentWrap2(GameBoard &board)
{
    /*
    QVector<AlphaBeta::AlgoArgs> args;
    int step = 1;

    connect(watcher, SIGNAL(resultReadyAt(int)), this, SLOT(resultReady(int)));

    for(int i = 0; i < max_thread_num; i += step)
    {
        //AlphaBeta::AlgoArgs newArg = AlphaBeta::AlgoArgs(i, i + step, board);
        AlphaBeta::AlgoArgs newArg;

        newArg.from = i;
        newArg.to = i + step;
        newArg.board = board;

        args.push_back(newArg);
    }

    watcher->setFuture(QtConcurrent::mapped(args.constBegin(), args.constEnd(), AlphaBeta::getBestMove));
    */
}

/*
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
}*/

void Worker::sequentialWrap1(GameBoard board)
{
    //auto result = AlphaBeta::getBestMove(AlphaBeta::AlgoArgs(0, board.getRowNumber(), board));
    AlphaBeta::AlgoArgs newArg;
    std::pair<int, int> result;

    newArg.from = 0;
    newArg.to = board.getRowNumber();
    newArg.board = board;

    result = AlphaBeta::getBestMove(newArg);

    emit newMove(result);
}

void Worker::sequentialWrap2(GameBoard &board)
{
    auto result = AlphaBeta::getBestMove(board, 0, board.getRowNumber());

    emit newMove(result);
}

/* slots */

void Worker::makeMove(GameBoard board)
{
    //concurrentWrap2(board);
    //concurrentWrap(board);
    qDebug() << "pre";
    sequentialWrap1(board);
    qDebug() << "post";
    //sequentialWrap2(board);
}

void Worker::resultReady(int)
{
    qDebug() << "a thread has finished";
}
