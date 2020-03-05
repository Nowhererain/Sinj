#ifndef SINJ_H
#define SINJ_H

#include <QWidget>

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

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

protected slots:
    void on_closeBtn_clicked();
};
#endif // SINJ_H
