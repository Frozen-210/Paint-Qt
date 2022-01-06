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
        // Saving The Last Sene
        PaintWindow *p = new PaintWindow();
        QString selectedFilter;
        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Save As"), "",
                    tr("JSON (*.json);; All Files (*)"),&selectedFilter);
        p->on_menuSave(fileName);

        // Opening the wanted File
        QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                        "/c://",
                                                        tr("JSON (*.json)"));

        p->show();
        this->hide();
        p->open(path);
        break;
    }
    case 2:
        PaintWindow *p = new PaintWindow();
        QString selectedFilter;
        QString fileName = QFileDialog::getSaveFileName(
                    this,
                    tr("Save As"), "",
                    tr("JSON (*.json);; All Files (*)"),&selectedFilter);
        p->on_menuSave(fileName);
        this->hide();
        break;
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

        this->hide();
        break;
    }
    case 2:
    {
        this->hide();
        break;
    }
    }
}

