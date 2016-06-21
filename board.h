#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
//#include <QPushButton>
#include <QLineEdit>
#include <QThread>

#include "button.h"
#include "gameboard.h"
#include "worker.h"

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
    enum {NumRows = 3, NumCols = 3};
    button *buttons[NumRows * NumCols];
    GameBoard *game_board;
    Worker *worker;
    QThread *workerThread;

    button *createButton(int row, int col, const QString&, const char *member);
    bool check_board(const char*);
    void disableButtons();
    void connectSignalsSlots();

    /*For debuggin*/
    QLineEdit *debug_display;

signals:
    void playBitch(GameBoard g);

private slots:
    void buttonClicked();
    void machinePlayed(std::pair<int, int>);
};

#endif // BOARD_H
