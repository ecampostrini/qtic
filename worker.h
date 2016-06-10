#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <utility>

#include "ai.h"

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(){};

private:
    int minimax(GameBoard &, const GameBoard::Player&);

signals:
    void newMove(std::pair<int, int>);

public slots:
    void makeMove(GameBoard);
};

#endif // WORKER_H
