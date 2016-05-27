#include <QGridLayout>
#include <utility>

#include "board.h"
#include "ui_board.h"

board::board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::board)
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
    for(int i = 0; i < NumRows * NumCols; i++)
        buttons[i]->setEnabled(false);
}

/******** SLOTS *********/

void board::buttonClicked()
{
    button *clickedButton = qobject_cast<button*>(sender());

    if(clickedButton)
    {
        int b_row = clickedButton->getRow();
        int b_col = clickedButton->getCol();

        debug_display->setText(QString::number(b_row) + ", " + QString::number(b_col));

        //obviously the button was clicked by the human
        clickedButton->setText("X");
        game_board->setSquare(b_row, b_col, 'X');
        if(game_board->hasWinner())
        {
            debug_display->setText("Human wins");
            disableButtons();
            return;
        }
        clickedButton->setEnabled(false);

        //then we make the machine play
        std::pair<int, int> machine_move;

        if(ai->getNextMove(*game_board, machine_move))
        {
            int m_row = machine_move.first;
            int m_col = machine_move.second;
            int delinearized_button_position = m_row * NumRows + m_col;

            buttons[delinearized_button_position]->setText("O");
            buttons[delinearized_button_position]->setEnabled(false);
            game_board->setSquare(m_row, m_col, 'O');

            if(game_board->hasWinner())
            {
                debug_display->setText("Machine wins");
                disableButtons();
                return;
            }
        }
    }
}
