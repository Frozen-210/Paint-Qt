#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>
#include "paintwindow.h"
namespace Ui {
class messageDialog;
}

class messageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit messageDialog(QWidget *parent = nullptr);
    ~messageDialog();
    int actionType;
    bool exitCheck = true;

private slots:
    void on_yesBtn_clicked();

    void on_closeBtn_clicked();

    void on_noBtn_clicked();

private:
    Ui::messageDialog *ui;
};

#endif // MESSAGEDIALOG_H
