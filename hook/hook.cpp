#include "hook.h"
#include <QDebug>

#ifdef Q_OS_WIN

HWND hwnd = NULL;

void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD event, HWND, LONG, LONG, DWORD, DWORD)
{
    //end
    if (event == EVENT_SYSTEM_MINIMIZEEND){
        ::SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, ZPOS_FLAGS);
        ::SetWindowPos(hwnd, HWND_BOTTOM, 0, 0, 0, 0, ZPOS_FLAGS);
    }
    //start
    if (event == EVENT_SYSTEM_MINIMIZESTART){
        ::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, ZPOS_FLAGS);
    }
}

Hook::Hook(QWidget *parent): QObject(parent)
{
    whook = ::SetWinEventHook(
                EVENT_SYSTEM_MINIMIZESTART,
                EVENT_SYSTEM_MINIMIZEEND,
                nullptr,
                WinEventProc,
                0,
                0,
                WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS
    );
}

Hook::~Hook()
{
    qDebug() << "Hook call destruction";
    if(whook){
        UnhookWinEvent(whook);
        whook = nullptr;
        qDebug() << "Uninstall hook";
    }
}

#endif //Q_OS_WIN



