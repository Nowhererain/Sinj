#include "sinj/sinj.h"
#include "hook/hook.h"
#include <QDesktopWidget>
#include <QTranslator>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("Sinj_zh_CN.qm");
    app.installTranslator(&translator);

    Sinj sinj;
#ifdef Q_OS_WIN
extern HWND hsinj;
    Hook hook;
    hsinj = (HWND)sinj.winId();
#endif
    int right = QApplication::desktop()->width();
    sinj.move(right - sinj.width() - 60, 50);
    sinj.show();
    return app.exec();
}
