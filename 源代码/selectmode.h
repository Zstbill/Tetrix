#ifndef SELECTMODE_H
#define SELECTMODE_H

#include <QWidget>
#include <widget.h>

namespace Ui {
class SelectMode;
}

class SelectMode : public QWidget
{
    Q_OBJECT

public:
    explicit SelectMode(QWidget *parent = nullptr);
    ~SelectMode();
    Widget* wid;

private slots:
    void on_pushButton_clicked();

    void on_singlejixian_clicked();

    void on_singleMode_clicked();

    void on_doubleMode_clicked();

private:
    Ui::SelectMode *ui;
};

#endif // SELECTMODE_H
