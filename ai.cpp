#include <QtDebug>
#include <cassert>

#include "ai.h"


/**** Board methods *******/
bool GameBoard::hasWinner()
{
    //Checks the rows
    for(int i = 0; i < rowNum; i++)
        if(game_board[i][0] != '\0' && game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2])
            return true;

    //Checks the columns
    for(int i = 0; i < colNum; i++)
        if(game_board[0][i] != '\0' && game_board[0][i] == game_board[1][i] && game_board[1][i] == game_board[2][i])
            return true;

    //Checks the diagonals
    if((game_board[0][0] != '\0' && game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) ||
        (game_board[0][2] != '\0' && game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0]))
        return true;

    return false;
}

void GameBoard::setSquare(int row, int col, const char val)
{
    assert(isEmpty(row, col) && "Trying to set a used squared");
    game_board[row][col] = val;
    freeBoxes--;
};

void GameBoard::clearSquare(int row, int col)
{
    assert(!isEmpty(row, col) && "Trying to clear a free square");
    game_board[row][col] = '\0';
    freeBoxes++;
}



/***** AI methods *********/
Ai::~Ai(){}

std::pair<int, int> Ai::nextMove(GameBoard* board)
{
    int result = -2;
    std::pair<int, int> best_move;

    for(int i = 0; i < board->getRowNumber(); i++)
        for(int j = 0; j < board->getColNumber(); j++)
        {
            int local_result;

            if(!board->isEmpty(i, j))
                continue;

            board->setSquare(i, j, 'O');
            local_result = minimize(board);
            board->clearSquare(i, j);

            if(local_result > result)
            {
                result = local_result;
                best_move.first = i;
                best_move.second = j;
            }

        }

    return best_move;
}

int Ai::minimize(GameBoard* board)
{
    int result = 2;

    if(board->hasWinner())
        return 1;
    else if(!board->hasPlace())
        return 0;

    for(int i = 0; i < board->getRowNumber(); i++)
        for(int j = 0; j < board->getColNumber(); j++)
        {
            int local_result;

            if(!board->isEmpty(i, j))
                continue;

            board->setSquare(i, j, 'X');
            local_result = maximize(board);
            board->clearSquare(i, j);

            if(local_result < result)
            {
                result = local_result;
            }
        }

    return result;
}

int Ai::maximize(GameBoard* board)
{
    int result = -2;

    if(board->hasWinner())
        return -1;
    else if(!board->hasPlace())
        return 0;

    for(int i = 0; i < board->getRowNumber(); i++)
        for(int j = 0; j < board->getColNumber(); j++)
        {
            int local_result;

            if(!board->isEmpty(i, j))
                continue;

            board->setSquare(i, j, 'O');
            local_result = minimize(board);
            board->clearSquare(i, j);

            if(local_result > result)
            {
                result = local_result;
            }
        }

    return result;
}
