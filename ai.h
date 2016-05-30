#ifndef AI_H
#define AI_H

#include <utility>
#include <QDebug>

class GameBoard
{
public:
    enum class Player : char {Human = -1, Machine = 1, None = 0};

    GameBoard(int rn, int cn) :
        rowNum(rn),
        colNum(cn),
        freeBoxes(rowNum * colNum)
    {
        game_board = new Player*[rowNum];
        for(int i = 0; i < rowNum; i++)
        {
            game_board[i] = new Player[colNum];

            for(int j = 0; j < colNum; j++)
                game_board[i][j] = Player::None;
        }

        last_to_play = Player::None;
        next_to_play = Player::None;
    }

    ~GameBoard()
    {
        for(int i = 0; i < rowNum; i++)
            delete[] game_board[i];
        delete[] game_board;
    }

    int getRowNumber(){ return rowNum;}
    int getColNumber(){ return colNum;}
    void setSquare(int row, int col, const Player &val);
    void clearSquare(int i, int j);
    Player getValue(int i, int j){return game_board[i][j];}
    bool isEmpty(int i, int j){return game_board[i][j] == Player::None;}
    bool hasPlace(){return freeBoxes > 0;}
    bool hasWinner();
    Player lastToPlay(){ return last_to_play;}
    Player nextToPlay(){ return next_to_play;}
    int score(int &score);

private:
    Player **game_board;
    int rowNum, colNum;
    int freeBoxes;
    Player last_to_play;
    Player next_to_play;

};

class Ai
{
public:
    Ai(int _rNum, int _cNum) : rowNum(_rNum), colNum(_cNum) {};
    ~Ai();

    std::pair<int,int> nextMove(GameBoard *board);
private:
    int rowNum, colNum;

    int maximize(GameBoard*);
    int minimize(GameBoard*);
    int minimax(GameBoard*, const GameBoard::Player &);
};

#endif // AI_H
