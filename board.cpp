#include <QGridLayout>
#include "board.h"
#include "ui_board.h"

board::board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::board),
    next_player(Player::HUMAN)
{
    ui->setupUi(this);

    debug_display = new QLineEdit("0");
    debug_display->setReadOnly(true);
    debug_display->setAlignment(Qt::AlignRight);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(debug_display, 0, 0, 1, 6);

    for(int i = 0; i < NumRows * NumCols; i++)
    {
        int row = i / NumRows + 1;
        int col = i % NumRows + 1;

        buttons[i] = createButton(i + 1, "", SLOT(buttonClicked()));
        mainLayout->addWidget(buttons[i], row, col);
    }

}

button* board::createButton(int id, const QString &text, const char *member)
{
    button *new_button = new button(id, text);
    connect(new_button, SIGNAL(clicked()), this, member);

    return new_button;
}

board::~board()
{
    delete ui;
}

/******** SLOTS *********/

void board::buttonClicked()
{
    button *clickedButton = qobject_cast<button*>(sender());

    if(clickedButton)
    {
        int button_id = clickedButton->getId();
        debug_display->setText(QString::number(button_id));

        if(next_player == Player::HUMAN)
        {
            clickedButton->setText("X");
            next_player = Player::MACHINE;
        }
        else if(next_player == Player::MACHINE)
        {
            clickedButton->setText("O");
            next_player = Player::HUMAN;
        }

        clickedButton->setEnabled(false);
    }
}
