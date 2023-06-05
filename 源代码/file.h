#ifndef FILE_H
#define FILE_H

#include <QWidget>
#include <QDir>
#include "tetrixeasywindow.h"
#include "tetrixwindow.h"

namespace Ui {
class File;
}

class File : public QWidget
{
    Q_OBJECT

public:
    explicit File(QWidget *parent = nullptr);

    ~File();

private slots:
    void on_deleteButton_clicked();

    void on_copyButton_clicked();

    void on_startButton_clicked();

private:
    Ui::File *ui;
};

#endif // FILE_H
