#include "paintwindow.h"
#include "ui_paintwindow.h"
#include<QColorDialog>
#include <QFileDialog>
#include "paintscene.h"
#include "json_utilities.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <QSequentialAnimationGroup>

PaintWindow::PaintWindow(QWidget *parent) :
    QMainWindow(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint),
    ui(new Ui::PaintWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    scene = new PaintScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &PaintWindow::slotTimer);
    timer->start(100);


    // Styling of the upper buttons
    QString upperBtnStyleSheet="QPushButton {"
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
    QString sideBtnStyleSheet="QPushButton {"
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



    // assigning the stylesheet to the upper buttons
    ui->rectangleBtn->setStyleSheet(upperBtnStyleSheet);
    ui->lineBtn->setStyleSheet(upperBtnStyleSheet);
    ui->triangleBtn->setStyleSheet(upperBtnStyleSheet);
    ui->circleBtn->setStyleSheet(upperBtnStyleSheet);
    ui->ersr_Btn->setStyleSheet(upperBtnStyleSheet);

    // assigning the stylesheet to the side buttons
    ui->colorBtn->setStyleSheet(sideBtnStyleSheet);
    ui->redoBtn->setStyleSheet(sideBtnStyleSheet);
    ui->undoBtn->setStyleSheet(sideBtnStyleSheet);
    ui->saveBtn->setStyleSheet(sideBtnStyleSheet);
    ui->tableBtn->setStyleSheet(sideBtnStyleSheet);

    // sets placeholder text to the search bar
    ui->searchBar->setPlaceholderText("Search");

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
void PaintWindow::on_triangleBtn_clicked()
{
    scene->setTypeFigure(PaintScene::TriangleType);
}


void PaintWindow::on_rectangleBtn_clicked()
{
    scene->setTypeFigure(PaintScene::SquareType);
}


void PaintWindow::on_lineBtn_clicked()
{
    scene->setTypeFigure(PaintScene::LineType);
}


void PaintWindow::on_circleBtn_clicked()
{
    scene->setTypeFigure(PaintScene::RombType);
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/c://",
                                                    tr("JSON (*.json)"));

    json_utilities *jsonSaveObject;
    jsonSaveObject->open(scene, fileName);
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
    qDebug() << "under construction.";
}

//Method for eraser button, the main idea is that it deletes the shape you're clicking.
void PaintWindow::on_ersr_Btn_clicked()
{
    //debug message, I swear i use the debugger, i just like it when text shows up after i click a button.
    qDebug()<<"Eraser selected";
    /*we set the type figure as Erasertype, which is just a marker, so when the mouse is clicked, (i.e, mousePressEvent() runs)
    the switch statment for type figure will run the code under the */
    scene->setTypeFigure(PaintScene::EraserType);
}

//function for when the user clicks enter while on the search bar.
void PaintWindow::on_searchBar_returnPressed()
{
    //get the text from the search bar and place it into a string.
       QString srchTxt = ui->searchBar->text();
       qDebug()<<"Searching for : "<<srchTxt;
       //then we copy the Figure vector into a temporary vector,
       QVector<Figure*> *TempVec = scene->ItemsVec;
       /*then we search that vector trying to find a match for (srchTxt), hopefully we can!
        complextity of find_if= N applications where N = std::distance(first, last). */
           auto it = std::find_if(TempVec->begin(), TempVec->end(), [=] (Figure* const& element) {
               return (element->name == srchTxt);
               });
           bool found = (it != TempVec->end());
           if(found==true){
               //code for when the item is found
              qDebug()<<"Item is here";
           }else     {
               //code for when the item is not found.
               qDebug()<<"Item is not here";
           }
}

