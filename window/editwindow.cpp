#include "editwindow.h"
#include "ui_editwindow.h"
#include <QDebug>

EditWindow::EditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
}

void EditWindow::on_okBtn_clicked()
{
    QString key = ui->titleText->text();
    QStringList list;
    list.append(ui->refText->text());
    list.append(ui->contentText->toPlainText());
}

void EditWindow::on_cancelBtn_clicked()
{
    this->close();
}

EditWindow::~EditWindow()
{
    delete ui;
    qDebug() << "EditWindow call destruction";
}
