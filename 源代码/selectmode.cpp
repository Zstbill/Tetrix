#include "selectmode.h"
#include "ui_selectmode.h"
#include "tetrixwindow.h"
#include "tetrixeasywindow.h"
#include "tetrixdoublewindow.h"
#include <QDebug>

SelectMode::SelectMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectMode)
{
    ui->setupUi(this);

}

SelectMode::~SelectMode()
{
    delete ui;
}

void SelectMode::on_pushButton_clicked()
{
    this->wid->show();
    this->close();
}


void SelectMode::on_singlejixian_clicked()
{
    Tetrixwindow* t = new Tetrixwindow(wid->width,wid->height);
    t->setWindowTitle("极限模式");
    t->show();
    t->wid=this;
    this->hide();
}


void SelectMode::on_singleMode_clicked()
{
    Tetrixeasywindow* t = new Tetrixeasywindow(wid->width,wid->height);
    t->setWindowTitle("简单模式");
    t->show();
    t->wid=this;
    this->hide();
}


void SelectMode::on_doubleMode_clicked()
{
    Tetrixdoublewindow* t = new Tetrixdoublewindow(wid->width,wid->height);
    t->setWindowTitle("双人模式");
    t->show();
    t->wid=this;
    this->hide();
}

