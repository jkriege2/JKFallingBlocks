#include "jkfallingblocksmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JKFallingBlocksMainWindow w;
    w.show();

    return a.exec();
}
