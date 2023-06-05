#include "key.h"
#include "ui_key.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>

key::key(int *k,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::key)
{
    ui->setupUi(this);
    QChar keyChar = QChar::fromLatin1(*k);
    ui->label_2->setText(keyChar);
    K=k;
}

key::~key()
{
    delete ui;
}

void key::keyPressEvent(QKeyEvent *event)
{
    if((event->key()>='A' && event->key()<='Z') || (event->key()>='0' && event->key()<='9'))
    {
        QChar keyChar = QChar::fromLatin1(event->key());
        ui->label_2->setText(keyChar);
        *K=event->key();
    }
}

void key::on_pushButton_clicked()
{
    change->display();
    close();
}

