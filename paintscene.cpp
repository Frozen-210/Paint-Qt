#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include"line.h"
#include "commands.h"
#include <QVector>
#include "figure.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

PaintScene::PaintScene(QGraphicsView *view,QTableWidget* table, QObject *parent) : QGraphicsScene(parent)
{
    this->view=view;
    undoStack = new QUndoStack(this);
    paintingColor=Qt::black;
    LineWeight=1;
    ItemsVec=new QVector<Figure*>();
    selectingItem=false;
    this->table = table;
}

PaintScene::~PaintScene()
{
}

int PaintScene::typeFigure() const
{
    return m_typeFigure;
}

void PaintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;

}

void PaintScene::setColor(QColor color)
{
    paintingColor=color;
}

void PaintScene::setWeight(int Value)
{
    LineWeight=Value;
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if(m_typeFigure!=EraserType){
    EndPoint=event->scenePos();
    tempFigure->setEndPoint(EndPoint);


    this->update(QRectF(0,0,this->width(), this->height()));}

}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{



    if (m_typeFigure!=EraserType){
        EndPoint=event->scenePos();
        tempFigure->setEndPoint(EndPoint);
        this->update();
       QUndoCommand *addCommand = new AddCommand(this,tempFigure,startPoint,table);
       undoStack->push(addCommand);}
    else{
        if(selectingItem){
        //we add the command for the deletion to the undo stack.
        QUndoCommand *deleteCommand = new DeleteCommand(this,tempFigure,startPoint,table);
        undoStack->push(deleteCommand);
        selectingItem=false;
        }

    }

}


void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (m_typeFigure) {
    case SquareType: {
        startPoint = event->scenePos();
        Square *item = new Square(startPoint,paintingColor,LineWeight);
        EndPoint = event->pos();
        item->setPos(EndPoint);
        tempFigure = item;
        this->addItem(tempFigure);

        break;
    }
    case RombType: {
      startPoint = event->scenePos();
      Romb *item = new Romb(startPoint,paintingColor,LineWeight);
      EndPoint = event->pos();
      item->setPos(event->pos());
      tempFigure = item;
      this->addItem(tempFigure);
      break;

    }
    case LineType: {
      startPoint = event->scenePos();
      Line *item = new Line(startPoint,paintingColor,LineWeight);
      EndPoint = event->pos();
      item->setPos(event->pos());
      tempFigure = item;
      this->addItem(tempFigure);
      break;

    }
    case TriangleType: {
        Figure *item = new Triangle(event->scenePos(),paintingColor,LineWeight);
        item->setPos(event->pos());
        tempFigure = item;
        this->addItem(tempFigure);
        break;
    }
    case EraserType :{ //this is the case for when you're selecting the eraser button and clicked on something

        //this method gets the position of the mouse.
        QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(),
                             event->buttonDownScenePos(Qt::LeftButton).y());
        //this gets the items at this position and puts them in the list.
        QVector<QGraphicsItem *> deletedItems = items(mousePos);
        //then we delete the item from the view and update.
        if(!deletedItems.isEmpty()){
            tempFigure= (Figure*)deletedItems[0];
            selectingItem=true;
            //we delete the item from the vector (ItemsVec) , NOT DONE.
        }
        break;
    }
    default:{
        Square *item = new Square(event->scenePos(),paintingColor,LineWeight);
        item->setPos(event->pos());
        tempFigure = item;
        this->addItem(tempFigure);
        break;
    }
    }


    }


