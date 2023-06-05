#include "changebackground.h"
#include "ui_changebackground.h"
#include <QSettings>
#include <QDir>
#include <QMessageBox>


changebackground::changebackground(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changebackground)
{
    ui->setupUi(this);
    QSettings Settings(QDir::currentPath() + "/color.ini", QSettings::IniFormat);
    image=Settings.value("image").toInt();
    if(image == 1)
    {
        ui->image1->setChecked(1);
    }
    if(image == 2)
    {
        ui->image2->setChecked(1);
    }
    if(image == 3)
    {
        ui->image3->setChecked(1);
    }
    if(image == 4)
    {
        ui->image4->setChecked(1);
    }
    QString imagePath = QDir::currentPath() + "/image/1.jpg";
    QPixmap pix(imagePath);
    ui->label_1->setPixmap(pix);
    imagePath = QDir::currentPath() + "/image/2.jpg";
    pix=QPixmap(imagePath);
    ui->label_2->setPixmap(pix);
    imagePath = QDir::currentPath() + "/image/3.jpg";
    pix=QPixmap(imagePath);
    ui->label_3->setPixmap(pix);
    imagePath = QDir::currentPath() + "/image/4.jpg";
    pix=QPixmap(imagePath);
    ui->label_4->setPixmap(pix);
}

changebackground::~changebackground()
{
    delete ui;
}

void changebackground::on_pushButton_clicked()
{
    QSettings Settings(QDir::currentPath() + "/color.ini", QSettings::IniFormat);
    if(ui->image1->isChecked())
    {
        image=1;
    }
    else if(ui->image2->isChecked())
    {
        image=2;
    }
    else if(ui->image3->isChecked())
    {
        image=3;
    }
    else if(ui->image4->isChecked())
    {
        image=4;
    }
    else image=0;
    Settings.setValue("image",image);
    close();
}


void changebackground::on_clear_clicked()
{
    QSettings Settings(QDir::currentPath() + "/color.ini", QSettings::IniFormat);
    image=0;
    Settings.setValue("image",image);
    close();
}

