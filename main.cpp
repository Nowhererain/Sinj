#include "sinj/sinj.h"
#include "hook/hook.h"
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
    sinj.show();
    return app.exec();
}
