#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "diagramscene.h"
#include "commands.h"
#include<QUndoStack>
#include<QUndoView>
#include<QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    undoStack = new QUndoStack(this);




    undoAction = undoStack->createUndoAction(this, "Undo");
    undoAction->setShortcuts(QKeySequence::Undo);




    diagramScene = new DiagramScene();
    QBrush pixmapBrush(QPixmap(":/images/cross.png").scaled(30, 30));
    diagramScene->setBackgroundBrush(pixmapBrush);
    diagramScene->setSceneRect(QRect(0, 0, 500, 500));

    connect(diagramScene, SIGNAL(itemMoved(DiagramItem*,QPointF)),
            this, SLOT(itemMoved(DiagramItem*,QPointF)));


    setWindowTitle("Undo Framework");
    ui->graphicsView->setScene(diagramScene);
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->show();
    undoView->setAttribute(Qt::WA_QuitOnClose, false);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Triangle_clicked()
{
    ui->graphicsView->raise();
}

void MainWindow::addBox()
{
    //QUndoCommand *addCommand = new AddCommand(DiagramItem::Box, diagramScene);
    //undoStack->push(addCommand);
}

void MainWindow::itemMoved(DiagramItem *movedItem,
                           const QPointF &oldPosition)
{
    undoStack->push(new MoveCommand(movedItem, oldPosition));
}



void MainWindow::on_Rectangle_clicked()
{

    ui->pushButton->raise();
    //QUndoCommand *addCommand = new AddCommand(DiagramItem::Box, diagramScene);
    //undoStack->push(addCommand);
}


void MainWindow::on_actionUndo_triggered()
{
    undoAction = undoStack->createUndoAction(this, "Undo");
    undoAction->setShortcuts(QKeySequence::Undo);
    undoAction->trigger();

}



void MainWindow::on_actionRedo_triggered()
{
    redoAction = undoStack->createRedoAction(this, "Redo");
    redoAction->setShortcuts(QKeySequence::Redo);
    redoAction->trigger();


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

   if(event->button()==Qt::RightButton){
      LastPoint=event->pos();
      isDrawing=true;
   }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton && isDrawing){
       EndPoint=event->pos();
       isDrawing=false;
       QString valueAsString = QString::number(LastPoint.rx());
       QString valueAsString2= QString::number(LastPoint.ry());
       ui->label->setText(valueAsString);
       ui->label_2->setText(valueAsString2);
       QUndoCommand *addCommand = new AddCommand(DiagramItem::Box, diagramScene,LastPoint,EndPoint);
       undoStack->push(addCommand);

    }


}


void MainWindow::deleteItem()
{
    if (diagramScene->selectedItems().isEmpty())
        return;

    QUndoCommand *deleteCommand = new DeleteCommand(diagramScene);
    undoStack->push(deleteCommand);
}



