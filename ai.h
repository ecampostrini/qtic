#ifndef AI_H
#define AI_H

#include <utility>

class GameBoard
{
public:
    GameBoard(int rn, int cn) : rowNum(rn), colNum(cn)
    {
        game_board = new char*[rowNum];
        for(int i = 0; i < rowNum; i++)
        {
            game_board[i] = new char[colNum];

            for(int j = 0; j < colNum; j++)
                game_board[i][j] = '\0';
        }
    }

    ~GameBoard()
    {
        for(int i = 0; i < rowNum; i++)
            delete[] game_board[i];
        delete[] game_board;
    }

    int getRowNumber(){ return rowNum;};
    int getColNumber(){ return colNum;};
    void setSquare(int row, int col, const char val) {game_board[row][col] = val;};
    char getValue(int i, int j){return game_board[i][j];};
    bool isEmpty(int i, int j){return game_board[i][j] == '\0';};
    void clearSquare(int i, int j){game_board[i][j] = '\0';}
    bool hasWinner();

private:
    char **game_board;
    int rowNum, colNum;

};

class Ai
{
public:
    Ai(int _rNum, int _cNum) : rowNum(_rNum), colNum(_cNum) {};
    ~Ai();

    bool getNextMove(GameBoard &gb, std::pair<int, int> &result);
    std::pair<int,int> minimax(GameBoard *board);
private:
    int rowNum, colNum;

    int maximize(GameBoard*);
    int minimize(GameBoard*);
};

#endif // AI_H
