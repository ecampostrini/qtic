#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QToolButton>

class button : public QToolButton
{
    Q_OBJECT

public:
    explicit button(int id, const QString&, QWidget *parent = 0);

    QSize sizeHint() const Q_DECL_OVERRIDE;
    int getId();

private:
    int id;
};

#endif // BUTTON_H
