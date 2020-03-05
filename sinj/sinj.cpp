#include "sinj.h"
#include "ui_sinj.h"
#include <QMouseEvent>
#include <QPainter>
#ifdef Q_OS_WINDOWS
HWND hsinj = NULL;
#endif

Sinj::Sinj(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sinj)
{
    ui->setupUi(this);
#ifdef Q_OS_WINDOWS
    whook = ::SetWinEventHook(
                EVENT_SYSTEM_MINIMIZESTART,
                EVENT_SYSTEM_MINIMIZEEND,
                nullptr,
                WinEventProc,
                0,
                0,
                WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
    );
#endif
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

void Sinj::on_closeBtn_clicked()
{
    QApplication::quit();
}

Sinj::~Sinj()
{
    if(whook){
        UnhookWinEvent(whook);
        whook = nullptr;
    }
    delete ui;
}

#ifdef Q_OS_WINDOWS
void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD event, HWND, LONG, LONG, DWORD, DWORD)
{
    /*Q_UNUSED(hWinEventHook);
    Q_UNUSED(hwnd);
    Q_UNUSED(idObject);
    Q_UNUSED(idChild);
    Q_UNUSED(dwEventThread);
    Q_UNUSED(dwmsEventTime);*/
    //end
    if (event == EVENT_SYSTEM_MINIMIZEEND){
        ::SetWindowPos(hsinj, HWND_NOTOPMOST, 0, 0, 0, 0, ZPOS_FLAGS);
        ::SetWindowPos(hsinj, HWND_BOTTOM, 0, 0, 0, 0, ZPOS_FLAGS);
    }
    //start
    if (event == EVENT_SYSTEM_MINIMIZESTART){
        ::SetWindowPos(hsinj, HWND_TOPMOST, 0, 0, 0, 0, ZPOS_FLAGS);
    }
}
#endif
