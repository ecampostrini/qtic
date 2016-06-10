#include <QApplication>
#include <QMetaType>

#include "board.h"
#include "ai.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    board w;

    /*so we can dinamically create and destroy instances of it during runtime*/
    qRegisterMetaType<GameBoard>();
    qRegisterMetaType<std::pair<int, int>>();

    w.show();

    return a.exec();
}
