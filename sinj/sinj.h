#ifndef SINJ_H
#define SINJ_H

#include <QWidget>
#include "systray/systray.h"
#include "window/settingwindow.h"
#include "filemanager/filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Sinj; }
QT_END_NAMESPACE

class Sinj : public QWidget
{
    Q_OBJECT

public:
    Sinj(QWidget *parent = nullptr);
    ~Sinj();

protected:
    Ui::Sinj *ui;
    bool pressed;
    QPoint wpos;
    int currId;
    QString currKey;
    QStringList sList;
    FileManager fileManager;
    Systray * systray = nullptr;
    SettingWindow * settingWindow = nullptr;

    void initData();
    void displayText();
    void recvEditData(QString key, QStringList list);
    void save();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

protected slots:
    void on_closeBtn_clicked();
    void on_settingBtn_clicked();
    void on_editBtn_clicked();
    void on_nextBtn_clicked();
    void on_lastBtn_clicked();
};
#endif // SINJ_H
