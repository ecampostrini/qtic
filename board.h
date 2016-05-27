#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
//#include <QPushButton>
#include <QLineEdit>
#include "button.h"
#include "ai.h"

namespace Ui {
class board;
}

class board : public QWidget
{
    Q_OBJECT

private:
    Ui::board *ui;
    enum {NumRows = 3, NumCols = 3};
    enum class Player : char {HUMAN = 'X', MACHINE = 'O'};

public:
    explicit board(QWidget *parent = 0);
    ~board();

private:
    Player next_player;
    button *buttons[NumRows * NumCols];
    //char game_board[NumRows][NumRows];
    char **game_board;
    Ai *ai;

    button *createButton(int row, int col, const QString&, const char *member);
    void disableButtons();
    bool check_board();

    /*For debuggin*/
    QLineEdit *debug_display;

private slots:
    void buttonClicked();
};

#endif // BOARD_H
