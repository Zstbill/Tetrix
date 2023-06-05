#ifndef CHANGECOLOR_H
#define CHANGECOLOR_H

#include <QWidget>

namespace Ui {
class changecolor;
}

class changecolor : public QWidget
{
    Q_OBJECT

public:
    explicit changecolor(QWidget *parent = nullptr);
    ~changecolor();

private slots:
    void on_commitButton_clicked();

private:
    Ui::changecolor *ui;
};

#endif // CHANGECOLOR_H
