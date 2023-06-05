#include "tetrixwindow.h"
#include "tetrixboard.h"
#include "ui_tetrixwindow.h"
#include <QMessageBox>

Tetrixwindow::Tetrixwindow(int w,int h,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tetrixwindow)
{
    ui->setupUi(this);
    ui->frame->BoardHeight=h;
    ui->frame->BoardWidth=w;
    ui->frame->setNextPieceLabel(ui->nextPieceLabel);
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

    connect(ui->startButton, &QPushButton::clicked, ui->frame, &TetrixBoard::start);
    connect(ui->pauseButton, &QPushButton::clicked, ui->frame, &TetrixBoard::pause);

    connect(ui->frame, &TetrixBoard::scoreChanged,
            ui->scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(ui->frame, &TetrixBoard::levelChanged,
            ui->levelLcd, qOverload<int>(&QLCDNumber::display));
    connect(ui->frame, &TetrixBoard::linesRemovedChanged,
            ui->linesLcd, qOverload<int>(&QLCDNumber::display));
    ui->frame->raise();
//    QString imagePath = QDir::currentPath() + "/1.jpg";
//    QPixmap pix(imagePath);
//    ui->image->setPixmap(pix);
   // ui->image->setStyleSheet("background-color: white;");
}

Tetrixwindow::~Tetrixwindow()
{
    delete ui;
}

void Tetrixwindow::on_quitButton_clicked()
{

    this->close();
}


void Tetrixwindow::on_saveButton_clicked()
{
    ui->frame->saveGame();
}


void Tetrixwindow::on_loadButton_clicked()
{
    ui->frame->loadGame();
}

void Tetrixwindow::load(QString str)
{
    ui->quitButton->setEnabled(0);
    ui->frame->LoadGame(str);
}

void Tetrixwindow::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::question(this, "关闭窗口",
            "您确定要关闭游戏吗？", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        ui->frame->timer.stop();
        delete ui->frame;
        if(this->wid!=NULL)
            this->wid->show();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
