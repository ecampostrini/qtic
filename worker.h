#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QFutureWatcher>
#include <QSharedPointer>
#include <utility>

#include "gameboard.h"


class Worker : public QObject
{
    Q_OBJECT

signals:
    void newMove(std::pair<int, int>);

public slots:
    void makeMove(GameBoard);
};

#endif // WORKER_H
