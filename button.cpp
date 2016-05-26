#include "button.h"

button::button(int _id,const QString &, QWidget *parent)
    : id(_id), QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QSize button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.width(), size.height());

    return size;
}

int button::getId()
{
    return id;
}
