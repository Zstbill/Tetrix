#ifndef RANK_H
#define RANK_H

#include <QWidget>
#include <QSettings>
#include <QPair>
#include <QList>
#include <QMetaType>
#include <QDir>


namespace Ui {
class Rank;
}

class Rank : public QWidget
{
    Q_OBJECT

public:
    explicit Rank(QWidget *parent = nullptr);
    ~Rank();
    QList<QPair<QString, int>> scores;
    QList<QPair<QString, int>> scores1;
    void display();


private slots:
    void on_pushButton_clicked();

private:
    Ui::Rank *ui;

};


#endif // RANK_H
