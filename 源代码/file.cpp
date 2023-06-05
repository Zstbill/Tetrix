#include "file.h"
#include "ui_file.h"
#include <QInputDialog>
#include <QMessageBox>


File::File(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
    QDir dir(QDir::currentPath()+"/save");
    QStringList filters;
    filters << "*.txt";
    dir.setNameFilters(filters);
    dir.setFilter(QDir::Files);

    QFileInfoList list = dir.entryInfoList();
    foreach (QFileInfo fileInfo, list)
    {
        QListWidgetItem* item = new QListWidgetItem(fileInfo.fileName());
        item->setData(Qt::UserRole, fileInfo.filePath());
        ui->list->addItem(item);
    }
}

File::~File()
{
    delete ui;
}


void File::on_deleteButton_clicked()
{
    int ret = QMessageBox::question(this, "删除", "是否删除此存档", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes)
    {
        QList<QListWidgetItem*> selectedItems = ui->list->selectedItems();
        foreach (QListWidgetItem* item, selectedItems) {
            QString filePath = item->data(Qt::UserRole).toString();
            QFile file(filePath);
            if (file.remove()) {
                ui->list->takeItem(ui->list->row(item));
            }
        }
    }
}


void File::on_copyButton_clicked()
{
    QList<QListWidgetItem*> selectedItems = ui->list->selectedItems();
    foreach (QListWidgetItem* item, selectedItems)
    {
        QString filePath = item->data(Qt::UserRole).toString();
        QFileInfo fileInfo(filePath);
        QString str = fileInfo.fileName();
        str = str.mid(0,str.size()-4);
        QString text = QInputDialog::getText(this, tr("存档"), tr("请输入存档名称："));
        if (!text.isEmpty())
        {
            QString destFilePath = QDir::currentPath() + "/save/" + text + ".txt";
            if (QFile::copy(filePath, destFilePath)) {
                // 创建一个新的 QListWidgetItem
                QListWidgetItem* newItem = new QListWidgetItem(text + ".txt");
                newItem->setData(Qt::UserRole, destFilePath);
                ui->list->addItem(newItem);
            }
        }
    }
}


void File::on_startButton_clicked()
{
    QList<QListWidgetItem*> selectedItems = ui->list->selectedItems();
    foreach (QListWidgetItem* item, selectedItems)
    {
        QString filePath = item->data(Qt::UserRole).toString();
        QFileInfo fileInfo(filePath);
        QString str = QDir::currentPath() + "/save/" + fileInfo.fileName();
        QFile file(str);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Failed to open file for reading.";
            return;
        }
        QTextStream in(&file);

        int if1;
        in >> if1;
        int w,h;
        in>>w>>h;
        file.close();
        if(if1==1)
        {
            Tetrixwindow * t = new Tetrixwindow(w,h);
            t->setWindowTitle("极限模式存档 "+fileInfo.fileName());
            t->show();
            t->load(str);

        }
        else
        {
            Tetrixeasywindow * t = new Tetrixeasywindow(w,h);
            t->setWindowTitle("简单模式存档 "+fileInfo.fileName());
            t->show();
            t->load(str);
        }
    }
}

