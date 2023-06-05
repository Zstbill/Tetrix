#include "changecolor.h"
#include "ui_changecolor.h"
#include <QSettings>
#include <QDir>
#include <QMessageBox>

changecolor::changecolor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changecolor)
{
    QSettings Settings(QDir::currentPath() + "/color.ini", QSettings::IniFormat);
    ui->setupUi(this);
    int speed = Settings.value("speed").toInt();
    QString s = QString::number(speed);
    ui->lineEdit->setText(s);
    int color = Settings.value("color").toInt();
    if(color == 1)
    {
        ui->color1->setChecked(1);
    }
    if(color == 2)
    {
        ui->color2->setChecked(1);
    }
    if(color == 3)
    {
        ui->color3->setChecked(1);
    }
    if(color == 4)
    {
        ui->color4->setChecked(1);
    }
}

changecolor::~changecolor()
{
    delete ui;
}

void changecolor::on_commitButton_clicked()
{
    QSettings Settings(QDir::currentPath() + "/color.ini", QSettings::IniFormat);
    int color=0;
    if(ui->color1->isChecked())
    {
        color=1;
    }
    else if(ui->color2->isChecked())
    {
        color=2;
    }
    else if (ui->color3->isChecked())
    {
        color=3;
    }
    else if(ui->color4->isChecked())
    {
        color=4;
    }
    Settings.setValue("color",color);
    QString str = ui->lineEdit->text();
    bool isNumber = false;
    int speed = str.toInt(&isNumber);
    if(isNumber)
    {
        if(speed < 100 || speed > 2000)
        {
            QMessageBox::warning(this,"警告","时间应在100~2000范围内！");
        }
        else
        {
            Settings.setValue("speed",speed);
            close();
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","请输入整数！");
    }
}

