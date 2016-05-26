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
        int row = i / NumRows;
        int col = i % NumRows;

        buttons[i] = createButton(row, col, "", SLOT(buttonClicked()));
        mainLayout->addWidget(buttons[i], row + 1, col + 1);

        game_board[row][col] = '\0';
    }
}

button* board::createButton(int row, int col, const QString &text, const char *member)
{
    button *new_button = new button(row, col, text);
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
        int row = clickedButton->getRow();
        int col = clickedButton->getCol();

        debug_display->setText(QString::number(row) + ", " + QString::number(col));

        if(next_player == Player::HUMAN)
        {
            clickedButton->setText("X");
            game_board[row][col] = 'X';
            next_player = Player::MACHINE;
        }
        else if(next_player == Player::MACHINE)
        {
            clickedButton->setText("O");
            game_board[row][col] = 'O';
            next_player = Player::HUMAN;
        }

        clickedButton->setEnabled(false);
    }
}
