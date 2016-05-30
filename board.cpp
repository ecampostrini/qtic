#include <QGridLayout>
#include <utility>
#include <QtDebug>

#include "board.h"
#include "ui_board.h"

board::board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::board)
{
    ui->setupUi(this);

    debug_display = new QLineEdit("Game on!");
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
    }

    setLayout(mainLayout);

    game_board = new GameBoard(NumRows, NumCols);
    ai = new Ai(NumRows, NumCols);
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
    delete ai;
    delete game_board;

}

void board::disableButtons()
{
    for(auto b : buttons)
        b->setEnabled(false);
}

bool board::check_board(const char *message)
{
    bool result = false;

    if(game_board->hasWinner())
    {
        debug_display->setText(message);
        result = true;
    }
    else if(!game_board->hasPlace())
    {
        debug_display->setText("Draw");
        result = true;
    }

    return result;
}

/******** SLOTS *********/

void board::buttonClicked()
{
    button *clickedButton = qobject_cast<button*>(sender());

    if(clickedButton)
    {
        int b_row = clickedButton->getRow();
        int b_col = clickedButton->getCol();

        //obviously the button was clicked by the human
        clickedButton->setText("X");
        clickedButton->setEnabled(false);
        game_board->setSquare(b_row, b_col, GameBoard::Player::Human);

        if(check_board("Human wins"))
            return;

        //then we make the machine play
        std::pair<int, int> machine_move;

        machine_move = ai->nextMove(game_board);
        int m_row = machine_move.first;
        int m_col = machine_move.second;
        int delinearized_button_position = m_row * NumRows + m_col;

        buttons[delinearized_button_position]->setText("O");
        buttons[delinearized_button_position]->setEnabled(false);
        game_board->setSquare(m_row, m_col, GameBoard::Player::Machine);

        if(check_board("Machine wins"))
            return;
    }
}
