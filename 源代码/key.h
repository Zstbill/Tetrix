#ifndef KEY_H
#define KEY_H

#include <QWidget>
#include "changekey.h"

class changekey;

namespace Ui {
class key;
}

class key : public QWidget
{
    Q_OBJECT

public:
    explicit key(int *k,QWidget *parent = nullptr);
    ~key();
    int *K;
    changekey* change;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_clicked();

private:
    Ui::key *ui;
};

#endif // KEY_H
