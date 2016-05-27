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



