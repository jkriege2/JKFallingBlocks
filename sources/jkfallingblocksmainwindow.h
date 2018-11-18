#ifndef JKTETRISMAINWINDOW_H
#define JKTETRISMAINWINDOW_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
    class JKFallingBlocksMainWindow;
}

class JKFallingBlocksMainWindow : public QWidget
{
        Q_OBJECT

    public:
        explicit JKFallingBlocksMainWindow(QWidget *parent = 0);
        ~JKFallingBlocksMainWindow();

    protected slots:
        void gameOver(int score, int level);
    private:
        Ui::JKFallingBlocksMainWindow *ui;
};

#endif // JKTETRISMAINWINDOW_H
