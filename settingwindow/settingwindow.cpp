#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QDebug>

SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
}

void SettingWindow::on_cancelBtn_clicked()
{
    this->hide();
}

SettingWindow::~SettingWindow()
{
    delete ui;
    qDebug() << "SettingWindow call destruction";
}
