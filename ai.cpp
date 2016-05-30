#include <QtDebug>
#include <cassert>

#include "ai.h"


/**** Board methods *******/
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

/*If the game it's over it writes the scores on the argument and returns true,
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

            board->setSquare(i, j, GameBoard::Player::Machine);
            //local_result = minimize(board);
            local_result = minimax(board, GameBoard::Player::Human);
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

int Ai::minimax(GameBoard* board, const GameBoard::Player &currentPlayer)
{
    int result = (currentPlayer == GameBoard::Player::Human) ? 2 : -2;
    int score;

    if(board->score(score))
        return score;

    for(int i = 0; i < board->getRowNumber(); i++)
    {
        for(int j = 0; j < board->getColNumber(); j++)
        {
            int local_result;

            if(!board->isEmpty(i, j))
                continue;

            board->setSquare(i, j, currentPlayer);
            local_result = minimax(board, board->nextToPlay());
            board->clearSquare(i, j);

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

            board->setSquare(i, j, GameBoard::Player::Human);
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

            board->setSquare(i, j, GameBoard::Player::Machine);
            local_result = minimize(board);
            board->clearSquare(i, j);

            if(local_result > result)
            {
                result = local_result;
            }
        }

    return result;
}
