#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H

#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include <QSettings>
#include <vector>

#include "tetrixpiece.h"
#include "saverank.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

//! [0]
class TetrixBoard : public QFrame
{
    Q_OBJECT

public:
    TetrixBoard(QWidget *parent = nullptr);

    void setNextPieceLabel(QLabel *label);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    void saveGame();
    void loadGame();
    void LoadGame(QString txt);
    int BoardWidth=10;
    int BoardHeight=20;
    int if_jixian=1;
    int timeout=1000;
    int color=1;

    QBasicTimer timer;
    int timeoutTime()
    {
        if(if_jixian)
            return timeout * (10.0/(9 + level));
        else
            return timeout;
    }
    ~TetrixBoard()
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
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape,int color);

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
    QMap<QString, int> currentKeySettings;


};
//! [1]

#endif
