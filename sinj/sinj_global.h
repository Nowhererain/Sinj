#ifndef SINJ_GLOBAL_H
#define SINJ_GLOBAL_H

#include <QtGlobal>
//*********************
#ifdef Q_OS_WINDOWS

#include <windows.h>
//#define ZPOS_FLAGS (SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSENDCHANGING)
#define ZPOS_FLAGS (SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW)

void CALLBACK WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);

#endif
//**********************

#endif // SINJ_GLOBAL_H
