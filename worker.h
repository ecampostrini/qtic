#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QFutureWatcher>
#include <utility>

#include "gameboard.h"

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker()
    {
        //watcher = new QFutureWatcher<std::pair<int, int> >();
    };

    ~Worker()
    {
        //delete watcher;
    }

private:
    //std::pair<int, int> getBestMove(GameBoard&);
    const int max_thread_num = 3;
    const int step = 1;
    //QFutureWatcher<std::pair<int, int> > *watcher;

    void concurrentWrap2(GameBoard&);
    //void concurrentWrap(GameBoard&);
    void sequentialWrap1(GameBoard);
    void sequentialWrap2(GameBoard&);

signals:
    void newMove(std::pair<int, int>);

public slots:
    void makeMove(GameBoard);
    void resultReady(int);
};

#endif // WORKER_H
