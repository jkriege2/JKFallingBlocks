# JKFallingBlocks
This was a tiny sunday-afternoon exercise in programming a small game as easter egg for a larger program (see https://github.com/jkriege2/QuickFit3).

This game is implemented in C++ and Qt >= 4

This software is licensed under the term of the GNU Lesser General Public License 3.0
(LGPL 3.0) or above. 

## Screenshots
![In the beginning ...](https://github.com/jkriege2/JKFallingBlocks/blob/master/Screenshots/screenshot1.png)
![... in getween ...](https://github.com/jkriege2/JKFallingBlocks/blob/master/Screenshots/screenshot2.png)
![Game Over](https://github.com/jkriege2/JKFallingBlocks/blob/master/Screenshots/screenshot3.png)

## Usage
Usage is simple:

```c++
#include "jkfallingblocksmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JKFallingBlocksMainWindow w;
    w.show();

    return a.exec();
}
```

