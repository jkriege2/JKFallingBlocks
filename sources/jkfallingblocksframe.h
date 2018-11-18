#ifndef JKTETRISFRAME_H
#define JKTETRISFRAME_H

#include <QFrame>
#include <QPointer>
#include <QLabel>
#include "jkfallingblockspiece.h"
#include <QTimer>
#include <QKeyEvent>
#include <QPaintEvent>

class JKFallingBlocksFrame : public QFrame {
        Q_OBJECT
    public:
        explicit JKFallingBlocksFrame(QWidget* parent=NULL);
        virtual ~JKFallingBlocksFrame();

        void resizeBoard(int w, int h);

        QSize sizeHint() const;
        QSize minimumSizeHint();

        void setNextPieceLabel(QLabel* label);
        void setScoreLabel(QLabel* label);
        void setLevelLabel(QLabel* label);
        void setLinesRemovedLabel(QLabel* label);
        int getInterval();
    public slots:
        void start();
        void pause(bool enabled);
        void nextStep();
        void savePieceToBoard(int &interval);
    signals:
        void pauseEnabled(bool enabled);
        void gameOver(int score, int level);
    protected slots:

    protected:
        void gameIsOver();
        void paintEvent(QPaintEvent* event);
        void keyPressEvent(QKeyEvent* event);
        void keyReleaseEvent(QKeyEvent* event);
        void setScore(int score);
        void setLevel(int level);
        void setLinesRemoved(int removed, int sum);
        void showPiece();
        void dropDown();

        bool removeLines(int lines);


        QTimer* timer;
        JKFallingBlocksPiece piece;
        JKFallingBlocksPiece nextPiece;
        int* board;
        int boardWidth;
        int boardHeight;
        int level;
        int score;
        bool running;
        bool fastDown;
        bool dropping;
        int linesRemoved;
        int linesRemovedSum;
        QSize tileSize;
        QPointer<QLabel> labNextPiece;
        QPointer<QLabel> labScore;
        QPointer<QLabel> labLevel;
        QPointer<QLabel> labLinesRemoved;
};

#endif // JKTETRISFRAME_H
