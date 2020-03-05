#include "sinj.h"
#include "ui_sinj.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

Sinj::Sinj(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sinj)
{
    ui->setupUi(this);
    systray = new Systray(QIcon(":icon/icon.png"), this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
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
    systray->show();
}

void Sinj::on_closeBtn_clicked()
{
    QApplication::quit();
}

Sinj::~Sinj()
{
    qDebug() << "Sinj call detruction";
    delete ui;
}
