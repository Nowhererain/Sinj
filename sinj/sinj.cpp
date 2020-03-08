#include "sinj.h"
#include "ui_sinj.h"
#include "global.h"
#include "window/editwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QDesktopWidget>
#include <QDebug>

Sinj::Sinj(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sinj)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);

    systray = new Systray(QIcon(":icon/icon.png"), this);
    settingWindow = new SettingWindow(this);

    fileManager.setPath(INI_PATH, DATA_PATH);
    initData();
    displayText();
}

void Sinj::initData()
{
    pressed = false;

    sList = fileManager.getList();
    Config config = fileManager.getConfig();
    currId = config.id;
    currKey = config.key;
    if(sList.size() == 0){
        currId = -1;
        currKey = "";
    }
    else if(currId < sList.size() && currKey == sList[currId]){
        currId = (currId + 1) % sList.size();
    }
    else{
        if(currId >= sList.size()) currId = 0;
        currKey = sList[currId];
    }
}

void Sinj::displayText()
{
    if(currId == -1) ui->textLbl->setText(EMPTY_TEXT);
    else{
        QStringList textList = fileManager.getData(currKey);
        ui->textLbl->setText(textList[CON_POS]);
    }
}

void Sinj::recvEditData(QString key, QStringList list)
{
    fileManager.saveData(key, list);
}

void Sinj::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        pressed = true;
        wpos = event->pos();
    }
}

void Sinj::mouseMoveEvent(QMouseEvent *event)
{
    if(pressed) move(event->pos() - wpos + pos());
}

void Sinj::mouseReleaseEvent(QMouseEvent *)
{
    pressed = false;
}

void Sinj::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(0, 0, 0, 122));
}

void Sinj::showEvent(QShowEvent *)
{
    if(systray == nullptr){
        qDebug() << "Wrong: systray is a nullptr.";
        return;
    }
    systray->show();
}

void Sinj::on_closeBtn_clicked()
{
    QApplication::quit();
}

void Sinj::on_settingBtn_clicked()
{
    if(settingWindow == nullptr){
        qDebug() << "Wrong: settingWindow is a nullptr.";
        return;
    }
    QRect rect = QApplication::desktop()->availableGeometry();
    settingWindow->move((rect.width() - settingWindow->width()) * 0.5, (rect.height() - settingWindow->height()) * 0.5);
    settingWindow->exec();
}

void Sinj::on_editBtn_clicked()
{
    EditWindow * editWindow = new EditWindow;

}

Sinj::~Sinj()
{
    qDebug() << "Sinj call detruction";
    delete ui;
}
