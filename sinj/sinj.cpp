#include "sinj.h"
#include "ui_sinj.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDesktopWidget>
#include <QDebug>

Sinj::Sinj(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sinj)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    systray = new Systray(QIcon(":icon/icon.png"), this);
    settingWindow = new SettingWindow(this);
}

void Sinj::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        pressed = true;
        wpos = event->pos();
    }
}

void Sinj::mouseMoveEvent(QMouseEvent *event)
{
    if(pressed) move(event->pos() - wpos + pos());
}

void Sinj::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}

void Sinj::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(0, 0, 0, 122));
}

void Sinj::showEvent(QShowEvent *)
{
    if(systray == nullptr){
        qDebug() << "Wrong: systray is a nullptr.";
        return;
    }
    systray->show();
}

void Sinj::on_closeBtn_clicked()
{
    QApplication::quit();
}

void Sinj::on_settingBtn_clicked()
{
    if(settingWindow == nullptr){
        qDebug() << "Wrong: settingWindow is a nullptr.";
        return;
    }
    QRect rect = QApplication::desktop()->availableGeometry();
    settingWindow->move((rect.width() - settingWindow->width()) * 0.5, (rect.height() - settingWindow->height()) * 0.5);
    settingWindow->exec();
}

Sinj::~Sinj()
{
    qDebug() << "Sinj call detruction";
    delete ui;
}
