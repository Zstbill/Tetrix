#ifndef TETRIXDOUBLEWINDOW_H
#define TETRIXDOUBLEWINDOW_H

#include <QWidget>
#include <widget.h>
#include <selectmode.h>
#include <QCloseEvent>
#include "tetrixboard1.h"
#include "tetrixboard2.h"

class TetrixBoard1;
class TetrixBoard2;

namespace Ui {
class Tetrixdoublewindow;
}

class Tetrixdoublewindow : public QWidget
{
    Q_OBJECT

public:
    explicit Tetrixdoublewindow(int w, int h, QWidget *parent = nullptr);
    ~Tetrixdoublewindow();
    SelectMode* wid;
    int image=0;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_quitButton_clicked();

private:
    Ui::Tetrixdoublewindow *ui;
};

#endif // TETRIXDOUBLEWINDOW_H
