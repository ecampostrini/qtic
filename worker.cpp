#include "worker.h"
#include "gameboard.h"


int Worker::minimax(GameBoard &board, const GameBoard::Player &currentPlayer)
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

/* slots */

void Worker::makeMove(GameBoard board)
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

    emit newMove(best_move);
}

