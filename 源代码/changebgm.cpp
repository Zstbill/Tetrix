#include "changebgm.h"
#include "ui_changebgm.h"
#include <QDir>

changebgm::changebgm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changebgm)
{
    ui->setupUi(this);
}

changebgm::~changebgm()
{
    delete ui;
}

void changebgm::on_pushButton_clicked()
{
    if(ui->bgm1->isChecked())
    {
        wid->continuebgm=1;
        wid->mediaPlayer->setVolume(30);
        wid->mediaPlayer->setMedia(QUrl::fromLocalFile(QDir::currentPath() +"/bgm/01.mp3"));
        wid->mediaPlayer->play();
    }
    else if(ui->bgm2->isChecked())
    {
        wid->continuebgm=1;
        wid->mediaPlayer->setVolume(30);
        wid->mediaPlayer->setMedia(QUrl::fromLocalFile(QDir::currentPath() +"/bgm/02.mp3"));
        wid->mediaPlayer->play();
    }
    else if(ui->bgm3->isChecked())
    {
        wid->continuebgm=1;
        wid->mediaPlayer->setVolume(30);
        wid->mediaPlayer->setMedia(QUrl::fromLocalFile(QDir::currentPath() +"/bgm/03.mp3"));
        wid->mediaPlayer->play();
    }
    else if(ui->bgm->isChecked())
    {
        wid->continuebgm=1;
        QString str=QFileDialog::getOpenFileName(this, tr("Open Music Files"),
                                                 QDir::homePath(), tr("Music Files (*.mp3 *.wav *.flac)"));
        wid->mediaPlayer->setVolume(30);
        wid->mediaPlayer->setMedia(QUrl::fromLocalFile(str));
        wid->mediaPlayer->play();
    }
    else
    {
        wid->continuebgm=0;
        wid->mediaPlayer->stop();
    }
    close();
}

