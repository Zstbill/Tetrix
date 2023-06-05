#ifndef TETRIXBOARD1_H
#define TETRIXBOARD1_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include <vector>

#include "tetrixpiece.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

//! [0]
class TetrixBoard1 : public QFrame
{
    Q_OBJECT

public:
    TetrixBoard1(QWidget *parent = nullptr);

    void setNextPieceLabel(QLabel *label);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void dropDown();
    void oneLineDown();
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);
    QBasicTimer timer;
    TetrixPiece curPiece;
    int curX;
    int curY;
    bool isStarted;
    bool isPaused;
    int BoardWidth=10;
    int BoardHeight=20;
    bool if_jixian=0;
    int timeout=1000;
    int score;
    int color=1;
    ~TetrixBoard1()
    {
        timer.stop();
    }


public slots:
    void start();
    void pause();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:

    TetrixShape &shapeAt(int x, int y) { return board[(y * BoardWidth) + x]; }
    int timeoutTime()
    {
        if(if_jixian)
            return timeout * (10.0/(9 + level));
        else
            return timeout;
    }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
    void clearBoard();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape,int c);


    QPointer<QLabel> nextPieceLabel;
    bool isWaitingAfterLine;
    TetrixPiece nextPiece;
    int numLinesRemoved;
    int numPiecesDropped;
    int level;

    QVector<TetrixShape> board;


};

#endif // TETRIXBOARD1_H
