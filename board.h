#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
//#include <QPushButton>
#include <QLineEdit>
#include "button.h"

namespace Ui {
class board;
}

class board : public QWidget
{
    Q_OBJECT

private:
    Ui::board *ui;
    enum {NumRows = 3, NumCols = 3};
    enum class Player : char {HUMAN, MACHINE};

public:
    explicit board(QWidget *parent = 0);
    ~board();

private:
    Player next_player;
    button *buttons[NumRows * NumCols];
    button *createButton(int row, int col, const QString&, const char *member);
    char game_board[NumRows][NumRows];
    /*For debuggin*/
    QLineEdit *debug_display;

private slots:
    void buttonClicked();
};

#endif // BOARD_H
