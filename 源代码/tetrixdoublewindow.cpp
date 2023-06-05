#include "tetrixdoublewindow.h"
#include <QMessageBox>
#include "ui_tetrixdoublewindow.h"
#include <QSettings>
#include <QDir>

Tetrixdoublewindow::Tetrixdoublewindow(int w,int h,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tetrixdoublewindow)

{
    ui->setupUi(this);
    ui->board1->BoardWidth=w;
    ui->board1->BoardHeight=h;
    ui->board2->BoardWidth=w;
    ui->board2->BoardHeight=h;
    ui->board1->setNextPieceLabel(ui->nextPieceLabel);
    QSettings Settings(QDir::currentPath() + "/color.ini", QSettings::IniFormat);
    image=Settings.value("image").toInt();
    if(image==1)
    {
        QString imagePath = QDir::currentPath() + "/image/1.jpg";
        QPixmap pix(imagePath);
        ui->image->setPixmap(pix);
    }
    else if(image==2)
    {
        QString imagePath = QDir::currentPath() + "/image/2.jpg";
        QPixmap pix(imagePath);
        ui->image->setPixmap(pix);
    }
    else if(image==3)
    {
        QString imagePath = QDir::currentPath() + "/image/3.jpg";
        QPixmap pix(imagePath);
        ui->image->setPixmap(pix);
    }
    else if(image==4)
    {
        QString imagePath = QDir::currentPath() + "/image/4.jpg";
        QPixmap pix(imagePath);
        ui->image->setPixmap(pix);
    }
    connect(ui->startButton, &QPushButton::clicked, ui->board1, &TetrixBoard1::start);
    connect(ui->pauseButton, &QPushButton::clicked, ui->board1, &TetrixBoard1::pause);

    connect(ui->board1, &TetrixBoard1::scoreChanged,
            ui->scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(ui->board1, &TetrixBoard1::linesRemovedChanged,
            ui->linesLcd, qOverload<int>(&QLCDNumber::display));

    ui->board2->setNextPieceLabel(ui->nextPieceLabel_2);
    connect(ui->startButton, &QPushButton::clicked, ui->board2, &TetrixBoard2::start);
    connect(ui->pauseButton, &QPushButton::clicked, ui->board2, &TetrixBoard2::pause);

    connect(ui->board2, &TetrixBoard2::scoreChanged,
            ui->scoreLcd_2, qOverload<int>(&QLCDNumber::display));
    connect(ui->board2, &TetrixBoard2::linesRemovedChanged,
            ui->linesLcd_2, qOverload<int>(&QLCDNumber::display));
    ui->board2->raise();
}

Tetrixdoublewindow::~Tetrixdoublewindow()
{
    delete ui;
}

void Tetrixdoublewindow::on_quitButton_clicked()
{
    this->close();
}


void Tetrixdoublewindow::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::question(this, "关闭窗口",
            "您确定要关闭游戏吗？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        delete ui;
        this->wid->show();
        event->accept();
    }
    else
    {
        // 用户选择了“否”，忽略关闭操作
        event->ignore();
    }
}
