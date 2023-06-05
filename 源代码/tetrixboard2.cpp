#include "tetrixboard2.h"


#include <QKeyEvent>
#include <QLabel>
#include <QPainter>
#include <QMessageBox>
#include <QSettings>
#include <QDir>

//! [0]
TetrixBoard2::TetrixBoard2(TetrixBoard1 * Board, QWidget *parent)
    : QFrame(parent), isStarted(false), isPaused(false), board1(Board)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    for (int i = 0; i < 41 * 20; ++i)
    {
        board.push_back(NoShape);
    }
    clearBoard();
    QSettings Settings(QDir::currentPath() + "/color.ini", QSettings::IniFormat);
    color=Settings.value("color").toInt();
    timeout=Settings.value("speed").toInt();

    QSettings KeySetting(QDir::currentPath() + "/key.ini", QSettings::IniFormat);//读取键位
    QByteArray data;
    data=KeySetting.value("key").toByteArray();
    QDataStream in(&data, QIODevice::ReadOnly);
    in >> currentKeySettings;

    nextPiece.setRandomShape();
}
//! [0]

//! [1]
void TetrixBoard2::setNextPieceLabel(QLabel *label)
{
    nextPieceLabel = label;
}
//! [1]

//! [2]
QSize TetrixBoard2::sizeHint() const
{
    return QSize(BoardWidth * 15 + frameWidth() * 2,
                 BoardHeight * 15 + frameWidth() * 2);
}

QSize TetrixBoard2::minimumSizeHint() const
//! [2] //! [3]
{
    return QSize(BoardWidth * 5 + frameWidth() * 2,
                 BoardHeight * 5 + frameWidth() * 2);
}
//! [3]

//! [4]
void TetrixBoard2::start()
{
    if (isPaused)
        return;

    isStarted = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    level = 1;
    clearBoard();

    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);

    newPiece();
    timer.start(timeoutTime(), this);
}
//! [4]

//! [5]
void TetrixBoard2::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
    //! [5] //! [6]
}
//! [6]

//! [7]
void TetrixBoard2::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();
    QFont font("Arial", 20, QFont::Bold);

    if (isPaused) {
        painter.setFont(font);
        painter.drawText(rect, Qt::AlignCenter, tr("暂停"));
        return;
    }

    //! [8]
    int boardTop = rect.bottom() - BoardHeight*squareHeight();

    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
            if (shape != NoShape)
                drawSquare(painter, rect.left() + j * squareWidth(),
                           boardTop + i * squareHeight(), shape,color);
        }
        //! [8] //! [9]
    }
    //! [9]

    //! [10]
    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY - curPiece.y(i);
            drawSquare(painter, rect.left() + x * squareWidth(),
                       boardTop + (BoardHeight - y - 1) * squareHeight(),
                       curPiece.shape(),color);
        }
        //! [10] //! [11]
    }
    painter.setPen(QPen(Qt::black, 1));
    int width = squareWidth()*BoardWidth+1;
    int height =squareHeight()*BoardHeight+1;

    // 绘制竖直方向的网格线
    for (int i = 0; i < width; i += squareWidth()) {

        painter.drawLine(i, 0, i, height);
    }
    // 绘制水平方向的网格线
    for (int i = 0; i < height; i += squareHeight()) {

        painter.drawLine(0, i, width, i);
    }
}
//! [12]

//! [13]
void TetrixBoard2::keyPressEvent(QKeyEvent *event)
{
    if (currentKeySettings.contains("Pause") && event->key() == currentKeySettings["Pause"])
    {
        pause();
        board1->pause();
    }
    else if (currentKeySettings.contains("Start") && event->key() == currentKeySettings["Start"])
    {
        start();
        board1->start();
    }
    else
        QFrame::keyPressEvent(event);

    if(score!=0 && board1->score!=0 && !isStarted && !board1->isStarted)
    {
        if(score < board1->score) QMessageBox::information(this, "游戏结束", "P1获胜！");
        else if(score > board1->score) QMessageBox::information(this, "游戏结束", "P2获胜！");
        else QMessageBox::information(this, "游戏结束", "平局！");
    }
    if ((!isStarted && !board1->isStarted) || isPaused || (curPiece.shape() == NoShape && board1->curPiece.shape() == NoShape))
    {
        QFrame::keyPressEvent(event);
        return;
    }

    bool if_stop1=0, if_stop2=0;
    if(curPiece.shape() == NoShape) if_stop2=1;
    if(board1->curPiece.shape() == NoShape) if_stop1=1;
    switch (event->key()) {
    case Qt::Key_Left:
        if(!if_stop2)
        tryMove(curPiece, curX - 1, curY);
        break;
    case Qt::Key_Right:
        if(!if_stop2)
        tryMove(curPiece, curX + 1, curY);
        break;
    case Qt::Key_Down:
        if(!if_stop2)
        tryMove(curPiece.rotatedRight(), curX, curY);
        break;
    case Qt::Key_Up:
        if(!if_stop2)
        tryMove(curPiece.rotatedLeft(), curX, curY);
        break;
    case Qt::Key_2:
        if(!if_stop2)
        dropDown();
        break;
    case Qt::Key_1:
        if(!if_stop2)
        oneLineDown();
        break;
    case Qt::Key_A:
        if(!if_stop1)
        board1->tryMove(board1->curPiece, board1->curX - 1, board1->curY);
        break;
    case Qt::Key_D:
        if(!if_stop1)
        board1->tryMove(board1->curPiece, board1->curX + 1, board1->curY);
        break;
    case Qt::Key_W:
        if(!if_stop1)
        board1->tryMove(board1->curPiece.rotatedRight(), board1->curX, board1->curY);
        break;
    case Qt::Key_S:
        if(!if_stop1)
        board1->tryMove(board1->curPiece.rotatedLeft(), board1->curX, board1->curY);
        break;
    case Qt::Key_K:
        if(!if_stop1)
        board1->dropDown();
        break;
    case Qt::Key_J:
        if(!if_stop1)
        board1->oneLineDown();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
    //! [14]
}

//! [15]
void TetrixBoard2::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            newPiece();
            timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);
        //! [15] //! [16]
    }
    //! [16] //! [17]
}
//! [17]

//! [18]
void TetrixBoard2::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}
//! [18]

//! [19]
void TetrixBoard2::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curPiece, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
    //! [19] //! [20]
}
//! [20]

//! [21]
void TetrixBoard2::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY - 1))
        pieceDropped(0);
}
//! [21]

//! [22]
void TetrixBoard2::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        shapeAt(x, y) = curPiece.shape();
    }

    ++numPiecesDropped;
    if (numPiecesDropped % 5 == 0) {
        ++level;
        timer.start(timeoutTime(), this);
        emit levelChanged(level);
    }

    score += dropHeight/5 + 1;
    emit scoreChanged(score);
    removeFullLines();

    if (!isWaitingAfterLine)
        newPiece();
    //! [22] //! [23]
}
//! [23]

//! [24]
void TetrixBoard2::removeFullLines()
{
    int numFullLines = 0;

    for (int i = BoardHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j) {
            if (shapeAt(j, i) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            //! [24] //! [25]
            ++numFullLines;
            for (int k = i; k < BoardHeight - 1; ++k) {
                for (int j = 0; j < BoardWidth; ++j)
                    shapeAt(j, k) = shapeAt(j, k + 1);
            }
            //! [25] //! [26]
            for (int j = 0; j < BoardWidth; ++j)
                shapeAt(j, BoardHeight - 1) = NoShape;
        }
        //! [26] //! [27]
    }
    //! [27]

    //! [28]
    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setShape(NoShape);
        update();
    }
    //! [28] //! [29]
}
//! [29]

//! [30]
void TetrixBoard2::newPiece()
{
    curPiece = nextPiece;
    nextPiece.setRandomShape();
    showNextPiece();
    curX = BoardWidth / 2 ;
    curY = BoardHeight - 1 + curPiece.minY();

    if (!tryMove(curPiece, curX, curY)) {
        curPiece.setShape(NoShape);
        timer.stop();
        isStarted = false;
    }

    //! [30] //! [31]
}
//! [31]

//! [32]
void TetrixBoard2::showNextPiece()
{
    if (!nextPieceLabel)
        return;

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().window());

    for (int i = 0; i < 4; ++i) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter, x * squareWidth(), y * squareHeight(),
                   nextPiece.shape(),color);
    }
    nextPieceLabel->setPixmap(pixmap);
    //! [32] //! [33]
}
//! [33]

//! [34]
bool TetrixBoard2::tryMove(const TetrixPiece &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }
    //! [34]

    //! [35]
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}
//! [35]

//! [36]
void TetrixBoard2::drawSquare(QPainter &painter, int x, int y, TetrixShape shape,int color1)
{
    QColor color;
    static constexpr QRgb colorTable1[8] =
        {
            0x000000, 0xDB8400, 0x894087, 0x58B0BC,
            0xEAD500, 0xCC0B10, 0x379A30, 0x1465A6
        };
    static constexpr QRgb colorTable2[8] =
        {
            0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
            0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
        };
    static constexpr QRgb colorTable3[8] =
        {
            0x000000, 0xFF0000, 0xFF0000, 0xFF0000,
            0xFF0000, 0xFF0000, 0xFF0000, 0xFF0000
        };
    static constexpr QRgb colorTable4[8] =
        {
            0x000000, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF,
            0xFFFFFF, 0xFFFFFF, 0xFFFFFF, 0xFFFFFF
        };
    if(color1 == 1)
    {
        color = colorTable1[int(shape)];
    }
    else if(color1 == 2)
    {
        color = colorTable2[int(shape)];
    }
    else if(color1 == 3)
    {
        color = colorTable3[int(shape)];
    }
    else if(color1 == 4)
    {
        color = colorTable4[int(shape)];
    }
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.lighter());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.darker());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}
