#include "saverank.h"
#include "ui_saverank.h"
#include <QCollator>
#include <QDebug>


Saverank::Saverank(int score,bool if_jixian, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Saverank)
{
    ui->setupUi(this);
    this->score = score;
    this->if_jixian = if_jixian;
}


Saverank::~Saverank()
{
    delete ui;
}

void Saverank::on_commitButton_clicked()
{
    name=ui->name->text();
    Rank* r =new Rank;

    if(if_jixian)
    {
        QSettings Settings(QDir::currentPath() + "/rank.ini", QSettings::IniFormat);

        // 添加一个新玩家：name 为玩家名称，score 为玩家得分
        r->scores.append(qMakePair(name, score));

        // 排序并保留前五名玩家
        QCollator collator;
        collator.setNumericMode(true);
        std::sort(r->scores.begin(), r->scores.end(), [&](const QPair<QString, int>& a, const QPair<QString, int>& b) {
            return collator.compare(QString::number(b.second), QString::number(a.second)) < 0;
        });
        if (r->scores.size() > 5) {
            r->scores.pop_back();
        }

        // 写入排行榜数据到 QSettings 中

        QByteArray bytes;
        QDataStream stream(&bytes, QIODevice::WriteOnly);
        for (int i = 0; i < r->scores.size(); ++i) {
            stream << r->scores.at(i); // 使用 QDataStream 将数据进行序列化
        }
        Settings.setValue("scores", bytes);
        r->display();
        r->show();
        this->close();
    }
    else
    {
        QSettings Settings(QDir::currentPath() + "/easyrank.ini", QSettings::IniFormat);

        // 添加一个新玩家：name 为玩家名称，score 为玩家得分
        r->scores1.append(qMakePair(name, score));

        // 排序并保留前五名玩家
        QCollator collator;
        collator.setNumericMode(true);
        std::sort(r->scores1.begin(), r->scores1.end(), [&](const QPair<QString, int>& a, const QPair<QString, int>& b) {
            return collator.compare(QString::number(b.second), QString::number(a.second)) < 0;
        });
        if (r->scores1.size() > 5) {
            r->scores1.pop_back();
        }

        // 写入排行榜数据到 QSettings 中
        QByteArray bytes;
        QDataStream stream(&bytes, QIODevice::WriteOnly);
        for (int i = 0; i < r->scores1.size(); ++i) {
            stream << r->scores1.at(i); // 使用 QDataStream 将数据进行序列化
        }
        Settings.setValue("scores", bytes);
        r->display();
        r->show();
        this->close();
    }
}

