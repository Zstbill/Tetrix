#ifndef SAVERANK_H
#define SAVERANK_H

#include <QWidget>
#include "rank.h"

namespace Ui {
class Saverank;
}

class Saverank : public QWidget
{
    Q_OBJECT

public:
    explicit Saverank(int score,bool if_jixian, QWidget *parent = nullptr);
    ~Saverank();

private slots:
    void on_commitButton_clicked();

private:
    Ui::Saverank *ui;
    int score;
    QString name;
    bool if_jixian=0;
};

#endif // SAVERANK_H
