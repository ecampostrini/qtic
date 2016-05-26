#ifndef BOARD_H
#define BOARD_H

#include <QWidget>

namespace Ui {
class board;
}

class board : public QWidget
{
    Q_OBJECT

public:
    explicit board(QWidget *parent = 0);
    ~board();

private:
    Ui::board *ui;
};

#endif // BOARD_H
