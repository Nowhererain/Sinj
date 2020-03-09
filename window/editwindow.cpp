#include "editwindow.h"
#include "ui_editwindow.h"
#include <QDebug>

EditWindow::EditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
    ui->titleText->setText("");
    ui->contentText->setPlainText("");
    ui->useRefBtn->setChecked(true);
}

void EditWindow::on_okBtn_clicked()
{
    QString key = ui->titleText->text();
    QStringList list;
    list.append(ui->refText->text());
    list.append(ui->contentText->toPlainText());
    emit sendEditData(key, list);
    this->close();
}

void EditWindow::on_cancelBtn_clicked()
{
    this->close();
}

void EditWindow::on_noRefBtn_clicked()
{
    ui->refText->clear();
    ui->refText->setEnabled(false);
}

void EditWindow::on_useRefBtn_clicked()
{
    ui->refText->setEnabled(true);
}

EditWindow::~EditWindow()
{
    delete ui;
    qDebug() << "EditWindow call destruction";
}
