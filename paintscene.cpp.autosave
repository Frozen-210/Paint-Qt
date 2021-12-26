#include "paintscene.h"
#include "romb.h"
#include "triangle.h"
#include "square.h"
#include"line.h"
#include "commands.h"
#include <QVector>
#include "figure.h"
#include <QDebug>


PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
undoStack = new QUndoStack(this);
paintingColor=Qt::black;
LineWeight=1;

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
//    for (int i=0;i<v.size();i++){
//        qDebug()<<v[i]->name<<"perimeter "<<v[i]->perimeter;
//    }
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
    /* Устанавливаем конечную координату положения мыши
     * в текущую отрисовываемую фигуру
     * */
    EndPoint=event->scenePos();
    tempFigure->setEndPoint(EndPoint);

    /* Обновляем содержимое сцены,
     * необходимо для устранения артефактов при отрисовке фигур
     * */

    this->update(QRectF(0,0,this->width(), this->height()));
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    EndPoint=event->scenePos();
    tempFigure->setEndPoint(EndPoint);

       this->update();
       QUndoCommand *addCommand = new AddCommand(this,tempFigure,startPoint);
       undoStack->push(addCommand);

}

/* Как только нажали кнопку мыши, создаём фигуру одного из трёх типов
 * и помещаем её на сцену, сохранив указатель на неё в переменной
 * tempFigure
 * */
void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (m_typeFigure) {
    case SquareType: {
        startPoint = event->scenePos();
        Square *item = new Square(startPoint,paintingColor,LineWeight);
        EndPoint = event->pos();
        item->setPos(EndPoint);
        tempFigure = item;
        Figure* fig= item;
        v.push_back(fig);

        break;
    }
    case RombType: {
      startPoint = event->scenePos();
      Romb *item = new Romb(startPoint,paintingColor,LineWeight);
      EndPoint = event->pos();
      item->setPos(event->pos());
      tempFigure = item;
      Figure* fig= item;
      v.push_back(fig);

      break;

    }
    case LineType: {
      startPoint = event->scenePos();
      Line *item = new Line(startPoint,paintingColor,LineWeight);
      EndPoint = event->pos();
      item->setPos(event->pos());
      tempFigure = item;
      Figure* fig= item;
      v.push_back(fig);

      break;

    }
    case TriangleType: {
        Figure *item = new Triangle(event->scenePos(),paintingColor,LineWeight);
        item->setPos(event->pos());
        tempFigure = item;
        Figure* fig= item;
        v.push_back(fig);

        break;
    }
    default:{
        Square *item = new Square(event->scenePos(),paintingColor,LineWeight);
        item->setPos(event->pos());
        tempFigure = item;
        Figure* fig= item;
        v.push_back(fig);

        break;
    }
    }
    this->addItem(tempFigure);
//    for (int i=0;i<v.size();i++){
//        qDebug()<<v[i]->name<<"perimeter "<<v[i]->perimeter;
//    }
}


