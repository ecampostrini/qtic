#include <QDebug>
#include <utility>
#include <algorithm>

#include "worker.h"
#include "gameboard.h"
#include "algorithms.h"


/* slots */

void Worker::makeMove(GameBoard board)
{
    auto result = Minimax::getBestMove(board);

    emit newMove(result);
}
