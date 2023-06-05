#ifndef SAVE_H
#define SAVE_H

#include <QWidget>

namespace Ui {
class Save;
}

class Save : public QWidget
{
    Q_OBJECT

public:
    explicit Save(QWidget *parent = nullptr);
    ~Save();

private:
    Ui::Save *ui;
};

#endif // SAVE_H
