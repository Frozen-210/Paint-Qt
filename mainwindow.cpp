#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QColorDialog>
#include "paintscene.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();   // Инициализируем графическую сцену
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);                // Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаем скроллбар по горизонтали

    timer = new QTimer();       // Инициализируем таймер
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);          // Запускаем таймер
    undoView = new QUndoView(scene->undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->show();
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer()
{
    /* Переопределяем размеры графической сцены в зависимости
     * от размеров окна
     * */
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QMainWindow::resizeEvent(event);
}

// Ромб
void MainWindow::on_pushButton_clicked()
{
    scene->setTypeFigure(PaintScene::RombType);
}

// Квадрат
void MainWindow::on_pushButton_2_clicked()
{
    scene->setTypeFigure(PaintScene::SquareType);
}

// Треугольник
void MainWindow::on_pushButton_3_clicked()
{
    scene->setTypeFigure(PaintScene::TriangleType);
}
void MainWindow::on_pushButton_4_clicked()
{
    scene->setTypeFigure(PaintScene::LineType);
}
void MainWindow::on_actionUndo_triggered()
{
    scene->undoStack->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    scene->undoStack->redo();
}


void MainWindow::on_actionColor_triggered()
{
    QColor newColor = QColorDialog::getColor();
    if (newColor.isValid()){
        scene->setColor(newColor);
    }


}



void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    scene->setWeight(position);
}


//method for comparison that the sort() method will use when comparing the objects in the vector v
bool compareAs(const Figure* first, const Figure* second){
    return first->perimeter < second->perimeter;
}
//method for sort AScending (by perimeter) button.
void MainWindow::on_sortA_Btn_clicked()
{
    //we make sure the button works
        qDebug()<<"sort ascending button pressed";

        //we sort the vector, parameters for sort here is begin,end of vector and the method used to compare LHs to LHs.
        //in this case the method is compareAs which has Lhs as smaller
        std::sort(scene->ItemsVec->begin(), scene->ItemsVec->end(), compareAs);
        //create a temporary vector that we use for printing.
        QVector<Figure*> *TempVec = scene->ItemsVec;
        //iterate on the temporary vector and disaply the stuff in it
        for (int i=0;i<TempVec->size();i++){
          qDebug()<<(*TempVec)[i]->name<<"perimeter "<<(*TempVec)[i]->perimeter;
        }
        //from now on you just need to signal the table element to update the vector and display it
}


//function that compares descendingly (bigger element is first)
bool compareDs(const Figure* first, const Figure* second){
    return first->perimeter > second->perimeter;
}
//method for button that sorts descendingly.
void MainWindow::on_sortD_Btn_clicked()
{
    //we make sure the button works
        qDebug()<<"sort ascending button pressed";

        //we sort the vector, parameters for sort here is begin,end of vector and the method used to compare LHs to LHs.
        std::sort(scene->ItemsVec->begin(), scene->ItemsVec->end(), compareDs);
        //create a temporary vector that we use for printing.
        QVector<Figure*> *TempVec = scene->ItemsVec;
        //iterate on the temporary vector and disaply the stuff in it
        for (int i=0;i<TempVec->size();i++){
          qDebug()<<(*TempVec)[i]->name<<"perimeter "<<(*TempVec)[i]->perimeter;
        }
        //from now on you just need to signal the table element to update the vector and disaply it
}

//Function that runs when search button is clicked
void MainWindow::on_srch_Btn_clicked()
{
    //get the text from the textbox and place it into a string.
       QString srchTxt = ui->lineEdit_srchTxt->text();
       qDebug()<<"Searching for : "<<srchTxt;
       //then we copy the Figure vector into a temporary vector,
       QVector<Figure*> *TempVec = scene->ItemsVec;
       //then we search that vector trying to find a match for (srchTxt), hopefully we can!
           auto it = std::find_if(TempVec->begin(), TempVec->end(), [=] (Figure* const& element) {
               return (element->name == srchTxt);
               });
           bool found = (it != TempVec->end());
           if(found==true){
              qDebug()<<"Item is here";
           }else     qDebug()<<"Item is not here";

}

