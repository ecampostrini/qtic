#include "ai.h"

Ai::~Ai(){}

bool Ai::getNextMove(char **board, std::pair<int, int> &result)
{
    for(int i = 0; i < rowNum; i++)
        for(int j = 0; j < colNum; j++)
        {
            if(board[i][j] == '\0')
            {
                result.first = i;
                result.second = j;
                return true;
            }
        }

    return false;
}
