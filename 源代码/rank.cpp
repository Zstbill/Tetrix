#include "rank.h"
#include "ui_rank.h"
#include <QDebug>
#include <QMessageBox>


Rank::Rank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Rank)
{
    ui->setupUi(this);
    QSettings Settings(QDir::currentPath() + "/rank.ini", QSettings::IniFormat);
    QSettings Settings1(QDir::currentPath() + "/easyrank.ini", QSettings::IniFormat);


    QVariantList list;
    QByteArray bytes = Settings.value("scores").toByteArray();
    QDataStream stream(bytes);
    while (!stream.atEnd()) {
        QPair<QString, int> value;
        stream >> value;  // 使用 QDataStream 将数据进行反序列化
        list.append(QVariant::fromValue(value));
    }
    for (int i = 0; i < list.size(); ++i)
    {
        QPair<QString,int> pair = list.at(i).value<QPair<QString,int>>();
        scores.append(pair);
    }


    QVariantList list1;
    bytes = Settings1.value("scores").toByteArray();
    QDataStream stream1(bytes);
    while (!stream1.atEnd()) {
        QPair<QString, int> value;
        stream1 >> value;  // 使用 QDataStream 将数据进行反序列化
        list1.append(QVariant::fromValue(value));
    }

    for (int i = 0; i < list1.size(); ++i)
    {
        QPair<QString,int> pair = list1.at(i).value<QPair<QString,int>>();
        scores1.append(pair);
    }
}


void Rank::display()
{
    scores.clear();
    scores1.clear();
    QSettings Settings(QDir::currentPath() + "/rank.ini", QSettings::IniFormat);
    QSettings Settings1(QDir::currentPath() + "/easyrank.ini", QSettings::IniFormat);

    QVariantList list;
    QByteArray bytes = Settings.value("scores").toByteArray();
    QDataStream stream(bytes);
    while (!stream.atEnd()) {
        QPair<QString, int> value;
        stream >> value;  // 使用 QDataStream 将数据进行反序列化
        list.append(QVariant::fromValue(value));
    }

    for (int i = 0; i < list.size(); ++i)
    {
        QPair<QString,int> pair = list.at(i).value<QPair<QString,int>>();
        scores.append(pair);
    }
    QVariantList list1;
    bytes = Settings1.value("scores").toByteArray();
    QDataStream stream1(bytes);
    while (!stream1.atEnd()) {
        QPair<QString, int> value;
        stream1 >> value;  // 使用 QDataStream 将数据进行反序列化
        list1.append(QVariant::fromValue(value));
    }

    for (int i = 0; i < list1.size(); ++i)
    {
        QPair<QString,int> pair = list1.at(i).value<QPair<QString,int>>();
        scores1.append(pair);
    }
    if(scores.size()>=1) ui->Name1->setText(scores[0].first);
    if(scores.size()>=2) ui->Name2->setText(scores[1].first);
    if(scores.size()>=3) ui->Name3->setText(scores[2].first);
    if(scores.size()>=4) ui->Name4->setText(scores[3].first);
    if(scores.size()>=5) ui->Name5->setText(scores[4].first);

    if(scores.size()>=1)
        ui->Score1->setText(QString::number(scores[0].second));
    if(scores.size()>=2)
        ui->Score2->setText(QString::number(scores[1].second));
    if(scores.size()>=3)
        ui->Score3->setText(QString::number(scores[2].second));
    if(scores.size()>=4)
        ui->Score4->setText(QString::number(scores[3].second));
    if(scores.size()>=5)
        ui->Score5->setText(QString::number(scores[4].second));

    if(scores1.size()>=1)ui->name1->setText(scores1[0].first);
    if(scores1.size()>=2)ui->name2->setText(scores1[1].first);
    if(scores1.size()>=3)ui->name3->setText(scores1[2].first);
    if(scores1.size()>=4)ui->name4->setText(scores1[3].first);
    if(scores1.size()>=5)ui->name5->setText(scores1[4].first);

    if(scores1.size()>=1)
        ui->score1->setText(QString::number(scores1[0].second));
    if(scores1.size()>=2)
        ui->score2->setText(QString::number(scores1[1].second));
    if(scores1.size()>=3)
        ui->score3->setText(QString::number(scores1[2].second));
    if(scores1.size()>=4)
        ui->score4->setText(QString::number(scores1[3].second));
    if(scores1.size()>=5)
        ui->score5->setText(QString::number(scores1[4].second));
}

Rank::~Rank()
{
    delete ui;
}

void Rank::on_pushButton_clicked()
{
    int ret = QMessageBox::question(this, "清空", "是否清空排行榜", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        QString filePath = QDir::currentPath() + "/rank.ini";
        QFile file(filePath);
        file.remove();
        filePath = QDir::currentPath() + "/easyrank.ini";
        QFile file1(filePath);
        file1.remove();
        ui->Name1->setText("");
        ui->Name2->setText("");
        ui->Name3->setText("");
        ui->Name4->setText("");
        ui->Name5->setText("");
        ui->name1->setText("");
        ui->name2->setText("");
        ui->name3->setText("");
        ui->name4->setText("");
        ui->name5->setText("");
        ui->score1->setText("");
        ui->score2->setText("");
        ui->score3->setText("");
        ui->score4->setText("");
        ui->score5->setText("");
        ui->Score1->setText("");
        ui->Score2->setText("");
        ui->Score3->setText("");
        ui->Score4->setText("");
        ui->Score5->setText("");
    }
}

