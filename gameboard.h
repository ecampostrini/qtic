#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QDebug>
#include <QMetaType>

#include <utility>
#include <cassert>

class GameBoard
{
public:
    enum class Player : char {Human = -1, Machine = 1, None = 0};

    /*I add a default constructor so I can add the class to the metatype system*/
    GameBoard() : game_board(nullptr), rowNum(0), colNum(0) {}

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

    GameBoard& operator=(const GameBoard& rhs)
    {
        Player** originalBoard = game_board;

        //game_board = rhs.game_board;
        freeBoxes = rhs.freeBoxes;
        last_to_play = rhs.last_to_play;
        next_to_play = rhs.next_to_play;
        rowNum = rhs.rowNum;
        colNum = rhs.colNum;

        if(originalBoard != nullptr)
        {
            for(int i = 0; i < rowNum; i++)
                for(int j = 0; j < colNum; j++)
                {
                    originalBoard[i][j] = rhs.game_board[i][j];
                }
        }
        else
        {
            game_board = new Player*[rowNum];
            for(int i = 0; i < rowNum; i++)
            {
                game_board[i] = new Player[rowNum];
                for(int j = 0; j < colNum; j++)
                    game_board[i][j] = rhs.game_board[i][j];
            }
        }

        return *this;
    }

    GameBoard(const GameBoard& other);

    ~GameBoard()
    {
        assert(game_board != nullptr && "trying to free a null board");

        for(int i = 0; i < rowNum; i++)
            delete[] game_board[i];
        delete[] game_board;
    }

    int getRowNumber() const { return rowNum;}
    int getColNumber() const { return colNum;}
    void setSquare(int row, int col, const Player &val);
    void clearSquare(int i, int j);
    Player getValue(int i, int j) const {return game_board[i][j];}
    bool isEmpty(int i, int j) const {return game_board[i][j] == Player::None;}
    Player lastToPlay() const { return last_to_play;}
    Player nextToPlay() const { return next_to_play;}
    int score(int &score);

private:
    Player **game_board;
    int rowNum, colNum;
    int freeBoxes;
    Player last_to_play;
    Player next_to_play;

    bool hasPlace(){return freeBoxes > 0;}
    bool hasWinner();
};

/*since we are passing the board to the thread we add it to the type system of QT*/
Q_DECLARE_METATYPE(GameBoard);

#endif // GAMEBOARD_H
