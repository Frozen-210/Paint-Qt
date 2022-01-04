#include "paintwindow.h"
#include "ui_paintwindow.h"
#include<QColorDialog>
#include <QFileDialog>
#include "paintscene.h"
#include "json_utilities.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <QSequentialAnimationGroup>
#include "painttable.h"
#include <QFontDatabase>
#include <QMessageBox>
#include "welcomewindow.h"

PaintWindow::PaintWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::PaintWindow)

{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    scene = new PaintScene(ui->graphicsView,ui->DataTable);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QFontDatabase::addApplicationFont(":/font/resources/IROicons.otf");
    QFontDatabase::addApplicationFont(":/font/resources/Montserrat-Regular.ttf");
    QFont montFont = QFont("Montserrat");


    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &PaintWindow::slotTimer);
    timer->start(100);


    // Styling of the upper buttons
    upperBtnStyleSheet="QPushButton {"
                   "background-color: #f9f9f9;"
                   "color: black;"
                   "font-family: Montserrat;"
                   "border-radius: 20px;"
                   "}"
                   "QPushButton:hover{"
                   "background-color: #e0e0e0;"
                   "}"
                   "QPushButton:focus{"
                   "background-color: black;"
                   "color: white;"
                   "}";


    // Styling of the side buttons
    sideBtnStyleSheet="QPushButton {"
                   "color: #a5aeaf;"
                   "border-radius: 10px;"
                   "text-align: left;"
                   "}"
                   "QPushButton:hover{"
                   "color: #6f6f6f;"
                   "}"
                   "QPushButton:pressed{"
                   "color: #000;"
                   ""
                   "}";


    // Styling of the table buttons
    tableBtnStyleSheet = "QPushButton{"
                                 "background-color: #f9f9f9;"
                                 "color: black;"
                                 "border-radius: 20px;"
                                 "font: 11pt Montserrat;"
                                 "}"
                         "QPushButton:hover{"
                                 "background-color: #e0e0e0;"
                                 "}"
                         "QPushButton:pressed{"
                                  "background-color: black;"
                                  "color: white;"
                                  "}";
    // Styling of the menu buttons
    QString menuBtnStyleSheet="QPushButton {"
                   "color: #a5aeaf;"
                   "border-radius: 10px;"
                   "}"
                   "QPushButton:hover{"
                   "color: #6f6f6f;"
                   "}"
                   "QPushButton:pressed{"
                   "color: #000;"
                   ""
                   "}";

    QString logoBtnStyleSheet = "QPushButton:pressed{"
                                "opacity: 0;"
                         "}";


    // Assigning the stylesheet to the upper buttons
    ui->rectangleBtn->setStyleSheet(upperBtnStyleSheet);
    ui->lineBtn->setStyleSheet(upperBtnStyleSheet);
    ui->triangleBtn->setStyleSheet(upperBtnStyleSheet);
    ui->circleBtn->setStyleSheet(upperBtnStyleSheet);

    ui->closeBtn->setFont(QFont("IROicons",21));
    ui->miniBtn->setFont(QFont("IROicons",21));



    // Assigning the stylesheet to the side buttons
    ui->colorBtn->setStyleSheet(sideBtnStyleSheet);
    ui->redoBtn->setStyleSheet(sideBtnStyleSheet);
    ui->undoBtn->setStyleSheet(sideBtnStyleSheet);
    ui->saveBtn->setStyleSheet(sideBtnStyleSheet);
    ui->tableBtn->setStyleSheet(sideBtnStyleSheet);
    ui->ersr_Btn->setStyleSheet(sideBtnStyleSheet);

    // setting embedded font to the icons
    ui->colorBtn->setFont(QFont("IROicons",20));
    ui->redoBtn->setFont(QFont("IROicons",20));
    ui->undoBtn->setFont(QFont("IROicons",18));
    ui->saveBtn->setFont(QFont("IROicons",19));
    ui->tableBtn->setFont(QFont("IROicons",28));
    ui->ersr_Btn->setFont(QFont("IROicons",22));


    // sets placeholder text to the search bar
    ui->searchBar->setPlaceholderText("Search");

    // assigning the stylesheet to the table buttons
    ui->SortASBtn->setStyleSheet(tableBtnStyleSheet);
    ui->SortDSBtn->setStyleSheet(tableBtnStyleSheet);

    ui->searchIcon->setFont(QFont("IROicons",20));
    ui->logoBtn->setStyleSheet(logoBtnStyleSheet);

    ui->newMenNew->setStyleSheet(menuBtnStyleSheet);
    ui->newMenOpen->setStyleSheet(menuBtnStyleSheet);
    ui->newMenSave->setStyleSheet(menuBtnStyleSheet);

}


PaintWindow::~PaintWindow()
{
    delete ui;
}

void PaintWindow::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

/*
 * Paint Window Buttons Clicked Functions
 */
void PaintWindow::on_triangleBtn_clicked()
{
    scene->setTypeFigure(PaintScene::TriangleType);
}


void PaintWindow::on_rectangleBtn_clicked()
{
    scene->setTypeFigure(PaintScene::RectangleType);
}


void PaintWindow::on_lineBtn_clicked()
{
    scene->setTypeFigure(PaintScene::LineType);
}


void PaintWindow::on_circleBtn_clicked()
{
    scene->setTypeFigure(PaintScene::CircleType);
}


void PaintWindow::on_undoBtn_clicked()
{
    scene->undoStack->undo();
}


void PaintWindow::on_redoBtn_clicked()
{
    scene->undoStack->redo();
}


void PaintWindow::on_colorBtn_clicked()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid()){
        scene->setColor(newColor);
    }
}


void PaintWindow::on_saveBtn_clicked()
{
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Save As"), "",
                tr("JSON (*.json);;PNG (*.png );; All Files (*)"),&selectedFilter);

    json_utilities *jsonSaveObject;
    if (selectedFilter == "JSON (*.json)") {
        jsonSaveObject->save(scene, fileName);
    }
    else if (selectedFilter == "PNG (*.png )") {
        jsonSaveObject->savePNG(scene, fileName);
    }
}


void PaintWindow::on_verticalSlider_sliderMoved(int position)
{
    scene->setWeight(position);
}

// table animation
//void PaintWindow::on_tableBtn_clicked()
//{
//    QSequentialAnimationGroup* animationGroup = new QSequentialAnimationGroup(this);
//    QPropertyAnimation* hamda = new QPropertyAnimation(ui->moveLO,"geometry");
//    hamda->setDuration(1000);
//    hamda->setStartValue(ui->moveLO->geometry());
//    hamda->setEndValue(ui->moveLO->geometry().translated(100,0));
//    animationGroup->addAnimation(hamda);
//    qDebug() << "ya rab";

//}

/*Dummy method so the compiler stops screaming and launches,
 * the one above is the actual method.at least it will be.*/
void PaintWindow::on_tableBtn_clicked()
{
    QPropertyAnimation *animCont = new QPropertyAnimation(ui->Gbox, "geometry");

    QRect startPos = QRect(1150,170,329,591); // postion of the container hidden
    QRect endPos = QRect(811,170,329,591);  // postion of the container shown

    animCont->setDuration(400);         // time of animation
    animCont->setStartValue(ui->Gbox->geometry());

    if(ui->Gbox->geometry() == startPos){ // Check table Pos

        animCont->setEndValue(endPos);
    }
    else{
        animCont->setEndValue(startPos);
    }
  animCont->start();
}

//Method for eraser button, the main idea is that it deletes the shape you're clicking.
void PaintWindow::on_ersr_Btn_clicked()
{
    scene->setTypeFigure(PaintScene::EraserType);
}


// Function for when the user clicks enter while on the search bar.
void PaintWindow::on_searchBar_returnPressed()
{
    //get the text from the search bar and place it into a string.
    QString srchTxt = ui->searchBar->text();

    //then we copy the Figure vector into a temporary vector,
    QVector<Figure*> *TempVec = scene->ItemsVec;

    /*
     * Then we search that vector trying to find a match for (srchTxt), hopefully we can!
     * complextity of find_if= N applications where N = std::distance(first, last).
    */
    auto it = std::find_if(TempVec->begin(), TempVec->end(), [=] (Figure* const& element) {
        return (element->name == srchTxt);
    });

    bool found = (it != TempVec->end());

    if(found==true){
        int index = std::distance(TempVec->begin(), it);

        // Get index of element from iterator
        ui->DataTable->selectRow(index);
    }
    else
        ui->DataTable->clearSelection();
}



void PaintWindow::open(QString path)
{
    json_utilities *jsonSaveObject;
    jsonSaveObject->open(scene,ui->DataTable,path);
}


void PaintWindow::on_DataTable_cellChanged(int row, int column)
{
    if (column!= 0)
        return;

    (*scene->ItemsVec)[row]->name = ui->DataTable->item(row,column)->text();

}


void PaintWindow::on_SortASBtn_clicked()
{
    PaintTable::SortAVec(scene->ItemsVec);
    PaintTable::UpdateTable(ui->DataTable,*scene->ItemsVec);
}


void PaintWindow::on_SortDSBtn_clicked()
{
    PaintTable::SortDVec(scene->ItemsVec);
    PaintTable::UpdateTable(ui->DataTable,*scene->ItemsVec);
}


void PaintWindow::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving){
        this->move(this->pos() + (event->pos() - mLastMousePosition));
    }
}


void PaintWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        mMoving = true;
        mLastMousePosition = event->pos();
    }
}


void PaintWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        mMoving = false;
    }
}

void PaintWindow::on_logoBtn_clicked()
{
    QPropertyAnimation *animCont = new QPropertyAnimation(ui->menuBox, "geometry");

    QRect startPos = QRect(-4,-85,91,81); // postion of the container hidden
    QRect endPos = QRect(-4,70,100,81);  // postion of the container shown

    animCont->setDuration(5);         // time of animation
    animCont->setStartValue(ui->menuBox->geometry());

    if(ui->menuBox->geometry() == startPos){ // Check table Pos

        animCont->setEndValue(endPos);
    }
    else{
        animCont->setEndValue(startPos);
    }
  animCont->start();
}



void PaintWindow::on_newMenNew_clicked()
{
    PaintWindow *p = new PaintWindow();
    p->show();
    this->hide();
}


void PaintWindow::on_newMenOpen_clicked()
{
    PaintWindow *p = new PaintWindow();

    QString path = QFileDialog::getOpenFileName(p, tr("Open File"),
                                                    "/c://",
                                                    tr("JSON (*.json)"));
    p->show();
    this->hide();
    p->open(path);
}


void PaintWindow::on_newMenSave_clicked()
{
    on_saveBtn_clicked();

}

