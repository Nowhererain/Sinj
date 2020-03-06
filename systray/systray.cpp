#include "systray.h"
#include <QApplication>
#include <QDebug>

Systray::Systray(const QIcon &icon, QWidget *parent): QSystemTrayIcon(icon, parent)
{
    sMenu = new QMenu(parent);
    init();

    connect(this, &QSystemTrayIcon::activated, [=](){
        sMenu->exec(QCursor::pos());
    });
}

void Systray::init()
{
    sQuit = new QAction(tr("quit"), sMenu);

    sMenu->addAction(sQuit);

    connect(sQuit, &QAction::triggered, &QApplication::quit);
}

Systray::~Systray()
{
    qDebug() << "Systray call detruction";
}
