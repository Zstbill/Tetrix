#ifndef CHANGEBACKGROUND_H
#define CHANGEBACKGROUND_H

#include <QWidget>

namespace Ui {
class changebackground;
}

class changebackground : public QWidget
{
    Q_OBJECT

public:
    explicit changebackground(QWidget *parent = nullptr);
    ~changebackground();
    int image=0;

private slots:
    void on_pushButton_clicked();

    void on_clear_clicked();

private:
    Ui::changebackground *ui;
};

#endif // CHANGEBACKGROUND_H
