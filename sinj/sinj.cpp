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
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    ui->textLbl->setPalette(pe);

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
    //qDebug() << sList;
    if(sList.size() == 0){
        currId = -1;
        currKey = "";
    }
    else if(0 <= currId && currId < sList.size() && currKey == sList[currId]){
        currId = (currId + 1) % sList.size();
    }
    else{
        if(currId == -1 || currId >= sList.size()) currId = 0;
        currKey = sList[currId];
    }
    //qDebug() << currKey;
}

void Sinj::displayText()
{
    QString str;
    if(currId == -1) str = EMPTY_TEXT;
    else{
        QStringList textList = fileManager.getData(currKey);
        str = textList[CON_POS];
    }

    QFont font(DISPLAY_FONT);
    if(str.length() <= 60) font.setPointSize(16);
    else font.setPointSize(12);
    ui->textLbl->setFont(font);
    ui->textLbl->setText(str);
}

void Sinj::recvEditData(QString key, QStringList list)
{
    sList.append(key);
    fileManager.saveData(key, list);
}

void Sinj::save()
{
    Config config;
    config.id = currId;
    config.key = currKey;
    fileManager.saveConfig(config);
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
    settingWindow->open();
}

void Sinj::on_editBtn_clicked()
{
    EditWindow * editWindow = new EditWindow(this);
    editWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(editWindow, &EditWindow::sendEditData, this, &Sinj::recvEditData);
    QRect rect = QApplication::desktop()->availableGeometry();
    editWindow->move((rect.width() - editWindow->width()) * 0.5, (rect.height() - editWindow->height()) * 0.5);
    editWindow->open();
}

void Sinj::on_nextBtn_clicked()
{
    if(currId == -1 || currId >= sList.size()) currId = 0;
    else if(sList[currId] == currKey) currId = (currId + 1) % sList.size();

    currKey = sList[currId];
    displayText();
}

void Sinj::on_lastBtn_clicked()
{
    currId--;
    if(currId == -1 || currId > sList.size()) currId = sList.size() - 1;
    currKey = sList[currId];
    displayText();
}

Sinj::~Sinj()
{
    save();
    delete ui;
    qDebug() << "Sinj call detruction";
}
