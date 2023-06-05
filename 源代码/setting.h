#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <widget.h>

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
    Widget* wid;

private slots:
    void on_changeboard_clicked();

    void on_changebgm_clicked();

    void on_pushButton_clicked();

    void on_changecolor_clicked();

    void on_changekeyevent_clicked();

    void on_changeback_clicked();

private:
    Ui::Setting *ui;
};

#endif // SETTING_H
