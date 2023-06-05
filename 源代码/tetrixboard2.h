#ifndef TETRIXBOARD2_H
#define TETRIXBOARD2_H


#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include <vector>
#include <QMap>

#include "tetrixpiece.h"
#include "tetrixboard1.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

//! [0]
class TetrixBoard2 : public QFrame
{
    Q_OBJECT

public:
    TetrixBoard2(TetrixBoard1 * Board, QWidget *parent = nullptr);

    void setNextPieceLabel(QLabel *label);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int BoardWidth=10;
    int BoardHeight=20;
    bool if_jixian=0;
    int timeout=1000;
    int color = 1;
    QMap<QString, int> currentKeySettings;
    ~TetrixBoard2()
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
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    //! [0]

    //! [1]
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
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(const TetrixPiece &newPiece, int newX, int newY);
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape,int c);

    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    TetrixPiece curPiece;
    TetrixPiece nextPiece;
    int curX;
    int curY;
    int numLinesRemoved;
    int numPiecesDropped;
    int score;
    int level;

    QVector<TetrixShape> board;
    TetrixBoard1 * board1;

};

#endif // TETRIXBOARD2_H
