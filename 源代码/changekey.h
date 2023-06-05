#ifndef CHANGEKEY_H
#define CHANGEKEY_H

#include <QWidget>
#include <QSettings>
#include "key.h"

namespace Ui {
class changekey;
}

class changekey : public QWidget
{
    Q_OBJECT

public:
    explicit changekey(QWidget *parent = nullptr);
    ~changekey();
    QMap<QString, int> keyCodes;
    int k[8]={0};
    void display();

private slots:
    void on_pushButton_clicked();

    void on_Left_clicked();

    void on_Right_clicked();

    void on_Up_clicked();

    void on_Down_clicked();

    void on_Oneline_clicked();

    void on_Drop_clicked();

    void on_Start_clicked();

    void on_Pause_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::changekey *ui;
};

#endif // CHANGEKEY_H
