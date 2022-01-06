#include "messagedialog.h"
#include "ui_messagedialog.h"

messageDialog::messageDialog(QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::messageDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);

    QString yesBtnStyleSheet="QPushButton {"
                   "background-color: #e0e0e0;"
                   "color: black;"
                   "font: 11pt Montserrat;"
                   "border-radius: 20px;"
                   "}"
                   "QPushButton:hover{"
                   "background-color: #78f8b4;"
                   "}"
                   "QPushButton:pressed{"
                   "background-color: #06ff7b;"
                   "}";

    QString noBtnStyleSheet="QPushButton {"
                   "background-color: #e0e0e0;"
                   "color: black;"
                   "font: 11pt Montserrat;"
                   "border-radius: 20px;"
                   "}"
                   "QPushButton:hover{"
                   "background-color: #fc87b1;"
                   "}"
                   "QPushButton:pressed{"
                   "background-color: #fd2873;"
                   "}";

    ui->yesBtn->setStyleSheet(yesBtnStyleSheet);
    ui->noBtn->setStyleSheet(noBtnStyleSheet);

    this->setModal(true);
}

messageDialog::~messageDialog()
{
    delete ui;
}
