#include "sinj/sinj.h"
#include <QTranslator>
#include <QApplication>

#ifdef Q_OS_WINDOWS
extern HWND hsinj;
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    translator.load("Sinj_zh_CN.qm");
    app.installTranslator(&translator);

    Sinj sinj;
#ifdef Q_OS_WINDOWS
    hsinj = (HWND)sinj.winId();
#endif
    sinj.show();
    return app.exec();
}
