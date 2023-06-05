#ifndef CHANGEBOARD_H
#define CHANGEBOARD_H

#include <QWidget>
#include <widget.h>

namespace Ui {
class changeboard;
}

class changeboard : public QWidget
{
    Q_OBJECT

public:
    explicit changeboard(QWidget *parent = nullptr);
    ~changeboard();
    Widget* wid;

private slots:
    void on_pushButton_clicked();

private:
    Ui::changeboard *ui;
};

#endif // CHANGEBOARD_H
