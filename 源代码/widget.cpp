#include "widget.h"
#include "ui_widget.h"
#include "tetrixwindow.h"
#include "selectmode.h"
#include "instruction.h"
#include "rank.h"
#include "setting.h"
#include "file.h"
#include <QDir>
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //this->setStyleSheet("border-image:url(D:/Tetrix/1.png)");
    this->setWindowTitle("Tetrix");
    QString imagePath = QDir::currentPath() + "/1.jpg";
    QPixmap pix(imagePath);
    ui->picture->setPixmap(pix);

    mediaPlayer->setVolume(30);
    mediaPlayer->setMedia(QUrl::fromLocalFile(QDir::currentPath() +"/bgm/02.mp3"));
    mediaPlayer->play();
    connect(mediaPlayer, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State state) {
        if (state == QMediaPlayer::StoppedState) {
            if(continuebgm)
                mediaPlayer->play();
        }
    });

    QSettings Settings(QDir::currentPath() + "/color.ini", QSettings::IniFormat);
    int speed = 1000,color = 1;
    Settings.setValue("speed",speed);
    Settings.setValue("color",color);

    QSettings KeySetting(QDir::currentPath() + "/key.ini", QSettings::IniFormat);//读取键位
    QByteArray data;
    data=KeySetting.value("key").toByteArray();
    QDataStream in(&data, QIODevice::ReadOnly);
    keyCodes.clear();
    in >> keyCodes;

}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_exit_clicked()
{
    close();
}


void Widget::on_startgame_clicked()
{
    SelectMode *s = new SelectMode;
    s->wid=this;
    s->setWindowTitle("请选择模式");
    s->show();
    this->hide();
}


void Widget::on_introduction_clicked()
{
    instruction* i = new instruction;
    i->setWindowTitle("游戏说明");
    i->show();
}


void Widget::on_rank_clicked()
{
    Rank* r = new Rank;
    r->setWindowTitle("排行榜");
    r->display();
    r->show();
}


void Widget::on_setting_clicked()
{
    Setting* s = new Setting;
    s->setWindowTitle("设置");
    s->wid=this;
    s->show();
    this->hide();
}


void Widget::on_safe_clicked()
{
    File* f= new File;
    f->setWindowTitle("存档");
    f->show();
}

