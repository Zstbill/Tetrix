#include "instruction.h"
#include "ui_instruction.h"

instruction::instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::instruction)
{
    ui->setupUi(this);
}

instruction::~instruction()
{
    delete ui;
}
