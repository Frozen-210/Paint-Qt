#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class messageDialog;
}

class messageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit messageDialog(QWidget *parent = nullptr);
    ~messageDialog();

private:
    Ui::messageDialog *ui;
};

#endif // MESSAGEDIALOG_H
