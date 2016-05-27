#include <QtDebug>
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


/***** AI methods *********/
Ai::~Ai(){}

bool Ai::getNextMove(GameBoard &board, std::pair<int, int> &result)
{
    for(int i = 0; i < board.getRowNumber(); i++)
        for(int j = 0; j < board.getColNumber(); j++)
        {
            if(board.getValue(i, j) == '\0')
            {
                result.first = i;
                result.second = j;
                return true;
            }
        }

    return false;
}

std::pair<int, int> Ai::minimax(GameBoard *board)
{
    int result = -1;
    std::pair<int, int> best_move;

    qDebug() << "rows" << board->getRowNumber();
    qDebug() << "cols" << board->getColNumber();
    for(int i = 0; i < board->getRowNumber(); i++)
        for(int j = 0; j < board->getColNumber(); j++)
        {
            qDebug() << "Minimax guacho !";
            int local_result;

            if(!board->isEmpty(i, j))
                continue;

            board->setSquare(i, j, 'O');
            if(result != 1 && (local_result = minimize(board)) > result)
            {
                result = local_result;
                best_move.first = i;
                best_move.second = j;
            }
            board->clearSquare(i, j);
        }

    return best_move;
}

int Ai::maximize(GameBoard *board)
{
    int result = 0;

    if(board->hasWinner())
        return -1;

    qDebug() << "Maximizing";
    for(int i = 0; i < board->getRowNumber(); i++)
    {
        for(int j = 0; j < board->getColNumber(); j++)
        {
            int local_result;

            if(!board->isEmpty(i, j))
                continue;

            board->setSquare(i, j, 'O');
            if( result != 1 && (local_result = minimize(board)) > result)
            {
                result = local_result;
            }
            board->clearSquare(i, j);
        }
    }

    return result;
}

int Ai::minimize(GameBoard *board)
{
    int result = 0;

    if(board->hasWinner())
        return 1;

    qDebug() << "Minimizing";
    for(int i = 0; i < board->getRowNumber(); i++)
        for(int j = 0; j < board->getColNumber(); j++)
        {
            int local_result;

            if(!board->isEmpty(i, j))
                continue;

            board->setSquare(i, j, 'X');
            if(result != -1 && (local_result = maximize(board)) < result)
            {
                result = local_result;
            }
            board->clearSquare(i, j);
        }

    return result;
}
