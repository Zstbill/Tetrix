#include "save.h"
#include "ui_save.h"

Save::Save(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Save)
{
    ui->setupUi(this);
}

Save::~Save()
{
    delete ui;
}
