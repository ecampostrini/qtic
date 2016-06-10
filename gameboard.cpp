#include <QtDebug>
#include <cassert>

#include "gameboard.h"


/**** Board methods *******/
GameBoard::GameBoard(const GameBoard &other):
    rowNum(other.getRowNumber()),
    colNum(other.getColNumber()),
    freeBoxes(other.freeBoxes),
    last_to_play(other.lastToPlay()),
    next_to_play(other.nextToPlay())
{
    game_board = new Player*[rowNum];

    for(int i = 0; i < rowNum; i++)
    {
        game_board[i] = new Player[colNum];
        for(int j = 0; j < colNum; j++)
        {
            game_board[i][j] = other.getValue(i, j);
        }
    }
}


bool GameBoard::hasWinner()
{
    //Checks the rows
    for(int i = 0; i < rowNum; i++)
        if(game_board[i][0] != Player::None && game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2])
            return true;

    //Checks the columns
    for(int i = 0; i < colNum; i++)
        if(game_board[0][i] != Player::None && game_board[0][i] == game_board[1][i] && game_board[1][i] == game_board[2][i])
            return true;

    //Checks the diagonals
    if((game_board[0][0] != Player::None && game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) ||
        (game_board[0][2] != Player::None && game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0]))
        return true;

    return false;
}

void GameBoard::setSquare(int row, int col, const Player &current_player)
{
    assert(isEmpty(row, col) && "Trying to set a used squared");
    game_board[row][col] = current_player;
    last_to_play = current_player;
    next_to_play = (current_player == Player::Human) ? Player::Machine : Player::Human;
    freeBoxes--;
};

void GameBoard::clearSquare(int row, int col)
{
    assert(!isEmpty(row, col) && "Trying to clear a free square");
    game_board[row][col] = Player::None;
    last_to_play = Player::None;
    next_to_play = Player::None;
    freeBoxes++;
}

/*If the game is over it writes the scores on the argument and returns true,
otherwise it returns false*/
int GameBoard::score(int &score)
{
    int winningScore = (last_to_play == Player::Human) ? -1 : 1;

    if(hasWinner())
    {
        score = winningScore;
        return true;
    }
    else if(!hasPlace())
    {
        score = 0;
        return true;
    }

    return false;
}
