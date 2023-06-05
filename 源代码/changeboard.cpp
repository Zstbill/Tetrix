#include "changeboard.h"
#include "ui_changeboard.h"
#include <QDebug>

changeboard::changeboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changeboard)
{
    ui->setupUi(this);
}

changeboard::~changeboard()
{
    delete ui;
}

void changeboard::on_pushButton_clicked()
{
    if(ui->small->isChecked())
    {
        wid->height=20;
        wid->width=10;
    }
    else if(ui->middle->isChecked())
    {

        wid->height=30;
        wid->width=15;
    }
    else if(ui->big->isChecked())
    {
        wid->height=40;
        wid->width=20;
    }
    close();
}

