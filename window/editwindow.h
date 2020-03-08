#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QDialog>

namespace Ui {
class EditWindow;
}

class EditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();

protected:
    Ui::EditWindow *ui;

protected slots:
    void on_okBtn_clicked();
    void on_cancelBtn_clicked();

};

#endif // EDITWINDOW_H
