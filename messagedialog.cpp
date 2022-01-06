#include "messagedialog.h"
#include "ui_messagedialog.h"
#include <QFileDialog>
#include "json_utilities.h"

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

void messageDialog::on_yesBtn_clicked()
{
    switch (actionType){
    case 1:{
        dialogCheck = 1;
        this->hide();
        break;
    }
    case 2:{
        dialogCheck = 2;
        this->hide();
        break;
    }
    case 5:{
        dialogCheck = 5;
        this->hide();
        break;
    }
    }
}


void messageDialog::on_closeBtn_clicked()
{
    exitCheck = false;
    this->hide();
}


void messageDialog::on_noBtn_clicked()
{
    switch (actionType){
    case 1:{
        dialogCheck = 3;
        this->hide();
        break;
    }
    case 2:
    {
        dialogCheck = 4;
        this->hide();
        break;
    }
    case 5:{
        exitCheck = true;
        this->hide();
        break;
    }
    }
}

