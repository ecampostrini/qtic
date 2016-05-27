#include <QGridLayout>
#include <utility>

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

    game_board = new char*[NumRows];
    for(int i = 0; i < NumCols; i++)
        game_board[i] = new char[NumCols];

    for(int i = 0; i < NumRows * NumCols; i++)
    {
        int row = i / NumRows;
        int col = i % NumRows;

        buttons[i] = createButton(row, col, "", SLOT(buttonClicked()));
        mainLayout->addWidget(buttons[i], row + 1, col + 1);

        game_board[row][col] = '\0';
    }

    setLayout(mainLayout);

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

    for(int i = 0; i < NumRows; i++)
        delete[] game_board[i];
    delete[] game_board;
}

bool board::check_board()
{
    //Checks the rows
    for(int i = 0; i < NumRows; i++)
        if(game_board[i][0] != '\0' && game_board[i][0] == game_board[i][1] && game_board[i][1] == game_board[i][2])
            return true;

    //Checks the columns
    for(int i = 0; i < NumCols; i++)
        if(game_board[0][i] != '\0' && game_board[0][i] == game_board[1][i] && game_board[1][i] == game_board[2][i])
            return true;

    //Checks the diagonals
    if((game_board[0][0] != '\0' && game_board[0][0] == game_board[1][1] && game_board[1][1] == game_board[2][2]) ||
        (game_board[0][2] != '\0' && game_board[0][2] == game_board[1][1] && game_board[1][1] == game_board[2][0]))
        return true;

    return false;
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
        int row = clickedButton->getRow();
        int col = clickedButton->getCol();

        debug_display->setText(QString::number(row) + ", " + QString::number(col));

        //obviously the button was clicked by the human
        clickedButton->setText("X");
        game_board[row][col] = 'X';
        if(check_board())
        {
            debug_display->setText("Human wins");
            disableButtons();
            return;
        }
        clickedButton->setEnabled(false);

        //then we make the machine play
        std::pair<int, int> machine_move;

        if(ai->getNextMove(game_board, machine_move))
        {
            row = machine_move.first;
            col = machine_move.second;

            int delinearized_button_position = row * NumRows + col;

            buttons[delinearized_button_position]->setText("O");
            buttons[delinearized_button_position]->setEnabled(false);
            game_board[row][col] = 'O';

            if(check_board())
            {
                debug_display->setText("Machine wins");
                disableButtons();
                return;
            }
        }
    }
}
