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
    button *buttons[NumRows * NumCols];
    GameBoard *game_board;
    Ai *ai;

public:
    explicit board(QWidget *parent = 0);
    ~board();

private:

    button *createButton(int row, int col, const QString&, const char *member);
    bool check_board(const char*);
    void disableButtons();
    //bool check_board();

    /*For debuggin*/
    QLineEdit *debug_display;

private slots:
    void buttonClicked();
};

#endif // BOARD_H
