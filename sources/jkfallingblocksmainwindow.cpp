#include "jkfallingblocksmainwindow.h"
#include "ui_jkfallingblocksmainwindow.h"

JKFallingBlocksMainWindow::JKFallingBlocksMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JKFallingBlocksMainWindow)
{
    ui->setupUi(this);

    ui->FallingBlocks->setLevelLabel(ui->labLevel);
    ui->FallingBlocks->setScoreLabel(ui->labPoints);
    ui->FallingBlocks->setLinesRemovedLabel(ui->labLinesRemoved);
    ui->FallingBlocks->setNextPieceLabel(ui->labNext);
    connect(ui->btnStart, SIGNAL(clicked()), ui->FallingBlocks, SLOT(start()));
    connect(ui->btnPause, SIGNAL(toggled(bool)), ui->FallingBlocks, SLOT(pause(bool)));
    connect(ui->FallingBlocks, SIGNAL(pauseEnabled(bool)), ui->btnPause, SLOT(setEnabled(bool)));
    connect(ui->FallingBlocks, SIGNAL(gameOver(int,int)), this, SLOT(gameOver(int,int)));
    ui->FallingBlocks->start();
}

JKFallingBlocksMainWindow::~JKFallingBlocksMainWindow()
{
    delete ui;
}

void JKFallingBlocksMainWindow::gameOver(int score, int level)
{
    QMessageBox::information(this, tr("Game Over!"), tr("Your game is over in level %2!\n\nSCORE = %1\n").arg(score).arg(level));
}
