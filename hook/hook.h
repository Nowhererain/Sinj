#ifndef HOOK_H
#define HOOK_H

#include <QtGlobal>
#include <QWidget>

#ifdef Q_OS_WIN

#include <windows.h>
//#define ZPOS_FLAGS (SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING)
#define ZPOS_FLAGS (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW)
#define hsinj hwnd

class Hook: public QObject
{
    Q_OBJECT

public:
    Hook(QWidget *parent = nullptr);
    ~Hook();

protected:
    HWINEVENTHOOK whook;

};
#endif

#endif // HOOK_H
