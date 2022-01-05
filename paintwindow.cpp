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



    // Assigning the stylesheet to the upper buttons
    ui->rectangleBtn->setStyleSheet(upperBtnStyleSheet);
    ui->lineBtn->setStyleSheet(upperBtnStyleSheet);
    ui->triangleBtn->setStyleSheet(upperBtnStyleSheet);
    ui->circleBtn->setStyleSheet(upperBtnStyleSheet);
    ui->ersr_Btn->setStyleSheet(upperBtnStyleSheet);

    // Assigning the stylesheet to the side buttons
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


void PaintWindow::on_tableBtn_clicked()
{
    QPropertyAnimation *animTable = new QPropertyAnimation(ui->DataTable, "geometry");
    QPropertyAnimation *animInfoTable = new QPropertyAnimation(ui->InfoTable, "geometry");
    QPropertyAnimation *animBtnA = new QPropertyAnimation(ui->SortASBtn , "geometry");
    QPropertyAnimation *animBtnD = new QPropertyAnimation(ui->SortDSBtn, "geometry");
    animBtnA->setDuration(400);
    animBtnD->setDuration(400);
    animTable->setDuration(400);
    animInfoTable->setDuration(400);
    animInfoTable ->setStartValue(ui->InfoTable->geometry());
    animTable->setStartValue(ui->DataTable->geometry());
    animBtnA->setStartValue(ui->SortASBtn->geometry());
    animBtnD->setStartValue(ui->SortDSBtn->geometry());

    if(ui->DataTable->geometry() == QRect(1140,150,329,451)){ // Check table Pos
        // if table is viewed out the view

        animTable->setEndValue(QRect(790,120,329,451));
        animInfoTable->setEndValue(QRect(790,590,329,191));
        animBtnA->setEndValue(QRect(790,90,160,29));
        animBtnD->setEndValue(QRect(960,90,160,29));
    }
    else{
        // if table is viewed over the view
        animTable->setEndValue(QRect(1140,150,329,451));
        animInfoTable->setEndValue(QRect(1140,620,329,191));
        animBtnA->setEndValue(QRect(1140,90,160,29));
        animBtnD->setEndValue(QRect(1310,90,160,29));

    }
  animTable->start();
  animBtnA->start();
  animInfoTable->start();
  animBtnD->start();
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
<<<<<<< Updated upstream
=======
        Figure* item= (*scene->ItemsVec)[index];
        PaintTable::UpdateInfoTable(ui->InfoTable,item);
        if  (ui->tableCont->geometry() == QRect(1220,149,321,571)) // Check tables visibiity
                             on_tableBtn_clicked();
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======

void PaintWindow::on_DataTable_cellClicked(int row, int column)
{
    Figure* item= (*scene->ItemsVec)[row];
    PaintTable::UpdateInfoTable(ui->InfoTable,item);
    Q_UNUSED(column)
}





void PaintWindow::on_logoBtn_clicked()
{
    QPropertyAnimation *animCont = new QPropertyAnimation(ui->menu, "geometry");
    animCont->setDuration(5);
    animCont->setStartValue(ui->tableCont->geometry());

    if(ui->menu->geometry() == QRect(50,69,121,111)){ // Check table Pos
        // if table is viewed out the view

        animCont->setEndValue(QRect(50,-115,121,111));
    }
    else{
        // if table is viewed over the view
        animCont->setEndValue(QRect(50,69,121,111));

    }
  animCont->start();
}


void PaintWindow::on_menuNew_clicked()
{
    delete this->scene->ItemsVec;
    delete this->scene->undoStack;
    scene->clear();
    this->scene->undoStack =new QUndoStack();
    this->scene->ItemsVec = new QVector<Figure*>();
    PaintTable::UpdateTable(scene->table, *scene->ItemsVec);
    Figure::countZero();

}


void PaintWindow::on_menuOpen_clicked()
{
    PaintWindow *p = new PaintWindow();
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/c://",
                                                    tr("JSON (*.json)"));
    p->show();
    this->hide();
    p->open(path);
}


void PaintWindow::on_menuSave_clicked()
{
    on_saveBtn_clicked();
}

>>>>>>> Stashed changes
