#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QFutureWatcher>
#include <QSharedPointer>
#include <utility>

#include "gameboard.h"

using ValuePos_t = std::pair<int, std::pair<int, int>>;

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker()
    {
        watcher = QSharedPointer<QFutureWatcher<ValuePos_t>>::create(this);
        connect(watcher.data(), SIGNAL(resultReadyAt(int)), this, SLOT(resultReady(int)));
        connect(watcher.data(), SIGNAL(finished()), this, SLOT(watcherFinished()));
    };

    ~Worker()
    {
        //delete watcher;
    }

private:
    //std::pair<int, int> getBestMove(GameBoard&);
    const int max_thread_num = 4;
    const int step = 1;
    std::pair<int , std::pair<int, int> > result_queue[10];
    QSharedPointer<QFutureWatcher<ValuePos_t>> watcher;
    //QFutureWatcher<ValuePos_t> *watcher;

    void concurrentWrap(GameBoard&);
    void sequentialWrap1(GameBoard);
    void sequentialWrap2(GameBoard&);

signals:
    void newMove(std::pair<int, int>);

public slots:
    void makeMove(GameBoard);
    void resultReady(int);
    void watcherFinished();
};

#endif // WORKER_H
