#include "button.h"

button::button(int _row, int _col,const QString &, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    col = _col;
    row = _row;
}

QSize button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());

    return size;
}

int button::getRow()
{
    return row;
}

int button::getCol()
{
    return col;
}
