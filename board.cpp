#include <QGridLayout>
#include <utility>
#include <QtDebug>
#include <QThread>

#include "board.h"
#include "worker.h"
#include "ui_board.h"

board::board(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::board)
{
    ui->setupUi(this);

    debug_display = new QLineEdit("Game on!");
    debug_display->setReadOnly(true);
    debug_display->setAlignment(Qt::AlignRight);

    /*set the interface*/
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

    /*and create the background processing classes*/
    //game_board = new GameBoard(NumRows, NumCols);
    game_board = std::make_shared<GameBoard>(NumRows, NumCols);
    worker = QSharedPointer<Worker>::create();
    workerThread = new QThread;

    worker->moveToThread(workerThread);
    connectSignalsSlots();
    workerThread->start();
}


button* board::createButton(int row, int col, const QString &text, const char *member)
{
    button *new_button = new button(row, col, text);
    connect(new_button, SIGNAL(clicked()), this, member);

    return new_button;
}

void board::connectSignalsSlots()
{
    connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
    connect(this, SIGNAL(playBitch(GameBoard)), worker.data(), SLOT(makeMove(GameBoard)));
    connect(worker.data(), SIGNAL(newMove(std::pair<int,int>)), this, SLOT(machinePlayed(std::pair<int, int>)));
}

board::~board()
{
    delete ui;
    //delete game_board;

    worker->deleteLater();
    if(workerThread != 0 && workerThread->isRunning())
    {
        workerThread->requestInterruption();
        workerThread->quit();
    }
}

void board::disableButtons()
{
    for(auto b : buttons)
        b->setEnabled(false);
}

bool board::check_board(const char *message)
{
    int score;

    if(game_board->score(score))
    {
        (score == 0) ? debug_display->setText("Draw") : debug_display->setText(message);
        return true;
    }
    return false;
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
        {
            disableButtons();
            return;
        }

        //then we make the machine play
        emit playBitch(*game_board);
    }
}

void board::machinePlayed(std::pair<int, int> pos)
{
    int m_row = pos.first;
    int m_col = pos.second;
    int delinearized_button_position = m_row * NumRows + m_col;

    buttons[delinearized_button_position]->setText("O");
    buttons[delinearized_button_position]->setEnabled(false);
    game_board->setSquare(m_row, m_col, GameBoard::Player::Machine);

    if(check_board("Machine wins"))
    {
        disableButtons();
        return;
    }
}
