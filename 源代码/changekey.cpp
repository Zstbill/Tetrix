#include "changekey.h"
#include "ui_changekey.h"
#include <QDir>
#include <QMessageBox>

changekey::changekey(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changekey)
{
    ui->setupUi(this);
    QSettings KeySetting(QDir::currentPath() + "/key.ini", QSettings::IniFormat);//读取键位
    QByteArray data;
    data=KeySetting.value("key").toByteArray();
    QDataStream in(&data, QIODevice::ReadOnly);
    keyCodes.clear();
    in >> keyCodes;
    k[0]=keyCodes.value("Left");
    k[1]=keyCodes.value("Right");
    k[2]=keyCodes.value("Up");
    k[3]=keyCodes.value("Down");
    k[4]=keyCodes.value("Oneline");
    k[5]=keyCodes.value("Drop");
    k[6]=keyCodes.value("Start");
    k[7]=keyCodes.value("Pause");
    QChar keyChar = QChar::fromLatin1(keyCodes.value("Left"));
    ui->Leftlable->setText(keyChar);
    keyChar = QChar::fromLatin1(keyCodes.value("Right"));
    ui->Rightlable->setText(keyChar);
    keyChar = QChar::fromLatin1(keyCodes.value("Up"));
    ui->Uplable->setText(keyChar);
    keyChar = QChar::fromLatin1(keyCodes.value("Down"));
    ui->Downlable->setText(keyChar);
    keyChar = QChar::fromLatin1(keyCodes.value("Oneline"));
    ui->Onelinelable->setText(keyChar);
    keyChar = QChar::fromLatin1(keyCodes.value("Drop"));
    ui->Droplable->setText(keyChar);
    keyChar = QChar::fromLatin1(keyCodes.value("Start"));
    ui->Startlable->setText(keyChar);
    keyChar = QChar::fromLatin1(keyCodes.value("Pause"));
    ui->Pauselable->setText(keyChar);
}

changekey::~changekey()
{
    delete ui;
}

void changekey::display()
{
    QChar keyChar = QChar::fromLatin1(k[0]);
    ui->Leftlable->setText(keyChar);
    keyChar = QChar::fromLatin1(k[1]);
    ui->Rightlable->setText(keyChar);
    keyChar = QChar::fromLatin1(k[2]);
    ui->Uplable->setText(keyChar);
    keyChar = QChar::fromLatin1(k[3]);
    ui->Downlable->setText(keyChar);
    keyChar = QChar::fromLatin1(k[4]);
    ui->Onelinelable->setText(keyChar);
    keyChar = QChar::fromLatin1(k[5]);
    ui->Droplable->setText(keyChar);
    keyChar = QChar::fromLatin1(k[6]);
    ui->Startlable->setText(keyChar);
    keyChar = QChar::fromLatin1(k[7]);
    ui->Pauselable->setText(keyChar);
}

void changekey::on_pushButton_clicked()
{
    bool b=0;
    for(int i=0;i<=7;i++)
    {
        for(int j=i+1;j<=7;j++)
            if(k[i] == k[j])
                b=1;
    }
    if(b) QMessageBox::information(this,"提示","存在相同键位！");
    else
    {
        keyCodes["Left"]=k[0];
        keyCodes["Right"]=k[1];
        keyCodes["Up"]=k[2];
        keyCodes["Down"]=k[3];
        keyCodes["Oneline"]=k[4];
        keyCodes["Drop"]=k[5];
        keyCodes["Start"]=k[6];
        keyCodes["Pause"]=k[7];
        QSettings KeySetting(QDir::currentPath() + "/key.ini", QSettings::IniFormat);//读取键位
        QByteArray data;
        QDataStream out(&data, QIODevice::WriteOnly);
        out << keyCodes;
        KeySetting.setValue("key",data);
        close();
    }
}


void changekey::on_Left_clicked()
{
    key* K = new key(&k[0]);
    K->change=this;
    K->setWindowTitle("方块左移");
    K->show();
}


void changekey::on_Right_clicked()
{
    key* K = new key(&k[1]);
    K->change=this;
    K->setWindowTitle("方块右移");
    K->show();
}


void changekey::on_Up_clicked()
{
    key* K = new key(&k[2]);
    K->change=this;
    K->setWindowTitle("逆时针旋转");
    K->show();
}


void changekey::on_Down_clicked()
{
    key* K = new key(&k[3]);
    K->change=this;
    K->setWindowTitle("顺时针旋转");
    K->show();
}


void changekey::on_Oneline_clicked()
{
    key* K = new key(&k[4]);
    K->change=this;
    K->setWindowTitle("下落一行");
    K->show();
}


void changekey::on_Drop_clicked()
{
    key* K = new key(&k[5]);
    K->change=this;
    K->setWindowTitle("下落到底");
    K->show();
}


void changekey::on_Start_clicked()
{
    key* K = new key(&k[6]);
    K->change=this;
    K->setWindowTitle("开始");
    K->show();
}


void changekey::on_Pause_clicked()
{
    key* K = new key(&k[7]);
    K->change=this;
    K->setWindowTitle("暂停");
    K->show();
}


void changekey::on_pushButton_2_clicked()
{
    int ret = QMessageBox::question(this, "提醒", "确认恢复默认设置吗？", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        keyCodes["Left"]=k[0]='A';
        keyCodes["Right"]=k[1]='D';
        keyCodes["Up"]=k[2]='W';
        keyCodes["Down"]=k[3]='S';
        keyCodes["Oneline"]=k[4]='J';
        keyCodes["Drop"]=k[5]='K';
        keyCodes["Start"]=k[6]='E';
        keyCodes["Pause"]=k[7]='P';
        display();
    }
}

