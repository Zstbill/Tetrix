#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QWidget>
#include <widget.h>
#include <selectmode.h>
#include <QCloseEvent>

class TetrixBoard;

namespace Ui {
class Tetrixwindow;
}

class Tetrixwindow : public QWidget
{
    Q_OBJECT

public:
    explicit Tetrixwindow(int w,int h,QWidget *parent = nullptr);
    ~Tetrixwindow();
    SelectMode* wid = NULL;
    Ui::Tetrixwindow *ui;
    void load(QString str);
    int image=0;


protected:
    void closeEvent(QCloseEvent *event) override;


private slots:
    void on_quitButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();


};

#endif // TETRIXWINDOW_H
