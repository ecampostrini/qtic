#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QToolButton>

class button : public QToolButton
{
    Q_OBJECT

public:
    explicit button(int row, int col, const QString&, QWidget *parent = 0);

    QSize sizeHint() const Q_DECL_OVERRIDE;
    int getRow();
    int getCol();

private:
    int row, col;
};

#endif // BUTTON_H
