#include "systray.h"
#include <QApplication>
#include <QDebug>

Systray::Systray(const QIcon &icon, QWidget *parent): QSystemTrayIcon(icon, parent)
{
    sMenu = new QMenu(parent);
    init();

    QObject::connect(this, &QSystemTrayIcon::activated, this, [=](){
        sMenu->exec(QCursor::pos());
    });
}

void Systray::init()
{
    sQuit = new QAction(tr("Quit"), sMenu);

    sMenu->addAction(sQuit);

    QObject::connect(sQuit, &QAction::triggered, this, &QApplication::quit);
}

void Systray::connect()
{

}

Systray::~Systray()
{
    qDebug() << "Systray call detruction";
}
