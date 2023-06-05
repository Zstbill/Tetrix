#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QMediaPlayer>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    bool continuebgm=1;
    Widget(QWidget *parent = nullptr);
    int width=10,height=20;
    QMediaPlayer* mediaPlayer = new QMediaPlayer(this);
    QMap<QString, int> keyCodes{{"Up", Qt::Key_W}, {"Down", Qt::Key_S}, {"Left", Qt::Key_A}, {"Right", Qt::Key_D},
                                {"Oneline", Qt::Key_J},{"Drop", Qt::Key_K},{"Start", Qt::Key_E},{"Pause", Qt::Key_P}};
    ~Widget();


private slots:


    void on_exit_clicked();

    void on_startgame_clicked();

    void on_introduction_clicked();

    void on_rank_clicked();

    void on_setting_clicked();

    void on_safe_clicked();

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
