#include "setting.h"
#include "ui_setting.h"
#include "changeboard.h"
#include "changebgm.h"
#include "changecolor.h"
#include "changekey.h"
#include "changebackground.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_changeboard_clicked()
{
    changeboard* c = new changeboard;
    c->setWindowTitle("更改尺寸");
    c->wid = wid;
    c->show();
}


void Setting::on_changebgm_clicked()
{
    changebgm* c = new changebgm;
    c->setWindowTitle("更改背景音乐");
    c->wid = wid;
    c->show();
}


void Setting::on_pushButton_clicked()
{
    this->wid->show();
    this->close();
}


void Setting::on_changecolor_clicked()
{
    changecolor* c = new changecolor;
    c->setWindowTitle("更改方块颜色和速度");
    c->show();
}


void Setting::on_changekeyevent_clicked()
{
    changekey* c = new changekey;
    c->setWindowTitle("更改键位");
    c->show();
}


void Setting::on_changeback_clicked()
{
    changebackground* c = new changebackground;
    c->setWindowTitle("更改背景");
    c->show();
}

