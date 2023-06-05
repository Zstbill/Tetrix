#ifndef TETRIXEASYWINDOW_H
#define TETRIXEASYWINDOW_H

#include <QWidget>
#include <widget.h>
#include <selectmode.h>
#include <QCloseEvent>

class TetrixBoard;

namespace Ui {
class Tetrixeasywindow;
}

class Tetrixeasywindow : public QWidget
{
    Q_OBJECT

public:
    explicit Tetrixeasywindow(int w,int h,QWidget *parent = nullptr);
    ~Tetrixeasywindow();
    SelectMode* wid = NULL;
    Ui::Tetrixeasywindow *ui;
    void load(QString str);
    int image=0;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_quitButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();


};

#endif // TETRIXEASYWINDOW_H
