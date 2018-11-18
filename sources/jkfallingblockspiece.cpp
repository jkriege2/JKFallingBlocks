#include "jkfallingblockspiece.h"
#include <QtGlobal>
#include <QDebug>

int JKFallingBlocksPiece::PieceData[JKFallingBlocksPiece::PieceCount][4][JKFallingBlocksPiece::PieceSize*JKFallingBlocksPiece::PieceSize] = {
    { {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}, {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}, {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}, {0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0} },
    { {0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0}, {1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0}, {0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0}, {0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0} },
    { {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0}, {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0}, {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0}, {1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0} },
    { {1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0}, {1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0}, {1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0}, {0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0} },
    { {0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0}, {1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0}, {1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0}, {1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0} },
    { {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0}, {1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0}, {0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0}, {1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0} },
    { {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0}, {0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0}, {1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0}, {0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0} },
};

QColor JKFallingBlocksPiece::PieceColor[JKFallingBlocksPiece::PieceCount] = {
    QColor("red") ,
    QColor("goldenrod") ,
    QColor("darkgreen") ,
    QColor("magenta") ,
    QColor("blue") ,
    QColor("orange") ,
    QColor("green") ,
};

JKFallingBlocksPiece::JKFallingBlocksPiece(int *board, int boardWidth, int boardHeight)
{
    rotation=0;
    type=0;
    x=0;
    y=0;
    this->board=board;
    this->boardWidth=boardWidth;
    this->boardHeight=boardHeight;
}

JKFallingBlocksPiece::~JKFallingBlocksPiece()
{

}

bool JKFallingBlocksPiece::checkHit() const
{
    const int* p=JKFallingBlocksPiece::PieceData[type][rotation];
    int i=0;
    for (int yy=0; yy<JKFallingBlocksPiece::PieceSize; yy++) {
        for (int xx=0; xx<JKFallingBlocksPiece::PieceSize; xx++) {
            if (p[i]>0) {
                if (x+xx<0 || x+xx>=boardWidth) return true;
                if (y+yy<0 || y+yy>=boardHeight) return true;
                if (board[(y+yy)*boardWidth+ (x+xx)]>=0) {
                    return true;
                }
            }
            i++;
        }
    }
    return false;
}

void JKFallingBlocksPiece::setBoard(int *board, int boardWidth, int boardHeight)
{
    this->board=board;
    this->boardWidth=boardWidth;
    this->boardHeight=boardHeight;
    initTop();
}

bool JKFallingBlocksPiece::init(const JKFallingBlocksPiece &other)
{
    this->x=other.x;
    this->y=other.y;
    this->type=other.type;
    this->rotation=other.rotation;
    return !checkHit();
}

bool JKFallingBlocksPiece::initTop(int type)
{
    this->x=boardWidth/2-JKFallingBlocksPiece::PieceSize/2;//qrand()%boardWidth;
    this->y=0;
    rotation=0;
    this->type=type;
    if (type<0) {
        this->type=qrand()%JKFallingBlocksPiece::PieceCount;
    }

    /*while (checkHit()) {
        x=qrand()%boardWidth;
    }*/
    return !checkHit();
}

bool JKFallingBlocksPiece::moveDown()
{
    if (y>=boardHeight) return false;
    int oldy=y;
    y++;
    if (!checkHit()) {
        return true;
    } else {
        y=oldy;
        return false;
    }
}

bool JKFallingBlocksPiece::moveLeft()
{
    int oldx=x;
    x--;
    if (!checkHit()) {
        return true;
    } else {
        x=oldx;
        return false;
    }
}

bool JKFallingBlocksPiece::moveRight()
{
    int oldx=x;
    x++;
    if (!checkHit()) {
        return true;
    } else {
        x=oldx;
        return false;
    }
}

bool JKFallingBlocksPiece::rotateRight()
{
    int oldrot=rotation;
    rotation=rotation+1;
    if (rotation>3) rotation=0;
    if (!checkHit()) {
        return true;
    } else {
        rotation=oldrot;
        return false;
    }
}

bool JKFallingBlocksPiece::rotateLeft()
{
    int oldrot=rotation;
    rotation=rotation-1;
    if (rotation<0) rotation=3;
    if (!checkHit()) {
        return true;
    } else {
        rotation=oldrot;
        return false;
    }
}

void JKFallingBlocksPiece::saveToBoard(int *rowsRemoved)
{
    const int* p=JKFallingBlocksPiece::PieceData[type][rotation];
    int i=0;
    for (int yy=0; yy<JKFallingBlocksPiece::PieceSize; yy++) {
        for (int xx=0; xx<JKFallingBlocksPiece::PieceSize; xx++) {
            if (p[i]>0) {
                if (x+xx>=0 && x+xx<boardWidth && y+yy>=0 && y+yy<boardHeight) {
                    board[(y+yy)*boardWidth+x+xx]=type;
                }
            }
            i++;
        }
    }

    if (rowsRemoved) *rowsRemoved=0;
    bool removed=true;
    while (removed) {
        bool remove=true;
        removed=false;
        int removeRow=-1;

        for (int yy=boardHeight-1; yy>=0; yy--) {
            remove=true;
            for (int xx=0; xx<boardWidth; xx++) {
                remove=remove&&(board[yy*boardWidth+xx]>=0);
                if (!remove) break;
            }
            //qDebug()<<"   yy="<<yy<<"  remove="<<remove;
            if (remove) {
                removeRow=yy;
                break;
            }
        }
        //qDebug()<<"remove "<<remove<<" row="<<removeRow;
        if (remove && removeRow>=0) {
            if (rowsRemoved) *rowsRemoved=*rowsRemoved+1;
            for (int yy=removeRow; yy>=0; yy--) {
                if (yy>=1) {
                    for (int xx=0; xx<boardWidth; xx++) {
                        board[yy*boardWidth+xx]=board[(yy-1)*boardWidth+xx];
                    }
                } else {
                    for (int xx=0; xx<boardWidth; xx++) {
                        board[yy*boardWidth+xx]=-1;
                    }
                }
            }
            removed=true;
        }
    }

    /*if (initNew) {
        initTop();
    }*/
}

QPixmap JKFallingBlocksPiece::drawPiece(QSize tilesize, int xoffset, int yoffset) const
{
    QPixmap pix(tilesize.width()*JKFallingBlocksPiece::PieceSize, tilesize.height()*JKFallingBlocksPiece::PieceSize);
    pix.fill(QColor("grey"));
    {
        QPainter painter(&pix);
        drawPiece(&painter, tilesize, xoffset, yoffset);
        painter.end();
    }
    return pix;
}

void JKFallingBlocksPiece::drawPiece(QPainter *painter, QSize tilesize, int xoffset, int yoffset) const
{
    QColor col=JKFallingBlocksPiece::PieceColor[type];
    QColor borderCol=col.darker();
    int i=0;
    const int* p=JKFallingBlocksPiece::PieceData[type][rotation];
    for (int yy=0; yy<JKFallingBlocksPiece::PieceSize; yy++) {
        for (int xx=0; xx<JKFallingBlocksPiece::PieceSize; xx++) {
            if (p[i]>0) {
                painter->save();
                QRect r(xoffset+xx*tilesize.width(), yoffset+yy*tilesize.height(), tilesize.width()-1, tilesize.height()-1);
                painter->fillRect(r,col);
                painter->setPen(borderCol);
                painter->drawRect(r);
                painter->restore();
            }
            i++;
        }
    }
}

void JKFallingBlocksPiece::drawBoard(QPainter *painter, QSize tilesize, bool withPiece) const
{
    painter->save();
    QPen p(QColor("black"));
    p.setWidthF(2.5);
    painter->setPen(p);
    painter->drawLine(0,boardHeight*tilesize.height(), boardWidth*tilesize.width(), boardHeight*tilesize.height());
    painter->restore();
    int i=0;
    for (int yy=0; yy<boardHeight; yy++) {
        for (int xx=0; xx<boardWidth; xx++) {
            if (board[i]>=0){
                QColor col=JKFallingBlocksPiece::PieceColor[board[i]];
                QColor borderCol=col.darker();
                painter->save();
                QRect r(xx*tilesize.width(), yy*tilesize.height(), tilesize.width()-1, tilesize.height()-1);
                painter->fillRect(r,col);
                painter->setPen(borderCol);
                painter->drawRect(r);
                painter->restore();
            }
            i++;
        }
    }
    if (withPiece) {
        drawPiece(painter, tilesize, x*tilesize.width(), y*tilesize.height());
    }

}

