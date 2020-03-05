#ifndef SYSTRAY_H
#define SYSTRAY_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>

class Systray: public QSystemTrayIcon
{
public:
    Systray(const QIcon &icon, QWidget *parent = nullptr);
    void connect();
    ~Systray();

protected:
    QMenu * sMenu;
    QAction * sQuit;

    void init();
};

#endif // SYSTRAY_H
