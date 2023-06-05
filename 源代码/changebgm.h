#ifndef CHANGEBGM_H
#define CHANGEBGM_H

#include <QWidget>
#include <widget.h>
#include <QFileDialog>

namespace Ui {
class changebgm;
}

class changebgm : public QWidget
{
    Q_OBJECT

public:
    explicit changebgm(QWidget *parent = nullptr);
    ~changebgm();
    Widget* wid;

private slots:
    void on_pushButton_clicked();

private:
    Ui::changebgm *ui;
};

#endif // CHANGEBGM_H
